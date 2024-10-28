#include <vector>
#include <string>
#include <sstream>
#include "../defines.h"
#include "RecordSchema.hpp"

// ------------------ clear --------------
void RecordSchema::clear_vector(){
    new_offset.clear();
    new_sizes.clear();
    new_index.clear();
    new_default_data.clear();
    new_types.clear();
}

// ----------------- write --------------------

void RecordSchema::set_write(){
    default_write = true;
}

void RecordSchema::set_write(std::vector<int> write_index){
    clear_vector();
    default_write = false;
    for (auto const& i : write_index){
        new_offset.push_back(offset[i]);
        new_sizes.push_back(dsizes[i]);
        new_index.push_back(i);
        new_types.push_back(types[i]);
    }
}

// ----------------- read ---------------------
// read all
void RecordSchema::set_read(){
    default_read = true;
}

// read part
void RecordSchema::set_read(std::vector<int> read_index){
    clear_vector();
    default_read = false;
    for (auto const& i : read_index){
        new_offset.push_back(offset[i]);
        new_sizes.push_back(dsizes[i]);
        new_index.push_back(i);
        new_default_data.push_back(default_data[i]);
        new_types.push_back(types[i]);
    }
}

// 首先, set_read() 或者 set_write() 在文件顶端设置schma
// 
// ------------------ op ---------------------

void RecordSchema::write(BytePtr buff_ptr){
    // 读 bitmap
    Bitmap<int> new_fieldmap(fnum);
    memcpy(new_fieldmap.bits, buff_ptr, bits_size);
    BytePtr write_ptr;

    // std::cerr << "k1" << std::endl;
    // std::cerr << "default" << default_write << std::endl;

    if (default_write){
        for (size_t i = 0; i < offset.size(); i++){
            // std::cerr << "k2" << std::endl;
            write_ptr = buff_ptr + offset[i] / CHAR_STRIDE ;
            if (write_data[i].null) {
                new_fieldmap.set(index[i], false);
            } else {
                if (write_data[i].field_data_type == DataType::INT){  
                    memcpy(write_ptr, &write_data[i].intValue, dsizes[i]);
                } else if (write_data[i].field_data_type == DataType::FLOAT){
                    memcpy(write_ptr, &write_data[i].floatValue, dsizes[i]);
                } else {
                    memcpy(write_ptr, &write_data[i].varcharValue, dsizes[i]);
                }
                new_fieldmap.set(index[i], true);
            }
        }
    } else {
        for (size_t i = 0 ; i < new_offset.size() ; i++){
            write_ptr = buff_ptr + new_offset[i] / CHAR_STRIDE ;
            if (write_data[i].null) {
                new_fieldmap.set(new_index[i], false);
            } else {
                if (write_data[i].field_data_type == DataType::INT){  
                    memcpy(write_ptr, &write_data[i].intValue, new_sizes[i]);
                } else if (write_data[i].field_data_type == DataType::FLOAT){
                    memcpy(write_ptr, &write_data[i].floatValue, new_sizes[i]);
                } else {
                    memcpy(write_ptr, &write_data[i].varcharValue, new_sizes[i]);
                }
                new_fieldmap.set(new_index[i], true);
            }
        }
    }
    memcpy(buff_ptr, new_fieldmap.bits, bits_size);
}


void RecordSchema::read(BytePtr buff_ptr){
    // 读 bitmap
    memcpy(fieldmap.bits, buff_ptr, bits_size);
    BytePtr read_ptr;
    result_data.clear();
    if (default_read){
        for (size_t i = 0 ; i < offset.size() ; i++){
            read_ptr = buff_ptr + offset[i] / CHAR_STRIDE ;
            if (!fieldmap.get(index[i])){
                result_data.push_back(default_data[i]);
            }else{
                FieldData d;
                d.field_data_type = types[i];
                if (types[i] == DataType::INT){  
                    memcpy(&d.intValue, read_ptr, dsizes[i]);
                } else if (types[i] == DataType::FLOAT){
                    memcpy(&d.floatValue, read_ptr, dsizes[i]);
                } else {
                    memcpy(&d.varcharValue, read_ptr, dsizes[i]);
                    d.varcharValue[dsizes[i]] = '\0';
                }
                d.null = false;
                fieldmap.set(index[i], true);
                result_data.push_back(d);
            }
        }
    }else{
        for (size_t i = 0 ; i < new_offset.size() ; i++){
            read_ptr = buff_ptr + new_offset[i] / CHAR_STRIDE ;
            if (!fieldmap.get(new_index[i])){
                result_data.push_back(new_default_data[i]);
            }else{
                FieldData d;
                d.field_data_type = new_types[i];
                if ( new_types[i] == DataType::INT){  
                    memcpy(&d.intValue, read_ptr, new_sizes[i]);
                } else if ( new_types[i] == DataType::FLOAT){
                    memcpy(&d.floatValue, read_ptr, new_sizes[i]);
                } else {
                    memcpy(&d.varcharValue, read_ptr, new_sizes[i]);
                    d.varcharValue[new_sizes[i]] = '\0';
                }
                d.null = false;
                fieldmap.set(new_index[i], true);
                result_data.push_back(d);
            }
        }
    }
}

std::string RecordSchema::show_data(std::vector<FieldData> data){
    std::stringstream ss;
    bool first = true;
    for (auto const & d : data){
        if (first) {first = false; }
        else { ss << ","; }
        if (d.null){
            ss << "NULL";
        }else {
            if (d.field_data_type == DataType::INT){
                ss << d.intValue;
            } else if (d.field_data_type == DataType::FLOAT){
                ss << d.floatValue;
            } else {
                ss << d.varcharValue;
            }
        }
    }
    return ss.str();
}