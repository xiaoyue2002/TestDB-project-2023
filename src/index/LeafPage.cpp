#include <string>
#include <vector>
#include <fstream>
#include "LeafPage.hpp"
#include "../defines.h"
#include "Compare.hpp"
#include "../record_manage/RecordSlot.hpp"

// search_key是安全的, 不会被标记为脏页
OPResult LeafPage::search_key(const std::vector<int> keys, SlotID& hit_slot){
    int index;
    Logger::logError("search_key");
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    SlotID now = slot_head;
    SlotID prev, next;
    
    // Logger::logError("now" + std::to_string(now));
    if (now == -1){
        Logger::logError("Slot_head = -1, seems blank");
        hit_slot = -2;
        return OPResult::SUCCESS;
    }
    Logger::logError("hello");
    BytePtr slot_ptr;
    // read_slot(prev, next, slot_ptr);
    std::vector<int> slot_keys;
    while (now != -1){ // 0 1
        slot_ptr = get_slot_ptr(now, buff_ptr);
        slot_keys = slot_schema->get_keys(slot_ptr);
        if (compare_ge(slot_keys, keys)){
            break;
        }else{
            read_slot(prev, next, slot_ptr);
            now = next;
        }
    }
    hit_slot = now;
    return OPResult::SUCCESS;
}

bool LeafPage::check_full(){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap_bool(buff_ptr);
    return slot_manager.full();
}

OPResult LeafPage::insert_data(const std::vector<int> & keys, const RID & rid){
    Logger::logError("insert_data");
    SlotID hit_slot;
    SlotID insert_slot;
    SlotID prev, next;
    search_key(keys, hit_slot);

    OPResult res;

    int index;
    BytePtr buff_ptr = get_page(index);

    // std::cerr << "buff_ptr" << std::hex << reinterpret_cast<void*>(buff_ptr) << std::endl;
    slot_manager.load_bitmap_bool(buff_ptr);

    insert_slot = slot_manager.find_empty_slot();
    // std::cerr << "insert_slot" << insert_slot << std::endl;
    BytePtr slot_ptr = get_slot_ptr(insert_slot, buff_ptr);
    slot_schema->write_keys(keys, slot_ptr); // keys 
    slot_schema->write_rid(rid, slot_ptr);  // rid

    slot_manager.set_slot(insert_slot, true);
    slot_manager.write_bitmap_bool(buff_ptr);

    // std::cerr << slot_manager.bitmap.show_bits() << std::endl;
    bpm->markDirty(index);

    // the page is empty
    if (hit_slot == -2){
        // Logger::logError("hi3");
        slot_head = insert_slot; slot_tail = insert_slot;
        prev = -1; next = -1;
        write_slot(prev, next, slot_ptr);
        // write 
        write();
        res = OPResult::UPDATE;
    }else if (hit_slot == slot_head){ // 在头上
        // Logger::logError("hi4");
        slot_head = insert_slot;
        prev = -1; next = hit_slot;
        write_slot(prev, next, slot_ptr);
        // 修改hit
        BytePtr hit_ptr = get_slot_ptr(hit_slot, buff_ptr);
        slot_schema->write_prev_slot(insert_slot, hit_ptr);
        // write
        write();
        res = OPResult::UPDATE; // 修改父亲
    }else if (hit_slot == -1){
        Logger::logError("hit tail");
        // 修改hit, hit 在 tail
        BytePtr hit_ptr = get_slot_ptr(slot_tail, buff_ptr);
        prev = slot_tail; next = -1; // 最后
        slot_tail = insert_slot; // update
        write_slot(prev, next, slot_ptr);
        slot_schema->write_next_slot(insert_slot, hit_ptr);
        write();
        res = OPResult::SUCCESS;
    } else { // before hit_ptr
        Logger::logError("hit middle.");
        BytePtr hit_ptr = get_slot_ptr(hit_slot, buff_ptr);
        prev = slot_schema->get_prev_slot(hit_ptr);
        next = hit_slot;
        write_slot(prev, next, slot_ptr);
        slot_schema->write_prev_slot(insert_slot, hit_ptr);
        BytePtr prev_ptr = get_slot_ptr(prev, buff_ptr);
        slot_schema->write_next_slot(insert_slot, prev_ptr);
        write();
        res = OPResult::SUCCESS;
    }

    bpm->markDirty(index);
    // bpm->writeBack(index);

    // std::string output = "show/" + std::to_string(page_id) + ".txt";
    // std::ofstream outfile(output);
    // print(outfile);
    // outfile.close();

    return res;
}


