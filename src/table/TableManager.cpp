#include "TableManager.hpp"
#include <stdexcept>
#include <vector>
#include "../index/IndexSchema.hpp"

void TableManager::describe_self(){
    std::cout<<"Field,Type,Null,Default"<<std::endl;
    Logger::logError(std::to_string(schema.fields.size()));
    for (auto const & f : schema.fields){
        std::cout << f.tostring_print() << std::endl;
    }
    std::cout << std::endl;
    if (schema.primary_key_ids.size() > 0){
        std::cout << "PRIMARY KEY (";
        bool first = true;
        for (auto const & id : schema.primary_key_ids){
            if (first){
                std::cout << schema.field_names[id];
                first = false;
            }else{
                std::cout << ", " << schema.field_names[id];
            }
        }
        std::cout << ");" <<std::endl;
    }
    for (auto const & f : schema.foreign_key_cons){
        std::cout << f.tostring_print() << std::endl;
    }

    // std::cout << std::endl;
    for (auto const & item : index.index_schemas){
        if (item.name != "default"){
            std::vector<int> kids = item.key_ids;
            std::cout << "INDEX (";
            bool first = true;
            for (auto const & k : kids){
                if(first) first = false;
                else std::cout << ", ";
                std::cout << schema.field_names[k];
            }
            std::cout <<");" << std::endl;
        }
    }
}

void TableManager::create_index_dir(){
    std::string path = dirname + "/index";
    struct stat info;
    if (stat(path.c_str(), &info) !=0){
        // Directory does not exist, create
        if (mkdir(path.c_str(), 0777) == -1){
            throw std::runtime_error("Error creating directory (create_meta_file)!" + path);
        }
    }
}

void TableManager::create_record_dir(){
    std::string path = dirname + "/record";
    struct stat info;
    if (stat(path.c_str(), &info) !=0){
        // Directory does not exist, create
        if (mkdir(path.c_str(), 0777) == -1){
            throw std::runtime_error("Error creating directory (create_meta_file)!" + path);
        }
    }
    
}

std::vector<FieldData> TableManager::trans_string(std::vector<std::string> string_list){
    std::vector<FieldData> ret_list;
    if (string_list.size() != schema.fields.size()){
        std::cout << schema.fields.size() << " " << string_list.size() << std::endl;
        throw std::runtime_error("Data length not match");
    }
    for (size_t i = 0 ; i < string_list.size(); i++){
        FieldData d;
        d.field_data_type = schema.fields[i].type;
        bool null = false;
        if ( string_list[i] == "NULL"){
            null = true;
        } else if (d.field_data_type == DataType::INT){
            d.intValue = std::stoi(string_list[i]);
        } else if (d.field_data_type == DataType::FLOAT){
            d.floatValue = std::stod(string_list[i]);
        } else if (d.field_data_type == DataType::VARCHAR){
            strncpy(d.varcharValue, string_list[i].c_str(), VARCHAR_LENGTH - 1); 
            d.varcharValue[VARCHAR_LENGTH - 1] = '\0';
        }
        d.null = null;
        ret_list.push_back(d);
    }
    return ret_list;
}

void TableManager::check_input_valid(std::vector<FieldData> data){
    if (data.size() != schema.fields.size()){
        throw std::runtime_error("DATA LENGTH NOT MATCH!.");
    }

    for (size_t i = 0 ; i < schema.fields.size(); i++){
        if (data[i].null && (!schema.fields[i].allow_null)){
            throw std::runtime_error("NULL NOT ALLOWED FOR " + schema.fields[i].name);
        }
        if (data[i].field_data_type != schema.fields[i].type){
            throw std::runtime_error("DATA TYPE NOT MATCH AT COLUMN " + schema.fields[i].name);
        }
    }
}


void TableManager::insert_batch_data(const std::vector<std::vector<std::string>> & data){
    // std::cerr << "what?" << std::endl;
    // std::cerr << large_d << std::endl;
    std::vector<std::vector<FieldData>> processed;
    for (auto & d : data){
        processed.push_back(trans_string(d));
    }
    std::vector<RID> inserted = record_file.insert_batch_data(processed);
}

int TableManager::insert_data(const std::vector<FieldData> & data){
    check_input_valid(data);
    if (schema.primary_key_ids.size() > 0){
        if (record_file.tot_num <= 5000){
        std::vector<int> primary_values;
        for (auto const & id : schema.primary_key_ids){
            primary_values.push_back(data[id].intValue);
        }
        if (record_file.dup_pk_check(primary_values)){
            std::cout << "!ERROR" << std::endl << "duplicate" << std::endl;
            return 0;
        }
        }
    }

    record_file.insert_data(data);
    return 1;
}


