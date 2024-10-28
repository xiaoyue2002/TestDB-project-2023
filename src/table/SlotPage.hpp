#pragma once
#include <vector>
#include "../defines.h"
#include "../bitmap/bitmap.hpp"
#include "../record_manage/RecordSchema.hpp"

class SlotPage{
public:
    // -- * to be saved * --
    SlotID free_slots;
    Bitmap<SlotID> bitmap;
    // -- * end * --

    BytePtr buff_ptr;
    size_t slot_size;
    size_t header_size;

    bool is_slot_empty(SlotID id){
        return !bitmap.get(id);
    }
    SlotID find_empty_slot(){
        return bitmap.findFirstEmptySlot();
    }
    size_t id_offset(SlotID id){
        return header_size + id * slot_size;
    }
    std::vector<SlotID> get_used_slots(){
        return bitmap.get_all_used();
    }
    bool full(){return (bitmap.findFirstEmptySlot() == -1);}

    void set_slot(SlotID id, bool add){
        if (is_slot_empty(id)){
            if (add) free_slots -= 1;
        }else{
            if (!add) free_slots += 1;
        }
        bitmap.set(id, add);
    }

public:
    SlotPage(){};
    SlotPage(SlotID max_slot, size_t ssize, size_t hsize){
        slot_size = ssize;
        header_size = hsize;
        bitmap = Bitmap<SlotID>(max_slot);
        free_slots = max_slot;
    }
    SlotPage(const SlotPage & other){
        slot_size = other.slot_size;
        bitmap = other.bitmap;
        header_size = other.header_size;
        free_slots = other.free_slots;
        buff_ptr = other.buff_ptr;
    }
    SlotPage(BytePtr b, SlotID max_slot, size_t ssize, size_t hsize){
        buff_ptr = b;
        slot_size = ssize;
        header_size = hsize;
        bitmap = Bitmap<SlotID>(max_slot);
        free_slots = max_slot;
    }

    // 给index用的，因为index会有一个Bool偏差
    BytePtr load_bitmap_bool();
    BytePtr write_bitmap_bool();

    void load_bitmap_bool(BytePtr new_buff_ptr){
        buff_ptr = new_buff_ptr;
        load_bitmap_bool();
    }
    void write_bitmap_bool(BytePtr new_buff_ptr){
        buff_ptr = new_buff_ptr;
        write_bitmap_bool();
    }

    // ------- 

    void load_bitmap(BytePtr new_buff_ptr){
        buff_ptr = new_buff_ptr;
        load_bitmap();
    }
    void write_bitmap(BytePtr new_buff_ptr){
        buff_ptr = new_buff_ptr;
        write_bitmap();
    }
    // Loading / Writing : free_slots, bitmap
    BytePtr load_bitmap();
    BytePtr write_bitmap();

    // Operate on slots
    OPResult insert(BytePtr slot_id, const RecordSchema &);
    OPResult get_by_index(SlotID slot_id, RecordSchema& data);
    OPResult insert_by_index(SlotID& slot_id,  RecordSchema& data);
    OPResult update_by_index(SlotID slot_id,  RecordSchema& data);
    OPResult delete_by_index(SlotID slot_id);

};