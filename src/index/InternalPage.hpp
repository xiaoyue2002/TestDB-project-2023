#pragma once
#include <vector>
#include <fstream>
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../bitmap/bitmap.hpp"
#include "../table/SlotPage.hpp"
#include "IndexSchema.hpp"
#include "../defines.h"
#include "../Logger.hpp"


class InternalPage {
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
    // -- * end * -- 

    /* Schemas */
    SlotSchema * slot_schema;
    IndexPageSchema * schema;
    
    int file_id;
    PageID page_id;
    BufPageManager * bpm;

public:;
    InternalPage(int fid, PageID pid, BufPageManager * bp, IndexPageSchema * schm, SlotSchema * slot_schm): slot_manager(schm->max_slot, schm->slot_size, schm->header_size){
        file_id = fid; page_id = pid; bpm = bp; 
        slot_schema = slot_schm; schema = schm;
        is_leaf = false;
        parent = -1; parent_slot = -1;
        slot_head = -1; slot_tail = -1;
    }

    BytePtr get_slot_ptr(SlotID id, BytePtr buff_ptr){
        // size_t id_offset = slot_manager.is_offset(id);
        return buff_ptr + slot_manager.id_offset(id) / CHAR_STRIDE;
    }
    
    void set_parent(PageID p, SlotID ps){
        parent = p; parent_slot = ps;
    }

    void write_slot(SlotID & prev, SlotID& next, BytePtr slot_ptr){
        Logger::logError("write slot prev " + std::to_string(prev));
        Logger::logError("offset " + std::to_string(slot_schema->prev_offset));
        slot_schema->write_prev_slot(prev, slot_ptr);
        slot_schema->write_next_slot(next, slot_ptr);
    }
    void read_slot(SlotID & prev, SlotID & next, BytePtr slot_ptr){
        prev = slot_schema->get_prev_slot(slot_ptr);
        next = slot_schema->get_next_slot(slot_ptr);
        Logger::logError("read slot prev " +  std::to_string(prev));
        Logger::logError("offset " + std::to_string(slot_schema->prev_offset));
    }

    OPResult search_key(const std::vector<int>, SlotID & hit);
    OPResult insert_slot_keys(const std::vector<int> keys, PageID child, SlotID &hit);
    OPResult update_slot_keys(SlotID tgt, const std::vector<int> keys);

    BytePtr get_page(int &index);
    std::vector<int> get_first_keys();

    void insert_blocks(std::vector<MemoryBlock> mem_block);
    std::vector<MemoryBlock> get_half_out();

    bool check_full();
    bool check_empty();

    OPResult search_child(const std::vector<int> keys, PageID & hit_child);

    /* Load some features */
    void load();
    void write();

    void print();
    
    std::vector<PageID> get_all_child();

    OPResult delete_slot(SlotID);

    PageID find(std::vector<int> keys);
};

    


