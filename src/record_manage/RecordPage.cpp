#include <vector>
#include <string>
#include <fstream>
#include "../defines.h"
#include "RecordPage.hpp"
#include "../table/Schema.hpp"
#include "../query/constrains.hpp"
#include "../index/IndexSchema.hpp"

BytePtr RecordPage::get_page(int& index){
    BufType b = bpm->getPage(file_id, page_id, index);
    return reinterpret_cast<BytePtr>(b);
}

// This is called creating a new page to insert many data
std::vector<RID> RecordPage::insert_batch_data(std::vector<std::vector<FieldData>> data_list){
    // 设置默认写入结构
    // std::cerr << "RecordPage" << std::endl;
    std::vector<RID> rid_list;

    data_schema.set_write();
    
    // 打开文件
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    SlotID slot;
    for (auto const & d : data_list){
        data_schema.write_data = d;
        slot_manager.insert_by_index(slot, data_schema);
        SlotID slot_id = slot;
        rid_list.push_back(RID(page_id, slot_id));
    }
    
    // 写入
    slot_manager.write_bitmap(buff_ptr);

    // 标记为脏页，然后写回文件里
    bpm->markDirty(index);
    bpm->writeBack(index);

    return rid_list;
}

void RecordPage::save(){
    int index; // 如果不在缓存中, 读一个新缓存页写回，没有影响； 在的话实现写回
    BytePtr buff_ptr = get_page(index);
    bpm->markDirty(index);
    bpm->writeBack(index);
}

void RecordPage::insert_data(std::vector<FieldData> data){
    // 设置默认写入结构
    data_schema.set_write();

    // 打开文件
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr; // load_bitmap由上级预先调用

    // 插入
    SlotID slot;
    data_schema.write_data = data;
    slot_manager.insert_by_index(slot, data_schema);
    // std::cerr << "[" << slot_manager.free_slots << "]:" <<  slot_manager.bitmap.show_bits() << std::endl;

    slot_manager.write_bitmap(buff_ptr);
    bpm->markDirty(index);
    bpm->writeBack(index);
}

bool RecordPage::empty(){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);
    return (slot_manager.free_slots > 0);
}

void RecordPage::load_bitmap(){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);
}


void RecordPage::print(){
    std::string filename = "show/" + std::to_string(page_id) + ".txt";
    std::ofstream outFile(filename);

    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);    

    prev_page = page_schema.get_prev_page(buff_ptr);
    next_page = page_schema.get_next_page(buff_ptr);
    prev_empty = page_schema.get_prev_empty(buff_ptr);
    next_empty = page_schema.get_next_empty(buff_ptr);

    outFile << "Page ID   : " << page_id << std::endl;
    outFile << "free slot : " << slot_manager.free_slots << std::endl;
    outFile << "empty     : " << empty() << std::endl;
    outFile << "bits      : " << slot_manager.bitmap.show_bits() << std::endl;
    outFile << "Prev Page : " << prev_page << std::endl;
    outFile << "Next Page : " << next_page << std::endl;
    outFile << "Prev Empt : " << prev_empty << std::endl;
    outFile << "Next Empt : " << next_empty << std::endl;

    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    // 用之前先设置模式
    data_schema.set_read();
    for (auto const & slot_id : all_slots){
        slot_manager.get_by_index(slot_id, data_schema);
        outFile << "[" << slot_id << "]"; 
        outFile << "[" << data_schema.fieldmap.show_bits() << "] : " << std::endl;
        outFile << data_schema.show_data(data_schema.result_data);
        outFile << std::endl;
    }
    outFile.close();
}


void RecordPage::select(std::vector<int> select_ids, std::vector<int> compare_ids, std::vector<Constrain> cons){
    // std::cerr << "page select!" << std::endl;
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);
    
    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    for (auto const & slot_id : all_slots){
        data_schema.set_read(compare_ids);
        slot_manager.get_by_index(slot_id, data_schema);
        bool all_true = true ;
        for (size_t i = 0 ; i < cons.size(); i++){
            bool res = cons[i].bench_judge(data_schema.result_data[i]);
            if (! res) all_true = false;
        }
        if (all_true){
            data_schema.set_read(select_ids);
            slot_manager.get_by_index(slot_id, data_schema);
            bool first = true;
            for (auto const & d : data_schema.result_data){
                if (first) first = false;
                else std::cout << ",";
                std::cout << d.to_string();
            }
            std::cout << std::endl;
        }
    }
}

int RecordPage::delete_data(std::vector<int> compare_ids, std::vector<Constrain> cons){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);

    int count = 0;
    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    for (auto const & slot_id : all_slots){
        data_schema.set_read(compare_ids);
        slot_manager.get_by_index(slot_id, data_schema);
        bool all_true = true ;
        for (size_t i = 0 ; i < cons.size(); i++){
            bool res = cons[i].bench_judge(data_schema.result_data[i]);
            if (! res) all_true = false;
        }
        if (all_true){
            count += 1;
            slot_manager.delete_by_index(slot_id);
        }
    }

    slot_manager.write_bitmap(buff_ptr);
    bpm->markDirty(index);
    bpm->writeBack(index);

    return count;
} 

