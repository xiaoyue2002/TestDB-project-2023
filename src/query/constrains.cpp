#include "constrains.hpp"
#include "../defines.h"
#include <string>
#include "../table/Schema.hpp"

void Constrain::print(){
    std::cerr << tb_name << "." << column_name;

    if (query_op == QueryType::EQ){
        std::cerr << " == ";
    } else if (query_op == QueryType::NEQ){
        std::cerr << " != ";
    } else if (query_op == QueryType::GE){
        std::cerr << " >= ";
    } else if (query_op == QueryType::GREATER){
        std::cerr << " > ";
    } else if (query_op == QueryType::LE){
        std::cerr << " <= ";
    } else if (query_op == QueryType::LESS){
        std::cerr << " < ";
    }   

    if (b_tb.size() == 0){
        std::cerr << bench_data.to_string();
    } else {
        std::cerr << b_tb << "." << b_column;
    }
}

bool Constrain::bench_judge(FieldData data){
    if (bench_data.field_data_type == DataType::INT){
        return compare_int(data.intValue, bench_data.intValue, query_op);
    } else if (bench_data.field_data_type == DataType::FLOAT){
        return compare_float(data.floatValue, bench_data.floatValue, query_op);
    } else {
        return compare_varchar(data.varcharValue, bench_data.varcharValue, query_op);
    }
}

bool Constrain::join_judge(FieldData A, FieldData B){
    if (A.field_data_type == DataType::INT){
        return compare_int(A.intValue, B.intValue, query_op);
    } else if (A.field_data_type == DataType::FLOAT){
        return compare_float(A.floatValue, B.floatValue, query_op);
    } else {
        return compare_varchar(A.varcharValue, B.varcharValue, query_op);
    }
}


bool Constrain::compare_int(int load, int tgt, QueryType query){
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
bool Constrain::compare_float(double load, double tgt, QueryType query){
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

bool Constrain::compare_varchar(std::string load, std::string tgt, QueryType query){
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