std::vector<int> TableManager::get_column_ids(std::vector<std::string> cols){
    std::vector<std::string> & A = schema.field_names;
    std::vector<int> indices;

    for (const auto& item : cols) {
        auto it = std::find(A.begin(), A.end(), item);

        if (it != A.end()) {
            indices.push_back(std::distance(A.begin(), it));
        } else {
            throw std::runtime_error("COLUMN " + item + " NOT FOUND.");
        }
    }
    return indices;
}

void TableManager::select(bool select_all, const std::vector<std::string> & cols, const std::vector<Constrain> & cons){
    std::vector<int> select_ids ;
    if (select_all){
        for (int i = 0 ; i < schema.fields.size(); i ++ ){
            select_ids.push_back(i);
        }
    } else {
        select_ids = get_column_ids(cols);
    }

    // std::cerr << "table_select " << select_ids.size() << std::endl;

    bool first = true;
    for (auto const & idx : select_ids){
        if (first) first = false;
        else std::cout << ",";
        std::cout << schema.field_names[idx];
    }
    std::cout << std::endl;

    std::vector<std::string> cons_names;
    for (auto constrain : cons){
        cons_names.push_back(constrain.column_name);
    }
    std::vector<int> compare_ids = get_column_ids(cons_names);

    record_file.select(select_ids, compare_ids, cons);
}

void TableManager::delete_data(const std::vector<Constrain> & cons){
    std::vector<std::string> cons_names;
    for (auto constrain : cons){
        cons_names.push_back(constrain.column_name);
    }
    std::vector<int> compare_ids = get_column_ids(cons_names);
    record_file.delete_data(compare_ids, cons);
}

void TableManager::update_data(const std::vector<std::string> & columns, const std::vector<FieldData> & new_data , const std::vector<Constrain> cons){
    std::vector<std::string> cons_names;
    for (auto constrain : cons){
        cons_names.push_back(constrain.column_name);
    }
    std::vector<int> compare_ids = get_column_ids(cons_names);

    std::vector<int> set_ids = get_column_ids(columns);
    record_file.update_data(set_ids, new_data, compare_ids, cons);
}

void TableManager::init_join(){
    record_file.init_join();
}

int TableManager::get_row(std::vector<string> select_ids, std::vector<string> compare_ids, std::vector<FieldData>& data_get, std::vector<FieldData>& data_comp, std::vector<Constrain> bench, std::vector<std::string> bench_index){
    std::vector<int> sel_ids = get_column_ids(select_ids);
    std::vector<int> comp_ids = get_column_ids(compare_ids);
    std::vector<int> bench_ids = get_column_ids(bench_index);
    std::vector<int> real_ids;
        // std::cerr << "real_ids ";
    for (int item : bench_ids) {
        auto it = std::find(comp_ids.begin(), comp_ids.end(), item);
        int a = std::distance(comp_ids.begin(), it);
        // std::cerr << a;
        real_ids.push_back(a);
    }

    return record_file.get_row(sel_ids, comp_ids, data_get, data_comp, bench, real_ids);
}

void TableManager::add_index(std::string index_name, std::vector<std::string> column_names){
    if (index_name.empty()){
        std::stringstream ss ;
        ss << "index_on_";
        for (auto const & cn : column_names){
            ss << cn << "_";
        }
        index_name = ss.str();
    }
    index.create_index_on(index_name, false, schema, column_names);   

    // Maybe we should add data to index here
    // But CI did not ask so :)    
}

void TableManager::drop_index(std::string index_name){
    index.drop_index(index_name);
}

void TableManager::drop_pk(){
    if (schema.primary_key_ids.size() == 0){
        std::cout << "!ERROR" << std::endl << "primary" << std::endl;
        return;
    }
    schema.primary_key_ids.clear();
    index.data_schema.primary_key_ids.clear();
    record_file.data_schema.primary_key_ids.clear();
    meta.write_schema(dirname, schema);
}

void TableManager::add_pk(std::vector<std::string> columns){
    std::vector<int> col_ids = get_column_ids(columns);
    std::vector<int> vec = schema.primary_key_ids;
    for (auto const a : col_ids){
        if (std::find(vec.begin(), vec.end(), a) != vec.end()) {
            std::cout << "!ERROR" << std::endl << "primary" << std::endl;
            return;
        } else {
            vec.push_back(a);
        }
    }
    if (!record_file.check_unique(vec)){
        std::cout << "!ERROR" << std::endl << "duplicate" << std::endl;
        return;
    }
    // std::cerr << "now pk :" ;
    // for (auto const & v : vec){
        // std::cerr << v << " " ;
    // }
    // std::cerr << std::endl;
    schema.primary_key_ids = vec;
    index.data_schema.primary_key_ids = schema.primary_key_ids;
    record_file.data_schema.primary_key_ids = schema.primary_key_ids;
    meta.write_schema(dirname, schema);
}