std::vector<int> LeafPage::get_first_keys(){
    std::vector<int> keys;
    if (slot_head != -1){
        int index;
        BytePtr buff_ptr = get_page(index);
        BytePtr slot_ptr = get_slot_ptr(slot_head, buff_ptr);
        keys = slot_schema->get_keys(slot_ptr);
    }
    return keys;
}

void LeafPage::insert_blocks(std::vector<MemoryBlock> mem_blocks){
    int index; 
    Logger::logError("insert_blocks_start");
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;
    
    // clear
    slot_manager.free_slots = schema->max_slot;
    slot_manager.bitmap = Bitmap<SlotID>(schema->max_slot);
    
    // load
    SlotID now;
    BytePtr slot_ptr;
    for (auto const & block : mem_blocks){
        now = block.slot_id;
        slot_ptr = get_slot_ptr(now, buff_ptr);
        memcpy(slot_ptr, block.data, schema->slot_size);
        slot_manager.set_slot(now, true);
    }   
    slot_tail = now;
    slot_head = mem_blocks[0].slot_id;
    slot_ptr = get_slot_ptr(slot_head, buff_ptr);
    slot_schema->write_prev_slot(-1, slot_ptr);

    write();
    bpm->markDirty(index);
    bpm->writeBack(index);
    Logger::logError("insert_blocks_end");
}

std::vector<MemoryBlock> LeafPage::get_half_out(){
    Logger::logError("get_half_out_start");
    std::vector<MemoryBlock> mem_blocks;
    SlotID now , prev, next;
    now = slot_head;
    BytePtr now_ptr;

    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;
    slot_manager.load_bitmap_bool(buff_ptr);

    SlotID count = 0;
    SlotID half_kept = schema->max_slot / 2 + 1;
    SlotID new_tail;
    Logger::logError("get_half_out_1");
    while(now != -1){ 
        now_ptr = get_slot_ptr(now, buff_ptr);
        count += 1;

        if (count > half_kept){
            slot_manager.set_slot(now, false);
            MemoryBlock copy_block(now, schema->slot_size);
            memcpy(copy_block.data, now_ptr, schema->slot_size);
            mem_blocks.push_back(copy_block);
        }
        if (count == half_kept){
            new_tail = now;
        }
        read_slot(prev, next, now_ptr);
        now = next;
    }
    slot_tail = new_tail;
    // 更新结尾的next
    now_ptr = get_slot_ptr(slot_tail, buff_ptr);
    slot_schema->write_next_slot(-1, now_ptr);

    write();
    bpm->markDirty(index);
    bpm->writeBack(index);

    Logger::logError("get_half_out_end");
    return mem_blocks;
}

    
void LeafPage::load(){
    int index;
    BytePtr buff_ptr = get_page(index);
    is_leaf = schema->get_is_leaf(buff_ptr);
    parent = schema->get_parent(buff_ptr);
    parent_slot = schema->get_parent_slot(buff_ptr);
    slot_head = schema->get_slot_head(buff_ptr);
    slot_tail = schema->get_slot_tail(buff_ptr);
    prev_page = schema->get_prev_page(buff_ptr);
    next_page = schema->get_next_page(buff_ptr);

    slot_manager.load_bitmap_bool(buff_ptr);
}

void LeafPage::write(){
    int index; 
    BytePtr buff_ptr = get_page(index);
    schema->write_is_leaf(is_leaf, buff_ptr);
    schema->write_parent(parent, buff_ptr);
    schema->write_parent_slot(parent_slot, buff_ptr);
    schema->write_slot_head(slot_head, buff_ptr);
    schema->write_slot_tail(slot_tail, buff_ptr);
    schema->write_prev_page(prev_page, buff_ptr);
    schema->write_next_page(next_page, buff_ptr);

    slot_manager.write_bitmap_bool(buff_ptr);
    bpm->markDirty(index);
}