int RecordPage::update_data(std::vector<int> set_ids, std::vector<FieldData> new_data,  std::vector<int> compare_ids, std::vector<Constrain> cons){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);

    int count = 0;
    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    for (auto const & slot_id : all_slots){
        data_schema.set_read(compare_ids);
        slot_manager.get_by_index(slot_id, data_schema);
        bool all_true = true ;
        for (size_t i = 0 ; i < cons.size(); i++){
            bool res = cons[i].bench_judge(data_schema.result_data[i]);
            if (! res) all_true = false;
        }
        if (all_true){
            count += 1;
            data_schema.set_write(set_ids);
            data_schema.write_data = new_data;
            slot_manager.update_by_index(slot_id, data_schema);
        }
    }

    bpm->markDirty(index);
    bpm->writeBack(index);
    return count;
}

void RecordPage::get_rows(std::vector<int> sel_ids, std::vector<int> comp_ids, std::vector<std::vector<FieldData>>& temp_get, std::vector<std::vector<FieldData>>& temp_comp, std::vector<Constrain> bench, std::vector<int> bench_index){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);

    if (! (temp_comp.empty() && temp_get.empty())){
        throw std::runtime_error("Wrong.");
    }

    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    for (auto const & slot_id : all_slots){
        data_schema.set_read(comp_ids);
        slot_manager.get_by_index(slot_id, data_schema);

        bool all_true = true;
        for (size_t i = 0 ; i < bench.size(); i++){
            // std::cerr << bench[i].bench_data.to_string() << std::endl;
            bool res = bench[i].bench_judge(data_schema.result_data[bench_index[i]]);
            if (!res) all_true = false;
        }
       
        // std::cerr << all_true << std::endl;
        
        if (all_true){   
            temp_comp.push_back(data_schema.result_data);

            data_schema.set_read(sel_ids);
            slot_manager.get_by_index(slot_id, data_schema);
            temp_get.push_back(data_schema.result_data);
        }
    }
    // std::cerr << "get slots " << temp_comp.size() << " " << temp_get.size() << std::endl;
}

bool RecordPage::dup_pk_check(std::vector<int> pk_data, std::vector<int> pids){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);

    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    for (auto const & slot_id : all_slots){
        data_schema.set_read(pids);
        slot_manager.get_by_index(slot_id, data_schema);

        std::vector<int> trans;
        for (auto const & d : data_schema.result_data){
            trans.push_back(d.intValue);
        }

        if (trans == pk_data){
            // std::cerr << "pk" << pk_data[0] << std::endl;
            return true;
        }

    }
    return false;
}

std::vector<std::vector<int>> RecordPage::check_unique(std::vector<int> kids){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap(buff_ptr);

    std::vector<std::vector<int>> has;
    data_schema.set_read(kids);

    std::vector<SlotID> all_slots = slot_manager.get_used_slots();
    for (auto const & slot_id : all_slots){
        slot_manager.get_by_index(slot_id, data_schema);
        std::vector<int> reader;
        for (auto const & d : data_schema.result_data){
            reader.push_back(d.intValue);
        }
        has.push_back(reader);
    }
    return has;
}


// ---- 一些set和get函数 ------ 

void RecordPage::set_pn(PageID p, PageID n){
    int index;
    BytePtr buff_ptr = get_page(index);
    prev_page = p; next_page = n;
    page_schema.write_prev_page(buff_ptr, prev_page);
    page_schema.write_next_page(buff_ptr, next_page);
    bpm->markDirty(index);
}

void RecordPage::set_p(PageID p){
    int index;
    BytePtr buff_ptr = get_page(index);
    prev_page = p;
    page_schema.write_prev_page(buff_ptr, prev_page);
    bpm->markDirty(index);
}

void RecordPage::set_n(PageID n){
    int index;
    BytePtr buff_ptr = get_page(index);
    next_page = n;
    page_schema.write_next_page(buff_ptr, next_page);
    bpm->markDirty(index);
}

void RecordPage::set_empn(PageID p, PageID n){
    int index;
    BytePtr buff_ptr = get_page(index);
    prev_empty = p; next_empty = n;
    page_schema.write_prev_empty(buff_ptr, prev_empty);
    page_schema.write_next_empty(buff_ptr, prev_empty);
    bpm->markDirty(index);
}

void RecordPage::set_emp(PageID p){
    int index;
    BytePtr buff_ptr = get_page(index);
    prev_empty = p;
    page_schema.write_prev_empty(buff_ptr, prev_empty);
    bpm->markDirty(index);
}

void RecordPage::set_emn(PageID n){
    int index;
    BytePtr buff_ptr = get_page(index);
    next_empty = n;
    page_schema.write_next_empty(buff_ptr, next_empty);
    bpm->markDirty(index);
}

PageID RecordPage::get_prev(){
    int index;
    BytePtr buff_ptr = get_page(index);
    prev_page = page_schema.get_prev_page(buff_ptr);
    return prev_page;
}
PageID RecordPage::get_next(){
    int index;
    BytePtr buff_ptr = get_page(index);
    next_page = page_schema.get_next_page(buff_ptr);
    return next_page;
}
PageID RecordPage::get_empprev(){
    int index;
    BytePtr buff_ptr = get_page(index);
    prev_empty = page_schema.get_prev_empty(buff_ptr);
    return prev_empty;
}
PageID RecordPage::get_empnext(){
    int index;
    BytePtr buff_ptr = get_page(index);
    next_page = page_schema.get_next_empty(buff_ptr);
    return next_page;
}
