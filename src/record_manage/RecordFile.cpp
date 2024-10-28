#include <fstream>
#include "RecordFile.hpp"
#include "RecordSchema.hpp"
#include "RecordPage.hpp"
#include "../defines.h"
#include "../query/constrains.hpp"
#include "../table/Schema.hpp"
#include "../index/IndexSchema.hpp"

void RecordFile::set_schema(Schema schm){
    data_schema = schm;
    record_schema = RecordSchema(schm.fields);
}

void RecordFile::set_dir(std::string dirname){
    meta_file = dirname + "/meta/record.txt" ;
    rec_file = dirname + "/record/data.db";
}

// page schema :
// header freeslot, page_id, next_page, prev_page ,next_empty, prev_empty 
void RecordFile::create_meta(){
    tot_num = 0;
    page_num = 0;
    page_head = -1;
    page_tail = -1;
    empty_head = -1;
    empty_tail = -1;

    size_t slot_size = data_schema.slot_size();
    size_t head_max = sizeof(char) + sizeof(PageID) * 5 + sizeof(SlotID);
    
    page_schema.max_slot = (PAGE_SIZE - head_max) / (slot_size + 1);
    size_t bits_size = std::max(CHAR_STRIDE, sizeof(char) * (page_schema.max_slot + CHAR_BIT - 1) / CHAR_BIT);
    page_schema.slot_size = slot_size;

    page_schema.page_id_offset = sizeof(SlotID) + bits_size;
    page_schema.next_page_offset = page_schema.page_id_offset + sizeof(PageID);
    page_schema.prev_page_offset = page_schema.next_page_offset + sizeof(PageID);
    page_schema.next_empty_offset = page_schema.prev_page_offset + sizeof(PageID);
    page_schema.prev_empty_offset = page_schema.next_empty_offset + sizeof(PageID);
    page_schema.header_size = page_schema.prev_empty_offset + sizeof(PageID);
}

void RecordFile::write_meta(){
    std::ofstream outFile(meta_file);

    outFile << tot_num << " " << page_num << " " << page_head << " " << empty_head << " " << page_tail << " " << empty_tail << std::endl;


    // page schema
    outFile << page_schema.max_slot << " ";
    outFile << page_schema.header_size << " ";
    outFile << page_schema.slot_size << " ";
    outFile << page_schema.page_id_offset << " ";
    outFile << page_schema.next_page_offset << " ";
    outFile << page_schema.prev_page_offset << " ";
    outFile << page_schema.next_empty_offset << " ";
    outFile << page_schema.prev_empty_offset ;

    outFile.close();
}

void RecordFile::read_meta(){
    std::ifstream inFile(meta_file);

    inFile >>  tot_num >> page_num >>  page_head >> empty_head >> page_tail >> empty_tail;
    inFile >> page_schema.max_slot >> page_schema.header_size >> page_schema.slot_size >> page_schema.page_id_offset >> page_schema.next_page_offset >>  page_schema.prev_page_offset >> page_schema.next_empty_offset >> page_schema.prev_empty_offset;

    inFile.close();
}


// --- insert --- 
std::vector<RID> RecordFile::insert_batch_data(std::vector<std::vector<FieldData>> data){
    // debug
    // RecordPage page0(page_num, file_id, bpm, record_schema, page_schema);
    // page0.print();

    RecordPage page(page_num, file_id, bpm, record_schema, page_schema);

    // std::cerr << "RecordFile" << std::endl;
    std::vector<RID> rids = page.insert_batch_data(data);
    
    // 加到 page list里
    if (page_num == 0){
        page.set_pn(-1, -1);
        page.set_empn(-1, -1);
        page_head = 0; page_tail = 0;
        if (page.empty()){
            empty_head = 0; empty_tail = 0;
        }
    }else{
        page.set_pn(page_tail, -1); 
        // prev
        RecordPage prev_page(page_tail, file_id, bpm, record_schema, page_schema);
        prev_page.set_n(page_num);
        // page_tail
        page_tail = page_num;

        // print 
        // prev_page.print();

        // std::cerr << "Empty " << page.empty() << std::endl;
        if(page.empty()){
            if (empty_head == -1){
                empty_head = page_num; // 新的head
                empty_tail = page_num;
                page.set_empn(-1, -1); // 没邻居
            } else{
                page.set_empn(empty_tail, -1);
                RecordPage prev_emp(empty_tail, file_id, bpm, record_schema, page_schema);
                prev_emp.set_emn(page_num);
                empty_tail = page_num;   

                // prev_emp.print();
            }
        } else {
            page.set_empn(-1, -1);
        }
    }

    page.save();
    page_num += 1;
    tot_num += data.size();

    write_meta();

    return rids;
}

