#include "SlotPage.hpp"
#include "../record_manage/RecordSchema.hpp"
#include "../Logger.hpp"
#include <string>

/* This must be called if loading an existing page. */
BytePtr SlotPage::load_bitmap(){
    if (!buff_ptr) return buff_ptr;
    BytePtr new_ptr = buff_ptr;
    memcpy(&free_slots, new_ptr, sizeof(free_slots));
    new_ptr += sizeof(free_slots) / CHAR_STRIDE;
    memcpy(bitmap.bits, new_ptr, bitmap.bits_size);
    new_ptr += bitmap.bits_size / CHAR_STRIDE;
    return new_ptr;
}

BytePtr SlotPage::write_bitmap(){
    if (!buff_ptr) return buff_ptr;
    BytePtr new_ptr = buff_ptr;
    memcpy(new_ptr, &free_slots, sizeof(free_slots));
    new_ptr += sizeof(free_slots) / CHAR_STRIDE;
    memcpy(new_ptr, bitmap.bits, bitmap.bits_size);
    new_ptr += bitmap.bits_size / CHAR_STRIDE;
    return new_ptr;
}

// for index
BytePtr SlotPage::load_bitmap_bool(){
    if (!buff_ptr) return buff_ptr;
    BytePtr new_ptr = buff_ptr + sizeof(bool) / CHAR_STRIDE;
    memcpy(&free_slots, new_ptr,  sizeof(free_slots));
    new_ptr += sizeof(free_slots) / CHAR_STRIDE;
    memcpy(bitmap.bits, new_ptr, bitmap.bits_size);
    new_ptr += bitmap.bits_size / CHAR_STRIDE;
    return new_ptr;
}

BytePtr SlotPage::write_bitmap_bool(){
    if (!buff_ptr) return buff_ptr;
    BytePtr new_ptr = buff_ptr + sizeof(bool) / CHAR_STRIDE;
    memcpy(new_ptr, &free_slots, sizeof(free_slots));
    new_ptr += sizeof(free_slots) / CHAR_STRIDE;
    memcpy(new_ptr, bitmap.bits, bitmap.bits_size);
    new_ptr += bitmap.bits_size / CHAR_STRIDE;
    return new_ptr;
}

/// 
OPResult SlotPage::get_by_index(SlotID slot_id, RecordSchema& data){
    if (is_slot_empty(slot_id))
        return OPResult::FAILED;
    BytePtr ptr = buff_ptr + id_offset(slot_id) / CHAR_STRIDE ;
    data.read(ptr);
    // Logger::logError("After read.");
    return OPResult::SUCCESS;
}

// 把写bitmap的工作换到外面去了
OPResult SlotPage::insert_by_index(SlotID& slot_id, RecordSchema& data){
    slot_id = find_empty_slot();
    if (slot_id == -1)
        return OPResult::FAILED;
    BytePtr ptr = buff_ptr + id_offset(slot_id) / CHAR_STRIDE;
    data.write(ptr);
    set_slot(slot_id, true);
    return OPResult::SUCCESS;
}

OPResult SlotPage::update_by_index(SlotID slot_id, RecordSchema& data){
    if (is_slot_empty(slot_id))
        return OPResult::FAILED;
    BytePtr ptr = buff_ptr + id_offset(slot_id) / CHAR_STRIDE;
    data.write(ptr);
    return OPResult::SUCCESS;
}

OPResult SlotPage::delete_by_index(SlotID slot_id){
    if (is_slot_empty(slot_id))
        return OPResult::FAILED;
    set_slot(slot_id, false);
    return OPResult::SUCCESS;
}
