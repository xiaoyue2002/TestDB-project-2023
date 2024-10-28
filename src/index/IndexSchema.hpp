#pragma once
#include <vector>
#include <climits>
#include <cstring>
#include <cstddef>
#include "../defines.h"
/**
 * Struct to help locate some features.
 * also : get features without initializing a whole page.
*/

struct RID{
    PageID page_id;
    SlotID slot_id;

    RID(PageID p, SlotID s): page_id(p), slot_id(s){}
    RID(const RID & other): page_id(other.page_id), slot_id(other.slot_id){};
};

struct IndexPageSchema{
    /* To help locate slots */
    size_t header_size;
    size_t slot_size;
    SlotID max_slot;

    /* To load some features */
    size_t is_leaf_offset;
    size_t parent_offset;
    size_t parent_slot_offset;
    size_t slot_head_offset;
    size_t slot_tail_offset;
    size_t prev_page_offset;
    size_t next_page_offset;

    IndexPageSchema(){};
    IndexPageSchema(const IndexPageSchema & other){
        header_size = other.header_size;
        slot_size = other.slot_size;  max_slot = other.max_slot;
        is_leaf_offset = other.is_leaf_offset; 
        parent_offset = other.parent_offset;
        parent_slot_offset = other.parent_slot_offset;
        slot_head_offset = other.slot_head_offset;
        slot_tail_offset = other.slot_tail_offset;
        prev_page_offset = other.prev_page_offset;
        next_page_offset = other.next_page_offset;
    }

    /* Functions to load */
    bool get_is_leaf(BytePtr buff_ptr);
    PageID get_parent(BytePtr buff_ptr);
    SlotID get_parent_slot(BytePtr buff_ptr);
    SlotID get_slot_head(BytePtr buff_ptr);
    SlotID get_slot_tail(BytePtr buff_ptr);
    PageID get_prev_page(BytePtr buff_ptr);
    PageID get_next_page(BytePtr buff_ptr);

    /* Functions to write */
    void write_is_leaf(bool is_leaf, BytePtr buff_ptr);
    void write_parent(PageID parent, BytePtr buff_ptr);
    void write_parent_slot(SlotID slot, BytePtr buff_ptr);
    void write_slot_head(SlotID head, BytePtr buff_ptr);
    void write_slot_tail(SlotID tail, BytePtr buff_ptr);
    void write_prev_page(PageID prev, BytePtr buff_ptr);
    void write_next_page(PageID next, BytePtr buff_ptr);

private:
    PageID _get_pageid(BytePtr buff_ptr, size_t offset);
    SlotID _get_slotid(BytePtr buff_ptr, size_t offset);
    void _write_pageid(PageID page_id, BytePtr buff_ptr, size_t offset);
    void _write_slotid(SlotID slot_id, BytePtr buff_ptr, size_t offset);
};

struct SlotSchema{
    std::vector<size_t> key_offsets;
    // internal
    size_t value_offset;
    
    size_t prev_offset;
    size_t next_offset;
    // leaf 
    size_t page_id_offset;
    size_t slot_id_offset;

    SlotSchema(){}
    SlotSchema(const SlotSchema & other){
        key_offsets = other.key_offsets;
        value_offset = other.value_offset;
        prev_offset = other.prev_offset;
        next_offset = other.next_offset;
        page_id_offset = other.page_id_offset;
        slot_id_offset = other.slot_id_offset;
    }
    
    std::vector<int> get_keys(BytePtr buff_ptr);
    PageID get_child_page(BytePtr buff_ptr);
    SlotID get_prev_slot(BytePtr buff_ptr);
    SlotID get_next_slot(BytePtr buff_ptr);

    void write_keys(std::vector<int> keys,  BytePtr buff_ptr);
    void write_child_page(PageID page, BytePtr buff_ptr);
    void write_prev_slot(SlotID slot, BytePtr buff_ptr);
    void write_next_slot(SlotID slot, BytePtr buff_ptr);

    RID get_rid(BytePtr buff_ptr);
    void write_rid(const RID& rid, BytePtr buff_ptr);
};

struct InternalSlot{
    std::vector<int> keys;
    PageID value;
    SlotID prev;
    SlotID next;

    InternalSlot(){}
    InternalSlot(const InternalSlot & other){
        keys = other.keys;
        value = other.value;
        prev = other.prev; next = other.next;
    }
    InternalSlot(std::vector<int> k, PageID v): keys(k), value(v){}
    InternalSlot(std::vector<int> k, PageID v, SlotID p, SlotID n): keys(k), value(v), prev(p), next(n){}    
};

struct LeafSlot{
    std::vector<int> keys;
    SlotID prev;
    SlotID next;
    LeafSlot(){}
    LeafSlot(const LeafSlot & other){
        keys = other.keys;
        prev = other.prev; next = other.next;
    }
    LeafSlot(std::vector<int> k, SlotID p, SlotID n): keys(k), prev(p), next(n){};
    LeafSlot(SlotID p, SlotID n): prev(p), next(n){};
};

struct MemoryBlock{
    size_t size;
    SlotID slot_id;
    char * data;

    MemoryBlock(SlotID sid, size_t a): size(a), slot_id(sid){
        data = new char[size];
    }
    MemoryBlock(const MemoryBlock& other) {
        size = other.size;
        data = new char[size];
        slot_id = other.slot_id;
        memcpy(data, other.data, size);
    }

    ~MemoryBlock() { delete[] data; data = nullptr;}
};

struct IndexSchema{
    std::string name;
    bool is_default;
    std::vector<int> key_ids;
    IndexPageSchema internal_schema;
    IndexPageSchema leaf_schema;
    SlotSchema internal_slot_schema;
    SlotSchema leaf_slot_schema;

    IndexSchema(){}
    IndexSchema(std::string n,bool autoc,  std::vector<int> k, IndexPageSchema ip, IndexPageSchema lp, SlotSchema is, SlotSchema ls)
        :name(n), is_default(autoc), key_ids(k), internal_schema(ip), leaf_schema(lp), internal_slot_schema(is), leaf_slot_schema(ls){}
    IndexSchema(const IndexSchema & other){
        name = other.name;
        is_default = other.is_default;
        key_ids = other.key_ids;
        internal_schema = other.internal_schema;
        leaf_schema = other.leaf_schema;
        internal_slot_schema = other.internal_slot_schema;
        leaf_slot_schema = other.leaf_slot_schema;
    }
};

struct IndexInfo{
    int tot_num;
    PageID page_num;
    PageID root;
    PageID data_head;
    
    IndexInfo(){};
    IndexInfo(int num, PageID pn, PageID r, PageID d): tot_num(num), page_num(pn), root(r), data_head(d){};
    IndexInfo(const IndexInfo & other){
        tot_num = other.tot_num; page_num = other.page_num ; root = other.root; data_head = other.data_head;
    }
};