void RecordFile::insert_data(std::vector<FieldData> data){
    // 有无空页
    // std::cerr << "insert" << std::endl;
    PageID insert_page = empty_head;
   
    if (insert_page == -1){
        // std::cerr << "new page when insert" << std::endl;
        insert_page = page_num;
        page_num += 1;
    }

    // page 
    RecordPage page(insert_page, file_id, bpm, record_schema, page_schema);
    
    // 这个页面不是凭空创造的
    if (empty_head != -1){
        page.load_bitmap();
    }

    // insert
    page.insert_data(data);

    if (empty_head == -1){  // 凭空创造的page插入list
        if (insert_page == 0){ // create page 0
            page.set_pn(-1, -1);
            page.set_empn(-1, -1);
            page_head = insert_page; page_tail = insert_page;
            if (page.empty()){
                empty_head = 0; empty_tail = 0;
            }
        } else { // create page n
            page.set_pn(page_tail, -1); 
            // prev
            RecordPage prev_page(page_tail, file_id, bpm, record_schema, page_schema);
            prev_page.set_n(insert_page);
            page_tail = insert_page;
            prev_page.save();
            // 此时一定没有空页，直接插入就行
            if (page.empty()){
                empty_head = insert_page; // 新的head
                empty_tail = insert_page;
                page.set_empn(-1, -1); // 唯一值
            }
        }
    } else { // 在已有的空页中插入
        if (!page.empty()){ // 满了
            empty_head = page.get_empnext(); // empty head 后移
            RecordPage next_empage(empty_head, file_id, bpm, record_schema, page_schema);
            next_empage.set_emp(-1); // next 的 prev
            page.set_empn(-1, -1); // full page 格式   
        }
    }

    // page.print();
    page.save();
    tot_num += 1;
    write_meta();
    // std::cerr << "empty tail " << empty_tail << " head " << empty_head << std::endl;
}

void RecordFile::select(std::vector<int> select_ids, std::vector<int> compare_ids, std::vector<Constrain> cons){
    PageID now = page_head;

    while (now != -1){
        RecordPage page(now, file_id, bpm, record_schema, page_schema);
        page.select(select_ids, compare_ids, cons);
        now = page.get_next();
        // std::cerr << "now" << now << std::endl;
    }
}

void RecordFile::delete_data(std::vector<int> comp_ids, std::vector<Constrain> cons){
    PageID now = page_head;

    int count = 0;
    while (now != -1){
        RecordPage page(now, file_id, bpm, record_schema, page_schema);
        bool ori_empty = page.empty();
        int a = page.delete_data(comp_ids, cons);
        
        // 若删空了
        if (!ori_empty){
            if (page.empty()){
                if (empty_head == -1){
                    empty_head = now; empty_tail = now;
                    page.set_empn(-1, -1);
                } else {
                    page.set_empn(empty_tail, -1);
                    RecordPage prev_emp(empty_tail, file_id,  bpm, record_schema, page_schema);
                    prev_emp.set_emn(now);
                    empty_tail = now;
                }
            }
        }

        count += a;
        tot_num -= a;
        page.save();
        now = page.get_next();
    }

    std::cout << "rows" << std::endl;
    std::cout << count << std::endl;
    write_meta();
}

void RecordFile::update_data(std::vector<int> set_ids, std::vector<FieldData> new_data,  std::vector<int> compare_ids, std::vector<Constrain> cons){
    PageID now = page_head;

    int count = 0;
    while (now != -1){
        RecordPage page(now, file_id, bpm, record_schema, page_schema);
        int a = page.update_data(set_ids, new_data, compare_ids, cons);
        now = page.get_next();
        count += a;
        // std::cerr << "now";
    }
    std::cout << "rows" << std::endl;
    std::cout << count << std::endl;
}

void RecordFile::init_join(){
    join_now_page = page_head;
    temp_get_list.clear();
    temp_comp_list.clear();
}

int RecordFile::get_row(std::vector<int> sel_ids, std::vector<int> comp_ids, std::vector<FieldData>& data_get, std::vector<FieldData>& data_comp, std::vector<Constrain> bench, std::vector<int> bench_index){
    
    while (temp_comp_list.size() == 0){

        if (join_now_page == -1){
            // std::cerr << "returning 0 !" << std::endl;
            return -1;
        }

        RecordPage now_page(join_now_page, file_id, bpm, record_schema, page_schema);
        now_page.get_rows(sel_ids, comp_ids, temp_get_list, temp_comp_list, bench, bench_index);      
        join_now_page = now_page.get_next();
    }   

    if (temp_comp_list.size() != 0){
        data_get = temp_get_list.back();
        data_comp = temp_comp_list.back();
        temp_get_list.pop_back();
        temp_comp_list.pop_back();
    }
    return 1;
}

bool RecordFile::dup_pk_check(std::vector<int> pk_data){
    if (tot_num == 0){
        return false;
    }

    PageID now = page_head;

    while (now != -1){
        RecordPage page(now, file_id, bpm, record_schema, page_schema);
        bool dup = page.dup_pk_check(pk_data, data_schema.primary_key_ids);
        if (dup){
            return true;
        }
        now = page.get_next();
    }
    return false;
}

bool RecordFile::check_unique(std::vector<int> kid){
    if (tot_num == 0){
        return true;
    }

    PageID now = page_head;
    std::vector<std::vector<int>> has;
    std::vector<std::vector<int>> page_has;
    while (now != -1){
        RecordPage page(now, file_id, bpm, record_schema, page_schema);
        page_has = page.check_unique(kid);

        // std::cerr << "now " << now << std::endl;
        // for (auto const & a : page_has){
            // std::cerr << a[0] << " " ;
        // }
        // std::cerr << std::endl;

        for (auto const & a : page_has){
            if (std::find(has.begin(), has.end(), a) != has.end()) {
                // std::cerr << "Hit " << a[0] << std::endl;
                return false;
            } else {
                has.push_back(a);
            }
        }

        now = page.get_next();
    }
    return true;
}