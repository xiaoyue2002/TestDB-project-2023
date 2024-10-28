#include <vector>
#include <string>
#include <sstream>
#include "../defines.h"
#include "RecordSlot.hpp"
#include "../Logger.hpp"

std::string OPSchema::tostring_data(std::vector<FieldData> show_data) {
    std::stringstream ss;
    bool first = true;
    for (size_t i = 0; i < dsizes.size(); i++){
        if (first) { first = false;}
        else {ss << ",";}

        if (show_data[i].null){
            ss << "NULL";
        }else{
            if(types[i] == DataType::INT){
                ss << show_data[i].intValue;
            }else if (types[i] == DataType::FLOAT){
                ss << show_data[i].floatValue;
            }else{
                ss << show_data[i].varcharValue;
            }
        }
    }
    return ss.str();
}

void OPSchema::read(BytePtr buff_ptr){
    result_data.clear();
    // bitmap
    // Logger::logError("OpSchema : read");
    Bitmap<int> fieldmap(fnum);
    // Logger::logError("fnum " + std::to_string(fnum));
    // std::cout << std::hex << (uintptr_t)buff_ptr << std::endl;
    // Logger::logError(std::to_string(bits_size));
    // fieldmap.show();
    memcpy(fieldmap.bits, buff_ptr, bits_size);
    // fieldmap.show();
    // Logger::logError("dsizes " + std::to_string(dsizes.size()));
    // Logger::logError("default " + std::to_string(default_data.size()));
    // Logger::logError("index " + std::to_string(index.size()));
    // Logger::logError("types " + std::to_string(types.size()));
    // Logger::logError("offset " + std::to_string(offset.size()));
    for (size_t i = 0; i < dsizes.size(); i++){
        int idx = index[i];
        size_t dsize = dsizes[i];
        DataType dtype = types[i];
        // Logger::logError("offset : " + std::to_string(offset[i]));
        // Logger::logError("size : " + std::to_string(dsizes[i]));
        BytePtr reader = buff_ptr + offset[i] / CHAR_STRIDE;
    
        // Logger::logError(fieldmap)

        if (!fieldmap.get(idx)){
            result_data.push_back(default_data[i]);
        }else{
            FieldData d;
            if (dtype == DataType::INT){
                memcpy(&d.intValue, reader, dsize);
            }else if (dtype == DataType::FLOAT){
                memcpy(&d.floatValue, reader, dsize);
            }else {
                memcpy(&d.varcharValue, reader, dsize);
                d.varcharValue[dsize-1] = '\0';
            }
            d.field_data_type = dtype;
            d.null = false;
            result_data.push_back(d);
        }
    }
}

void OPSchema::write(BytePtr buff_ptr) const {
    // Logger::logError("writing");
    Bitmap<int> fieldmap(fnum);
    // std::cout << std::hex << (uintptr_t) buff_ptr << std::endl;
    // 先读
    memcpy(fieldmap.bits, buff_ptr, bits_size);
    // fieldmap.show();
    for (size_t i = 0 ; i < dsizes.size(); i++){
        int idx = index[i];
        size_t dsize = dsizes[i];
        DataType dtype = types[i];
        BytePtr reader = buff_ptr + offset[i] / CHAR_STRIDE;

        fieldmap.set(idx, true);
        if (dtype == DataType::INT){
            memcpy(reader, &new_data[i].intValue, dsize);
        }else if (dtype == DataType::FLOAT){
            memcpy(reader, &new_data[i].floatValue, dsize);
        }else {
            memcpy(reader, &new_data[i].varcharValue, dsize);
        }
    }
    // 写
    // fieldmap.show();
    // Logger::logError(std::to_string(bits_size));
    memcpy(buff_ptr, fieldmap.bits, bits_size);
}