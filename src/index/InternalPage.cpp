#include <string>
#include <vector>
#include "InternalPage.hpp"
#include "Compare.hpp"


std::vector<PageID> InternalPage::get_all_child(){
    std::vector<PageID> ret_list;
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    SlotID now = slot_head;
    SlotID prev, next;
    BytePtr now_ptr;

    while (now != -1){
        now_ptr = get_slot_ptr(now, buff_ptr);
        PageID child = slot_schema->get_child_page(now_ptr);
        ret_list.push_back(child);
        read_slot(prev, next, now_ptr);
        now = next;
    }
    return ret_list;
}

OPResult InternalPage::search_child(const std::vector<int> keys, PageID & hit_child){
    int hit_slot;
    search_key(keys, hit_slot);
    SlotID real_hit ;

    SlotID prev, next;

    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    if (hit_slot == -1){
        real_hit = slot_tail;
    } else if (hit_slot == - 2){
        throw std::runtime_error("Wrong...!");
    } else if (hit_slot == slot_head){
        real_hit = hit_slot;
    } else {
        BytePtr hit_ptr = get_slot_ptr(hit_slot, buff_ptr);
        read_slot(prev, next, hit_ptr);
        real_hit = prev;
    }
    
    BytePtr slot_ptr = get_slot_ptr(real_hit, buff_ptr);
    hit_child = slot_schema->get_child_page(slot_ptr);
    return OPResult::SUCCESS;
}

