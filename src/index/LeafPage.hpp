#pragma once
#include <vector>
#include <fstream>
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../bitmap/bitmap.hpp"
#include "../table/SlotPage.hpp"
#include "IndexSchema.hpp"
#include "../defines.h"
#include "../record_manage/RecordSlot.hpp"
#include "../Logger.hpp"
#include "Compare.hpp"


class LeafPage {
public:
    // -- * to be stored * --
    // free_slot 和 bitmap 用一个slotpage来管理
    SlotPage slot_manager;
    // SlotID free_slot;
    // Bitmap<SlotID> bitmap;
    bool is_leaf;
    PageID parent;
    SlotID parent_slot;
    SlotID slot_head;
    SlotID slot_tail;
    PageID prev_page;
    PageID next_page;
    // -- * end * -- 

    /* Schemas */
    SlotSchema * slot_schema;
    IndexPageSchema * schema;
    
    int file_id;
    PageID page_id;
    BufPageManager * bpm;

public:
    LeafPage(int fid, PageID pid, BufPageManager * bp, IndexPageSchema * schm, SlotSchema * slot_schm): slot_manager(schm->max_slot, schm->slot_size, schm->header_size){
        // Logger::logError("initialize Leafpage " + std::to_string(pid));
        file_id = fid; page_id = pid; bpm = bp; 
        slot_schema = slot_schm; schema = schm;
        is_leaf = true;
        parent = -1; parent_slot = -1;
        slot_head = -1; slot_tail = -1; prev_page = -1; next_page = -1;
    }
    
    BytePtr get_page(int & index);

    BytePtr get_slot_ptr(SlotID id, BytePtr buff_ptr){
        // size_t id_offset = slot_manager.id_offset(id);
        // Logger::logError("id_offset : " + std::to_string(id_offset));
        return buff_ptr + slot_manager.id_offset(id) / CHAR_STRIDE;
    }
    
    void set_parent(PageID p, SlotID ps){
        parent = p; parent_slot = ps;
    }
    void set_sibling(PageID p, PageID n){
        prev_page = p; next_page = n;
    }
    
    std::vector<int> get_first_keys();

    void write_slot(SlotID& prev, SlotID& next, BytePtr slot_ptr){
        // Logger::logError("write slot prev " + std::to_string(prev));
        // Logger::logError("offset " + std::to_string(slot_schema->prev_offset));
        slot_schema->write_prev_slot(prev, slot_ptr);
        slot_schema->write_next_slot(next, slot_ptr);
    }
    void read_slot(SlotID & prev, SlotID & next, BytePtr slot_ptr){
        prev = slot_schema->get_prev_slot(slot_ptr);
        next = slot_schema->get_next_slot(slot_ptr);
        // Logger::logError("read slot prev " +  std::to_string(prev));
        // Logger::logError("offset " + std::to_string(slot_schema->prev_offset));
    }

    void load();
    void write();

    OPResult search_key(const std::vector<int> keys, SlotID& hit_slot);
    OPResult insert_data(const std::vector<int> & keys, const RID & rid);
    
    bool check_full();
    bool check_empty(){return slot_manager.free_slots == schema->max_slot;};

    void print(std::ofstream & outFile);

    void insert_blocks(std::vector<MemoryBlock> mem_block);
    std::vector<MemoryBlock> get_half_out();

    // void traverse(TARGET op, int & tot,  QuerySchema query, OPSchema opschm);
    OPResult delete_slot(SlotID id);

    bool find(std::vector<int> keys, SlotID & slot);
};

