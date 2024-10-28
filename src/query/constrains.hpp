#pragma once
#include <vector>
#include <string>
#include "../defines.h"
#include "../table/Schema.hpp"

// enum class QueryType {EQ = 0, NEQ = 1, 
// GREATER = 2,  LESS = 3, GE = 4, LE = 5};

struct Constrain{
    std::string tb_name;
    std::string column_name;

    QueryType query_op; // > < = >= <> ...
   
    // value
    FieldData bench_data; 

    // column
    std::string b_tb;
    std::string b_column;

    Constrain(){}
    Constrain(const Constrain & other){
        tb_name = other.tb_name;
        column_name = other.column_name;
        query_op = other.query_op;
        bench_data = other.bench_data;
        b_tb = other.b_tb;
        b_column = other.b_column;
    }

    void print();

    bool join_judge(FieldData A, FieldData B);

    bool bench_judge(FieldData data);

    bool compare_int(int load, int tgt, QueryType query);
    bool compare_float(double load, double tgt, QueryType query);
    bool compare_varchar(std::string load, std::string tgt, QueryType query);
    
};