OPResult InternalPage::search_key(const std::vector<int> keys, SlotID & hit_slot){
    Logger::logError("search_key");
    int index;
    BytePtr buff_ptr = get_page(index);
    SlotID now = slot_head;
    SlotID prev, next;

    if (now == -1){
        Logger::logError("Internal Search Key : seems blank?");
        hit_slot = -2;
        return OPResult::SUCCESS;
    }
    BytePtr slot_ptr;
    std::vector<int> slot_keys;
    while (now != -1){
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

// half done
PageID InternalPage::find(std::vector<int> keys){
    int index;
    BytePtr buff_ptr = get_page(index);
    SlotID now = slot_head;
    SlotID prev, next;

    BytePtr slot_ptr;
    std::vector<int> slot_keys;

    while (now != -1){
        slot_ptr = get_slot_ptr(now, buff_ptr);
        slot_keys = slot_schema->get_keys(slot_ptr);
    }
}

bool InternalPage::check_full(){
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.load_bitmap_bool(buff_ptr);
    return slot_manager.full();
}

bool InternalPage::check_empty(){
    return slot_manager.free_slots == schema->max_slot;
}

OPResult InternalPage::update_slot_keys(SlotID tgt, const std::vector<int> keys){
    int index;
    // get page
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    BytePtr slot_ptr = get_slot_ptr(tgt, buff_ptr);
    slot_schema->write_keys(keys, slot_ptr);

    bpm->markDirty(index);

    if (tgt == slot_head){
        return OPResult::UPDATE;
    }
    print();
    return OPResult::SUCCESS;
}




OPResult InternalPage::insert_slot_keys(const std::vector<int> keys, PageID child, SlotID & insert_slot){
    Logger::logError("insert_slot_keys");
    SlotID hit_slot;
    SlotID prev, next;

    // find place
    search_key(keys, hit_slot);

    // get page
    OPResult res;
    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    Logger::logError("insert_slot_keys_1");
    
    // insert
    slot_manager.load_bitmap_bool(buff_ptr);
    insert_slot = slot_manager.find_empty_slot();

    // slot_manager.bitmap.show();

    Logger::logError("=== insert slot === " + std::to_string(insert_slot));
    BytePtr slot_ptr = get_slot_ptr(insert_slot, buff_ptr);
    slot_schema->write_keys(keys, slot_ptr);
    slot_schema->write_child_page(child, slot_ptr);
    slot_manager.set_slot(insert_slot, true);
    bpm->markDirty(index);

    Logger::logError("==== hit_slot === "+ std::to_string(hit_slot));
    Logger::logError("Attention!");
    // std::cout << std::hex << (uintptr_t)slot_ptr << std::endl;
    // prev & next
    if (hit_slot == -2){
        slot_head = insert_slot;
        slot_tail = insert_slot;
        prev = -1; next = -1;
        write_slot(prev, next, slot_ptr);
        write();
        res = OPResult::SUCCESS;
    }else if (hit_slot == slot_head){
        slot_head = insert_slot;
        prev = -1; next = hit_slot;
        write_slot(prev, next, slot_ptr);
        // next(hit)
        BytePtr hit_ptr = get_slot_ptr(hit_slot, buff_ptr);
        slot_schema->write_prev_slot(insert_slot, hit_ptr);
        write();
        res = OPResult::UPDATE;
    }else if (hit_slot == -1){
        BytePtr hit_ptr = get_slot_ptr(slot_tail, buff_ptr);
        prev = slot_tail; next = -1;
        slot_tail = insert_slot;
        write_slot(prev, next, slot_ptr);
        slot_schema->write_next_slot(insert_slot, hit_ptr);
        write();
        res = OPResult::SUCCESS;
    }else {
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

    Logger::logError("insert_slot_keys_2");

    bpm->markDirty(index);

    print();
    return res;
}

BytePtr InternalPage::get_page(int & index){
    // Logger::logError("try to get page " + std::to_string(file_id) + " " + std::to_string(page_id));
    BufType buff_ptr = bpm->getPage(file_id, page_id, index);
    return reinterpret_cast<BytePtr>(buff_ptr);
}

std::vector<int> InternalPage::get_first_keys(){
    std::vector<int> keys;
    if (slot_head != -1){
        int index;
        BytePtr buff_ptr = get_page(index);
        BytePtr slot_ptr = get_slot_ptr(slot_head, buff_ptr);
        keys = slot_schema->get_keys(slot_ptr);
    }
    return keys;
}

void InternalPage::load(){
    int index;
    BytePtr buff_ptr = get_page(index);
    is_leaf = schema->get_is_leaf(buff_ptr);
    parent = schema->get_parent(buff_ptr);
    parent_slot = schema->get_parent_slot(buff_ptr);
    slot_head = schema->get_slot_head(buff_ptr);
    slot_tail = schema->get_slot_tail(buff_ptr);

    slot_manager.load_bitmap_bool(buff_ptr);
}

void InternalPage::write(){
    int index; 
    BytePtr buff_ptr = get_page(index);
    schema->write_is_leaf(is_leaf, buff_ptr);
    schema->write_parent(parent, buff_ptr);
    schema->write_parent_slot(parent_slot, buff_ptr);
    schema->write_slot_head(slot_head, buff_ptr);
    schema->write_slot_tail(slot_tail, buff_ptr);

    slot_manager.write_bitmap_bool(buff_ptr);
    bpm->markDirty(index);
}

void InternalPage::print(){
    if (1){
    Logger::logError("==== internal print ! === ");
    std::string name = "show/" + std::to_string(page_id) + ".txt";
    std::ofstream outFile(name);
    load();
    int index;
    SlotID prev, next;

    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;
    if (!buff_ptr){
        Logger::logError("failed to get buff_ptr");
        return ;
    }else{
        Logger::logError("Get buff_ptr");
    }

    outFile << "page_id" << page_id << std::endl;
    outFile << "header_size" << slot_manager.header_size << " slot_size " << slot_manager.slot_size << std::endl; 
    outFile << "max_slot" << schema->max_slot << std::endl;
    outFile << "free_slots" << slot_manager.free_slots << " : " <<  slot_manager.bitmap.show_bits() << std::endl;
    outFile << "is_leaf " << std::to_string(is_leaf) << " " << " parent " << parent << " " << " parent_slot " << parent_slot << " " << std::endl;
    outFile << "slot_head " << slot_head << " slot_tail " << slot_tail << std::endl;

    SlotID now = slot_head;
    BytePtr now_ptr;

    Logger::logError("Attention!");
   
    int count = 0;
    while (now != -1){
        now_ptr = get_slot_ptr(now, buff_ptr);

        // std::cout << std::hex << (uintptr_t)now_ptr << std::endl;
        
        outFile << now << " : (";
        for (auto const & v : slot_schema->get_keys(now_ptr)){
            outFile << v << ", ";
        }
        outFile << ") " << slot_schema->get_child_page(now_ptr);

        read_slot(prev, next, now_ptr);
        outFile << " ; prev_slot " << prev << " next_slot " << next; 
        outFile << std::endl;
        
        now = next;
    }
    // Logger::logError("finished printing");

    outFile.close();
    }
}

std::vector<MemoryBlock> InternalPage::get_half_out(){
    Logger::logError("get_half_out_start");
    std::vector<MemoryBlock> mem_blocks;
    SlotID now , prev, next;
    now = slot_head;
    BytePtr now_ptr;

    int index;
    BytePtr buff_ptr = get_page(index);
    slot_manager.buff_ptr = buff_ptr;

    SlotID half_kept = schema->max_slot / 2 + 1;
    SlotID new_tail;
    Logger::logError("get_half_out_1");
    SlotID count = 0;
    while(now != -1){
        now_ptr = get_slot_ptr(now, buff_ptr);
        
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
        count ++;
    }
    slot_tail = new_tail;
    // 更新结尾的next
    now_ptr = get_slot_ptr(slot_tail, buff_ptr);
    slot_schema->write_next_slot(-1, now_ptr);

    write();
    bpm->markDirty(index);

    Logger::logError("get_half_out_end");
    return mem_blocks;
}

void InternalPage::insert_blocks(std::vector<MemoryBlock> mem_blocks){
    int index; 
    Logger::logError("insert_blocks_inter");
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
    Logger::logError("insert_blocks_end");
}


OPResult InternalPage::delete_slot(SlotID id){
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
            if (slot_schema->get_keys(slot_ptr) != slot_schema->get_keys(slot_ptr)){
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