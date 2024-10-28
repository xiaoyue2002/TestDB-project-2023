#include <vector>
#include <cstddef>
#include "Compare.hpp"

/* if key1 >= keys 2 , return true */
// key1 >= key2 -> key1的值里如果有比key2小的，就不行
bool compare_ge(std::vector<int> keys1, std::vector<int> keys2){
    for (size_t i = 0; i < keys1.size(); i++){
        if (keys1[i] > keys2[i]) {
            return true;
        } else if (keys1[i] < keys2[i]){
            return false;
        }
    }
    return true;
}

bool QuerySchema::compare_int(int load, int tgt, QueryType query){
        if (query == QueryType::EQ){
            return load == tgt;
        }else if (query == QueryType::NEQ){
            return load != tgt;
        }else if (query == QueryType::GREATER){
            return load > tgt;
        }else if (query == QueryType::LESS){
            return load < tgt;
        }else if (query == QueryType::GE){
            return load >= tgt;
        }else if (query == QueryType::LE){
            return load <= tgt;
        }else{
            throw std::runtime_error("Unsupported compare");
        }
}
bool QuerySchema::compare_float(double load, double tgt, QueryType query){
        if (query == QueryType::EQ){
            return load == tgt;
        }else if (query == QueryType::NEQ){
            return load != tgt;
        }else if (query == QueryType::GREATER){
            return load > tgt;
        }else if (query == QueryType::LESS){
            return load < tgt;
        }else if (query == QueryType::GE){
            return load >= tgt;
        }else if (query == QueryType::LE){
            return load <= tgt;
        }else{
            throw std::runtime_error("Unsupported compare");
        }
}
bool QuerySchema::compare_varchar(std::string load, std::string tgt, QueryType query){
        if (query == QueryType::EQ){
            return load == tgt;
        }else if (query == QueryType::NEQ){
            return load != tgt;
        }else if (query == QueryType::GREATER){
            return load > tgt;
        }else if (query == QueryType::LESS){
            return load < tgt;
        }else if (query == QueryType::GE){
            return load >= tgt;
        }else if (query == QueryType::LE){
            return load <= tgt;
        }else{
            throw std::runtime_error("Unsupported compare");
        }
}

bool QuerySchema::compare_data(std::vector<FieldData> load){
    bool check;
    for (size_t i = 0 ; i < load.size() ; i++){
        if (data_types[i] == DataType::INT){
            check = compare_int(load[i].intValue, tgt_datas[i].intValue, query_types[i]);
        } else if (data_types[i] == DataType::FLOAT){
            check = compare_float(load[i].floatValue, tgt_datas[i].floatValue, query_types[i]);
        } else {
            check = compare_varchar(std::string(load[i].varcharValue), std::string(tgt_datas[i].varcharValue), query_types[i]);
        }
        if (!check){
            return false;
        }
    }
    return true;
}