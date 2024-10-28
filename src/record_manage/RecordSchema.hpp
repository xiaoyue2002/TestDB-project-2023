#pragma once
#include <vector>
#include <string>
#include "../table/Schema.hpp"
#include "../defines.h"
#include "../bitmap/bitmap.hpp"
/*
 *  Standard Schema of a record slot.
 *  This will not change for an entire table.
*/

struct RecordSchema{
    size_t fnum;
    size_t bits_size;
    std::vector<int> index;
    std::vector<size_t> dsizes;
    std::vector<size_t> offset;
    std::vector<DataType> types;
    std::vector<FieldData> default_data;

    Bitmap<int> fieldmap;

    RecordSchema(){}
    RecordSchema(const RecordSchema & other){
        fnum = other.fnum; bits_size = other.bits_size;
        index = other.index; dsizes = other.dsizes;
        offset = other.offset; types = other.types;
        default_data = other.default_data;
        // new
        new_offset = other.new_offset;
        new_sizes = other.new_sizes;
        new_index = other.new_index;
        new_default_data = other.new_default_data;
        new_types = other.new_types;
        // 
        result_data = other.result_data;
        write_data = other.write_data;
    }
    RecordSchema(const std::vector<FieldManager> & fields){
        fnum = fields.size();
        fieldmap = Bitmap<int>(fnum);
        // bitmap
        bits_size = sizeof(char) * ((fnum + CHAR_BIT - 1) / CHAR_BIT);
        bits_size = std::max(CHAR_STRIDE, bits_size);
        size_t off = bits_size;
        for (size_t i = 0; i < fields.size(); i++){
            auto f = fields[i];
            index.push_back(i);
            dsizes.push_back(f.field_size());
            offset.push_back(off);
            types.push_back(f.type);
            default_data.push_back(f.default_value);
            off += f.field_size();
        }
    }

    // if we only read part of slot
    std::vector<size_t> new_offset;
    std::vector<size_t> new_sizes;
    std::vector<int> new_index;
    std::vector<FieldData> new_default_data;
    std::vector<DataType> new_types;

    // to store reading result
    std::vector<FieldData> result_data;

    std::vector<FieldData> write_data;

    bool default_write;
    bool default_read;

    void write(BytePtr buff_ptr);

    void read(BytePtr buff_ptr);

    void clear_vector();

    void set_read();

    void set_read(std::vector<int>);

    void set_write();

    void set_write(std::vector<int>);

    // tostring

    std::string show_data(std::vector<FieldData>);

};


struct RecordPageSchema{

    SlotID max_slot;
    size_t header_size;
    size_t slot_size;

    size_t page_id_offset;
    size_t next_page_offset;
    size_t prev_page_offset;
    size_t next_empty_offset;
    size_t prev_empty_offset;

    // read
    PageID _read_offset(BytePtr buff_ptr, size_t offset){
        PageID get;
        buff_ptr += offset / CHAR_STRIDE;
        memcpy(&get, buff_ptr, sizeof(PageID));
        return get;
    }
    PageID get_page_id(BytePtr buff_ptr){
        return _read_offset(buff_ptr, page_id_offset);
    }
    PageID get_next_page(BytePtr buff_ptr){
        return _read_offset(buff_ptr, next_page_offset);
    }
    PageID get_prev_page(BytePtr buff_ptr){
        return _read_offset(buff_ptr, prev_page_offset);
    }
    PageID get_next_empty(BytePtr buff_ptr){
        return _read_offset(buff_ptr, next_empty_offset);
    }
    PageID get_prev_empty(BytePtr buff_ptr){
        return _read_offset(buff_ptr, prev_empty_offset);
    }
    
    // get
    void _write_offset(BytePtr buff_ptr, size_t offset, PageID page_id){
        buff_ptr += offset / CHAR_STRIDE;
        memcpy(buff_ptr, &page_id, sizeof(PageID));
    }
    void write_page_id(BytePtr buff_ptr, PageID id){
        _write_offset(buff_ptr, page_id_offset, id);
    }
    void write_next_page(BytePtr buff_ptr, PageID id){
        _write_offset(buff_ptr, next_page_offset, id);
    }
    void write_prev_page(BytePtr buff_ptr, PageID id){
        _write_offset(buff_ptr, prev_page_offset, id);
    }
    void write_next_empty(BytePtr buff_ptr, PageID id){
        _write_offset(buff_ptr, next_empty_offset, id);
    }
    void write_prev_empty(BytePtr buff_ptr, PageID id){
        _write_offset(buff_ptr, prev_empty_offset, id);
    }



};


