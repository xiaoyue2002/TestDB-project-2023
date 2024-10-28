#pragma once
#include <stdexcept>
#include <vector>
#include "../defines.h"
#include "../table/Schema.hpp"

bool compare_ge(std::vector<int> keys1, std::vector<int> key2);


struct QuerySchema{
    // QueryType {EQ = 0, NEQ = 1, GREATER = 2,  LESS = 3, GE = 4, LE = 5};

    std::vector<QueryType> query_types;
    std::vector<int> tgt_idxs;
    std::vector<FieldData> tgt_datas;
    std::vector<DataType> data_types;

    std::vector<int> get_data;

    QuerySchema(std::vector<QueryType> qt, std::vector<int> tids, std::vector<FieldData> tdatas){
        query_types = qt; tgt_idxs = tids; tgt_datas = tdatas;
    }

    bool compare_float(double load, double tgt, QueryType query);
    bool compare_varchar(std::string load, std::string tgt, QueryType query);
    bool compare_int(int load, int tgt, QueryType query);

    bool compare_data(std::vector<FieldData> load);
};