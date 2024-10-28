#pragma once
#include <vector>
#include <string>
#include <climits>
#include <fstream>
#include "../table/Schema.hpp"
#include "../bitmap/bitmap.hpp"
#include "../defines.h"
#include "RecordSchema.hpp"



/*
 * Operation Schema of a insert / update / get operation.
 * OPSchema is s subset of RecordSchema.
 * We may only read part of the fields
*/
struct OPSchema{
    // bitmap -> this will be same with RecordSchema
    size_t fnum;
    size_t bits_size;
    std::vector<int> index;
    std::vector<size_t> dsizes;
    std::vector<size_t> offset;
    std::vector<DataType> types;
    std::vector<FieldData> default_data;

    // for writing and updating
    std::vector<FieldData> new_data;

    // for reading data
    std::vector<FieldData> result_data;
    
    OPSchema(){}
    OPSchema(const OPSchema & other){
        fnum = other.fnum;
        bits_size = other.bits_size;
        index = other.index;
        dsizes = other.dsizes;
        offset = other.offset;
        types = other.types;
        default_data = other.default_data;
    
        new_data = other.new_data;
        result_data = other.result_data;
    }
    // for insert, opschema = recordschema 
    OPSchema(const RecordSchema & other){
        fnum = other.fnum;
        bits_size = other.bits_size;
        index = other.index;
        dsizes = other.dsizes;
        offset = other.offset;
        types = other.types;
        default_data = other.default_data;
    }

    std::string tostring_data(std::vector<FieldData> show_data);

    // inx : fields of interest
    void set_part_fields(const std::vector<int> idx, const RecordSchema & record_schema){
        for (auto const & i : idx){
            index.push_back(record_schema.index[i]);
            dsizes.push_back(record_schema.dsizes[i]);
            offset.push_back(record_schema.offset[i]);
            types.push_back(record_schema.types[i]);
            default_data.push_back(record_schema.default_data[i]);
        }
    }

    bool equal_new_data(std::vector<FieldData> comp){
        bool res;
        for (size_t i = 0 ;i < index.size(); i++){
            if (types[i] == DataType::INT){
                res = (new_data[i].intValue == comp[i].intValue);
            } else if (types[i] == DataType::FLOAT){
                res = (new_data[i].floatValue == comp[i].floatValue);
            } else if (types[i] == DataType::VARCHAR){
                res = (new_data[i].varcharValue == comp[i].varcharValue);
            }
            if (!res) return false;
        }   
        return true;
    }

    void read(BytePtr buff_ptr);
    void write(BytePtr buff_ptr) const ;
};