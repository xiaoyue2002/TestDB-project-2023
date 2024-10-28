#include <vector>
#include <cstddef>
#include <string>
#include "IndexSchema.hpp"
#include "../Logger.hpp"

/* private */
PageID IndexPageSchema::_get_pageid(BytePtr buff_ptr, size_t offset){
    PageID page_id; buff_ptr += offset / CHAR_STRIDE;
    memcpy(&page_id, buff_ptr, sizeof(PageID));
    return page_id;
}
SlotID IndexPageSchema::_get_slotid(BytePtr buff_ptr, size_t offset){
    SlotID slot_id; buff_ptr += offset / CHAR_STRIDE;
    memcpy(&slot_id, buff_ptr, sizeof(SlotID));
    return slot_id;
}
void IndexPageSchema::_write_pageid(PageID page_id, BytePtr buff_ptr, size_t offset){
    buff_ptr += offset / CHAR_STRIDE;
    memcpy(buff_ptr, &page_id, sizeof(PageID));
}
void IndexPageSchema::_write_slotid(SlotID slot_id, BytePtr buff_ptr, size_t offset){
    buff_ptr += offset / CHAR_STRIDE;
    memcpy(buff_ptr, &slot_id, sizeof(SlotID));
} 

/* Functions to load */
bool IndexPageSchema::get_is_leaf(BytePtr buff_ptr){
    bool is_leaf;
    // Logger::logError("write_is_leaf " + std::to_string(is_leaf) + " off " + std::to_string(is_leaf_offset));
    buff_ptr += is_leaf_offset / CHAR_STRIDE;
    memcpy(&is_leaf, buff_ptr, sizeof(bool));
    // Logger::logError("get_is_leaf " + std::to_string(is_leaf) + " off " + std::to_string(is_leaf_offset));
    return is_leaf;
}
PageID IndexPageSchema::get_parent(BytePtr buff_ptr){
    return _get_pageid(buff_ptr, parent_offset);
}
SlotID IndexPageSchema::get_parent_slot(BytePtr buff_ptr){
    return _get_slotid(buff_ptr, parent_slot_offset);
}
SlotID IndexPageSchema::get_slot_head(BytePtr buff_ptr){
    return _get_slotid(buff_ptr, slot_head_offset);
}
SlotID IndexPageSchema::get_slot_tail(BytePtr buff_ptr){
    return _get_slotid(buff_ptr, slot_tail_offset);
}
PageID IndexPageSchema::get_prev_page(BytePtr buff_ptr){
    PageID id =  _get_pageid(buff_ptr, prev_page_offset);
    // Logger::logError("get_prev_page : " + std::to_string(id));
    return id ;
}
PageID IndexPageSchema::get_next_page(BytePtr buff_ptr){
    return _get_pageid(buff_ptr, next_page_offset);
}

/* Functions to write */
void IndexPageSchema::write_is_leaf(bool is_leaf, BytePtr buff_ptr){
    // Logger::logError("write_is_leaf " + std::to_string(is_leaf) + " off " + std::to_string(is_leaf_offset));
    buff_ptr += is_leaf_offset / CHAR_STRIDE;
    memcpy(buff_ptr, &is_leaf, sizeof(bool));
}
void IndexPageSchema::write_parent(PageID parent, BytePtr buff_ptr){
    _write_pageid(parent, buff_ptr, parent_offset);
}
void IndexPageSchema::write_parent_slot(SlotID slot, BytePtr buff_ptr){
    _write_slotid(slot, buff_ptr, parent_slot_offset);
}
void IndexPageSchema::write_slot_head(SlotID head, BytePtr buff_ptr){
    _write_slotid(head, buff_ptr, slot_head_offset);
}
void IndexPageSchema::write_slot_tail(SlotID tail, BytePtr buff_ptr){
    _write_slotid(tail, buff_ptr, slot_tail_offset);
}
void IndexPageSchema::write_prev_page(PageID prev, BytePtr buff_ptr){
    // Logger::logError("write_prev_page : " + std::to_string(prev));
    _write_pageid(prev, buff_ptr, prev_page_offset);
}
void IndexPageSchema::write_next_page(PageID next, BytePtr buff_ptr){
    _write_pageid(next, buff_ptr, next_page_offset);
}  


/* SlotSchema */
std::vector<int> SlotSchema::get_keys(BytePtr buff_ptr){
    std::vector<int> keys;
    int k;
    for (auto const & off : key_offsets){
        auto ptr = buff_ptr + off / CHAR_STRIDE;
        memcpy(&k, ptr, sizeof(int));
        keys.push_back(k);
    }
    return keys;
}
PageID SlotSchema::get_child_page(BytePtr buff_ptr){
    PageID page_id; buff_ptr += value_offset / CHAR_STRIDE;
    memcpy(&page_id, buff_ptr, sizeof(SlotID));
    return page_id;
}
SlotID SlotSchema::get_prev_slot(BytePtr buff_ptr){
    SlotID slot_id; buff_ptr += prev_offset / CHAR_STRIDE;
    memcpy(&slot_id, buff_ptr, sizeof(SlotID));
    // Logger::logError("slotschema get_prev " + std::to_string(slot_id));
    return slot_id;
}
SlotID SlotSchema::get_next_slot(BytePtr buff_ptr){
    SlotID slot_id; buff_ptr += next_offset / CHAR_STRIDE;
    memcpy(&slot_id, buff_ptr, sizeof(SlotID));
    return slot_id;
}

void SlotSchema::write_keys(std::vector<int> keys, BytePtr buff_ptr){
    for (size_t i = 0 ; i < keys.size(); i++){
        auto ptr = buff_ptr + key_offsets[i] / CHAR_STRIDE;
        memcpy(ptr, &keys[i], sizeof(int));
    }
}
void SlotSchema::write_child_page(PageID page, BytePtr buff_ptr){
    buff_ptr += value_offset / CHAR_STRIDE;
    memcpy(buff_ptr, &page, sizeof(PageID));
}
void SlotSchema::write_prev_slot(SlotID slot, BytePtr buff_ptr){
    buff_ptr += prev_offset / CHAR_STRIDE;
    memcpy(buff_ptr, &slot, sizeof(SlotID));
    // Logger::logError("slotschema write_prev " + std::to_string(slot));
}
void SlotSchema::write_next_slot(SlotID slot, BytePtr buff_ptr){
    buff_ptr += next_offset / CHAR_STRIDE;
    memcpy(buff_ptr, &slot, sizeof(SlotID));
}

// new add
RID SlotSchema::get_rid(BytePtr buff_ptr){
    PageID pid; SlotID sid;
    BytePtr pid_ptr = buff_ptr + page_id_offset / CHAR_STRIDE;
    BytePtr sid_ptr = buff_ptr + slot_id_offset / CHAR_STRIDE;
    memcpy(&pid, pid_ptr, sizeof(PageID));
    memcpy(&sid, sid_ptr, sizeof(SlotID));
    return RID(pid, sid);
}

void SlotSchema::write_rid(const RID& rid, BytePtr buff_ptr){
    BytePtr pid_ptr = buff_ptr + page_id_offset / CHAR_STRIDE;
    BytePtr sid_ptr = buff_ptr + slot_id_offset / CHAR_STRIDE;
    memcpy(pid_ptr, &rid.page_id, sizeof(PageID));
    memcpy(sid_ptr, &rid.slot_id, sizeof(SlotID));
}