void LeafPage::print(std::ofstream & outFile){
    Logger::logError("printing!");
    load();
    int index;
    SlotID prev, next;
    // load page
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;
    

    outFile << "page_id    : " << page_id << std::endl;
    outFile << "header_size: " << slot_manager.header_size << " slot_size " << slot_manager.slot_size << std::endl; 
    outFile << "max_slot   : " << schema->max_slot << std::endl;
    outFile << "free_slots : " << slot_manager.free_slots << " : " <<  slot_manager.bitmap.show_bits() << std::endl;
    outFile << "is_leaf    : " << std::to_string(is_leaf) << " " << " parent " << parent << " " << " parent_slot " << parent_slot << " " << std::endl;
    outFile << "slot_head  : " << slot_head << " slot_tail " << slot_tail << " " << " prev " << prev_page << " next " << next_page << std::endl;

    SlotID now = slot_head;
    BytePtr now_ptr;

    // std::cerr << "buff_ptr" << std::hex << reinterpret_cast<void*>(buff_ptr) << std::endl;

    int count = 0;
    while (now != -1){
        // std::cerr << "now_ptr" << std::hex << reinterpret_cast<void*>(now_ptr) << std::endl;
        now_ptr = get_slot_ptr(now, buff_ptr);

        // slot_manager.get_by_index(now, opschm);
        outFile << now << " : (";
        
        std::vector<int> keys = slot_schema->get_keys(now_ptr);
        
        for (auto const & k : keys){
            outFile << k << ", " ;
        }

        RID rid = slot_schema->get_rid(now_ptr);
        
        outFile << "), [" << rid.page_id << ", " << rid.slot_id << "]";

        read_slot(prev, next, now_ptr);
        outFile << " ; prev_slot " << prev << " next_slot " << next; 
        outFile << std::endl;
        
        now = next;
        count += 1;
        if (count > 200){
            break;
        }
    }
    Logger::logError("finished printing");
}

BytePtr LeafPage::get_page(int & index){
    BufType buff_ptr = bpm->getPage(file_id, page_id, index);
    return reinterpret_cast<BytePtr>(buff_ptr);
}

bool LeafPage::find(std::vector<int> keys, SlotID & slot_id){
    int index;
    Logger::logError("search_key");
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    SlotID now = slot_head;
    SlotID prev, next;
    std::vector<int> slot_keys;

    BytePtr slot_ptr;

    while (now != -1){
        slot_ptr = get_slot_ptr(now, buff_ptr);
        slot_keys = slot_schema->get_keys(slot_ptr);
        if (keys == slot_keys){
            slot_id = now;
            return true;
        }
    }
    return false;
}

// void LeafPage::traverse(TARGET op, int& tot, PageID & next, QuerySchema query, OPSchema& opschm){
//     int index;
//     BytePtr buff_ptr = get_page(index);
//     slot_manager.load_bitmap_bool(buff_ptr);

//     SlotID now = slot_head;
//     SlotID prev, next;

//     BytePtr slot_ptr;
//     while (now != -1){
//         slot_ptr = get_slot_ptr(now, buff_ptr);
//         slot_manager.get_by_index(now, opschm);

//         if (query.compare_data(opschm.result_data)){
//             if tot 
//         }
        
//         read_slot(prev, next, slot_ptr); // travel
//         now = next;
//     }


// }

OPResult LeafPage::delete_slot(SlotID id){
    int index; 
    BytePtr buff_ptr = get_page(index);

    // bitmap
    slot_manager.load_bitmap_bool(buff_ptr);
    slot_manager.set_slot(id, false);
    slot_manager.write_bitmap_bool(buff_ptr);

    BytePtr slot_ptr = get_slot_ptr(id, buff_ptr);
    SlotID prev, next;
    read_slot(prev, next, slot_ptr);

    OPResult res = OPResult::SUCCESS ;

    // head,tail | 前后的指针 
    if (prev != -1){
        BytePtr prev_ptr = get_slot_ptr(prev, buff_ptr);
        slot_schema->write_next_slot(next, prev_ptr);
    }
    if (next != -1){
        BytePtr next_ptr = get_slot_ptr(next, buff_ptr);
        slot_schema->write_prev_slot(prev, next_ptr);
    }
    if (id == slot_head){
        slot_head = next;
        if (check_empty()){ // 已经空了
            res = OPResult::DELETE;
        } else {
            BytePtr next_ptr = get_slot_ptr(next, buff_ptr);
            if (slot_schema->get_keys(slot_ptr) != slot_schema->get_keys(next_ptr)){
                res = OPResult::UPDATE;
            }
        }
    }
    if (id == slot_tail){
        slot_tail = prev;
    }

    bpm->markDirty(index);
    return res;
}