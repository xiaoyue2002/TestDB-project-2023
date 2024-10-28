#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <sys/stat.h> 

#include "../Logger.hpp"
#include "DBManager.hpp"
#include "../table/Schema.hpp"
#include "../table/TableManager.hpp"
#include "../query/constrains.hpp"

/**
 * --init 
*/

int DBManager::init(){

    try { // check
        if (std::filesystem::exists(data_path) && std::filesystem::is_directory(data_path)) {
            for (const auto& entry : std::filesystem::directory_iterator(data_path)) {
                std::filesystem::remove_all(entry.path());
            }
        }
        return 0;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return -1;
    }
}


// ---------------- DATABASE -------------------
/**
 * Create a new database, which is a directory under ./data.
 * @param name : name of the database to create
*/
void DBManager::create_db(const std::string &name){
    std::string path = data_path + '/' + name;

    // check if the directory already exists
    if (std::filesystem::exists(path)){
        throw std::runtime_error("DATABASE " + name + "ALREADY EXISTS!");
    } else if (std::filesystem::create_directories(path)){
        std::cerr << "CREATED DATABASE " << name <<std::endl;
    } else {
        throw std::runtime_error("Error creating directory (create_db)! " + path);
    }
    // struct stat info;
    // if (stat(path.c_str(), &info) !=0){
    //     // Directory does not exist, create
    //     if (! std::filesystem::create_directories(path)){
    //         throw std::runtime_error("Error creating directory (create_db)!" + path);
    //     }
    // }else if (info.st_mode){
    //     throw std::runtime_error("DATABASE " + name + " ALREADY EXISTS!");
    // }
}

/**
 * Drop a database, and delete all the files in the directory.
 * @param db_name : name of the database to delete
*/
void DBManager::drop_db(const std::string &db_name){
    std::string path = data_path + '/' + db_name;

    // check if database exists
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("DATABASE " + db_name + " DOES NOT EXIST." );
    }

    try {
        std::filesystem::remove_all(path);
        // print screen
        if (!batch_mode){
            std::cout << "DROPPED DATABASE " << db_name << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Error deleting database: " + std::string(e.what()));
    }
}

/**
 * Show names of the existing databases.
*/
vector<string> DBManager::show_db(){
    std::vector<std::string> db_names;
    std::string path = data_path;
    
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory()) {
                db_names.push_back(entry.path().filename().string());
            }
        }
    }else{
        Logger::logError("Failed to open " + path);
    }
    
    // print screen
    std::cout<<"DATABASES"<<std::endl;
    for (auto const & name : db_names){
        std::cout << name << std::endl;
    }
    return db_names;
}

/*
 * 切换当前数据库
*/
void DBManager::use_db(const std::string & db_name){
    // std::cerr << "USING DB !" << std::endl;

    std::string ask_path = data_path + "/" + db_name;
    
    if (!(std::filesystem::exists(ask_path) && std::filesystem::is_directory(ask_path))) {
        throw std::runtime_error("DATABASE " + db_name + " DOES NOT EXIST.");    
    } else {
        if (is_using){
            close_database();
        }
        using_db_name = db_name;
        is_using = true;

        using_table.clear();

        load_database();

        // print screen 
        // if (!batch_mode){
            // std::cerr << "USING DATABSE " << db_name << std::endl;
        // }
    }
}


// ===== private =====
/*
 * Check is_using
*/
void DBManager::check_using(){
    if (!is_using){
        throw std::runtime_error("NO DATABASE BEING USED.");
    }
}

/*
 * 打开数据库时更新 using_table vector
*/
void DBManager::load_database(){
    check_using();

    std::vector<std::string> tb_names;
    std::string path = data_path + '/' + using_db_name;

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory()) {
                tb_names.push_back(entry.path().filename().string());
            }
        }
    }else{
        throw std::runtime_error("Failed to open (when loading database) : " + path);
    }
    
    // std::cerr << "LOAD DATABASE : ";
    for (auto const & name : tb_names){
        // std::cerr << name << " ";
        std::string tb_path = path + '/' + name;
        using_table[name] = TableManager(fm, bpm, name, tb_path);
        using_table[name].open();
    }
    // std::cerr << std::endl;
}

/*
 * 关闭数据库的时候调用 TableManager 的 close 函数, 会执行
 * 1. 写 meta file
 * 2. 使用fm关闭掉打开的文件
*/
void DBManager::close_database(){
    // std::cerr << "CLOSING !" << std::endl;
    for (auto& pair : using_table) {
        std::string key = pair.first;
        pair.second.close();
    }
}


// ------------------ TABLE ------------------------

/*
 * 创建表, 创建表的时候必须输入schema
*/
void DBManager::create_table(const std::string &tb_name, const Schema & schm){
    check_using();
    std::string path = data_path + "/" + using_db_name + "/" + tb_name;
    
    // check if the directory already exists
    // struct stat info;
    // if (stat(path.c_str(), &info) !=0){
    //     // Directory does not exist, create
    //     if (mkdir(path.c_str(), 0777) == -1){
    //         throw std::runtime_error("Error creating directory (create_table)!" + path);
    //     }
    // }else if (info.st_mode){
    //     throw std::runtime_error("TABLE" + tb_name +  "ALREADY EXISTS!");
    // }

    if (std::filesystem::exists(path)){
        throw std::runtime_error("DATABASE " + tb_name + "ALREADY EXISTS!");
    } else if (std::filesystem::create_directories(path)){
        std::cerr << "CREATED DATABASE " << tb_name <<std::endl;
    } else {
        throw std::runtime_error("Error creating directory (create_db)! " + path);
    }

    // create Table
    using_table[tb_name] = TableManager(fm, bpm, tb_name, schm, path);
    using_table[tb_name].open();
    // close_database();
    // load_database();

    // print screen
    if (!batch_mode){
        std::cout << "CREATED TABLE "<< tb_name << std::endl;
    }
}

/*
 * 展示数据库
*/
void DBManager::show_tables(){
    check_using();
    std::vector<std::string> tb_names;
    std::string path = data_path + '/' + using_db_name;

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory()) {
                tb_names.push_back(entry.path().filename().string());
            }
        }
    }else{
        Logger::logError("Failed to open " + path);
    }
    
    // print screen
    // std::cerr << "TABLES" << std::endl;
    std::cout << "TABLES" << std::endl;
    for (auto & name : tb_names){
        // std::cerr << name << std::endl;
        std::cout << name << std::endl;
    }
}

/*
 * 描述table
*/
void DBManager::describe_table(const std::string & tb_name){
    check_using();
    if (using_table.find(tb_name) != using_table.end()) {
        using_table[tb_name].describe_self();
    }else{
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }   
}

/*
 * 删除 table
*/
void DBManager::drop_table(const std::string & tb_name){
    check_using();
    std::string path = data_path + '/' + using_db_name + '/' + tb_name;

    // check if table exists
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }

    close_database();

    try {
        std::filesystem::remove_all(path);
        // print screen
        if (!batch_mode){
            std::cout << "DROPPED TABLE " << tb_name << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Error deleting table: " + std::string(e.what()));
    }

    load_database();
}

/*
 * 从文件加载
*/
int DBManager::load_from_file(const std::string filename, const std::string tb_name, const std::string divider){
    check_using();
    
    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }

    // 处理字符串
    std::string path = filename;
    if (!path.empty() && path.front() == '\'' && path.back() == '\'') {
        path = path.substr(1, path.length() - 2);
    }
    if (!path.empty() && path[0] == '/') {
        path = path.substr(1);
    }

    std::string div = divider;
    if (!div.empty() && div.front() == '\'' && div.back() == '\'') {
        div = div.substr(1, div.length() - 2);
    }
    
    // 打开文件
    std::ifstream infile(path);
    if (!infile.is_open()){
        throw std::runtime_error("Failed to Open " + path + " " + path);
    }

    // 按行读取
    std::string line;
    int count = 0;
    SlotID max_slot = using_table[tb_name].get_max_slot();
    // std::cerr << "get max slot : " << max_slot << std::endl;

    std::vector<std::vector<std::string>> batch;

    std::vector<std::string> fields;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string field;
        
        while (std::getline(ss, field, div[0])) {
            fields.push_back(field);
        }

        batch.push_back(fields);
        fields.clear();

        if (batch.size() == max_slot){
            using_table[tb_name].insert_batch_data(batch);
            batch.clear();
        }
        
        count += 1;
    }

    if (!batch.empty()){
        using_table[tb_name].insert_batch_data(batch);
    }

    // 把所有脏页写回
    bpm->close();

    // print screen
    std::cout << "rows" << std::endl;
    std::cout << count << std::endl;

    infile.close();

    return 0;
}   

/*
 * 插入一条数据
*/
void DBManager::insert_data(std::string tb_name, std::vector<std::vector<FieldData>> data_list){
    check_using();
    int print;

    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }else{
        // 检查外键和合法性
        // for (auto const & data : data_list){
        //     using_table[tb_name].check_data_valid()

        //     for (auto const & fk : using_table[tb_name].schema.foreign_key_cons){
        //         std::vector<int> insert_keys = using_table[tb_name].generate_foreign_keys(data, fk.field_name);
                
        //         std::string fk_table = fk.foreign_table;
        //         std::vector<std::string> fk_cols = fk.foreign_field;
        //         if (!using_table[fk_table].check_has(insert_keys, fk_cols)){
        //             std::cout << 
        //         }
        //     }
        // }

        for (auto const & data : data_list){
            print = using_table[tb_name].insert_data(data);    
        }
    }


    using_table[tb_name].save();
    if (print){
        std::cout << "rows" << std::endl;
        std::cout << data_list.size() << std::endl;
    }
}

/* query */
void DBManager::select(bool select_all, std::vector<std::string> columns, std::string table, std::vector<Constrain> cons){
    check_using();

    if (using_table.find(table) == using_table.end()) {
        throw std::runtime_error("TABLE" + table + "DOES NOT EXIST.");
    }
    // std::cerr << "all" << select_all ;
    using_table[table].select(select_all, columns, cons);
}

void DBManager::delete_data(std::string tb_name, std::vector<Constrain> cons){
    check_using();

    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }

    using_table[tb_name].delete_data(cons);
}

void DBManager::update_data(std::string tb_name, std::vector<std::string> columns, std::vector<FieldData> new_data, std::vector<Constrain> cons){
    check_using();

    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }

    // std::cerr << "update" << std::endl;
    using_table[tb_name].update_data(columns, new_data, cons);
}

void DBManager::join_select(std::vector<std::string> tables, std::vector<std::string> columns, std::vector<std::string> names, std::vector<Constrain> cons){
    // std::cerr << "Hello" << std::endl;
    check_using();
    // std::cerr << "Hello" << std::endl;

    for (auto const & name : names){
        if (using_table.find(name) == using_table.end()) {
            throw std::runtime_error("TABLE" + name + "DOES NOT EXIST.");
        }
    }


    // to select
    std::vector<std::string> table_1_get;
    std::vector<std::string> table_2_get;
    bool tb_first = true;
    for (size_t i = 0; i < tables.size(); i++){
        if (tb_first) tb_first = false;
        else std::cout << ",";
        if (tables[i] == names[0]){
            table_1_get.push_back(columns[i]);
        } else {
            table_2_get.push_back(columns[i]);
        }
        std::cout << columns[i];
    }
    std::cout << std::endl;


    std::string table_1 = names[0];
    std::string table_2 = names[1];

    // to compare
    std::unordered_map<std::string, std::vector<std::string>> map;
    // 提前把 bench map 找出来，减少遍历次数
    std::unordered_map<std::string, std::vector<Constrain>> bench_map;
    std::unordered_map<std::string, std::vector<std::string>> bench_index;
    for (auto const & constrain : cons){
        if (constrain.b_tb.size() == 0){ // value 
            map[constrain.tb_name].push_back(constrain.column_name);
            bench_map[constrain.tb_name].push_back(constrain);
            bench_index[constrain.tb_name].push_back(constrain.column_name);
        } else { // join
            map[constrain.tb_name].push_back(constrain.column_name);
            map[constrain.b_tb].push_back(constrain.b_column);
        }
    }

    // std::cerr << bench_map[table_1].size() << "bench" << std::endl;

    std::vector<FieldData> data_1_get;
    std::vector<FieldData> data_1_comp;
    std::vector<FieldData> data_2_get;
    std::vector<FieldData> data_2_comp;

    using_table[table_1].init_join();

    // select_ids, compare_ids, data_get, data_comp
    int pp = using_table[table_1].get_row(table_1_get, map[table_1], data_1_get, data_1_comp, bench_map[table_1], bench_index[table_1]);
    int count = 0; 
    while (pp != -1){
        using_table[table_2].init_join();
        while (using_table[table_2].get_row(table_2_get, map[table_2], data_2_get, data_2_comp, bench_map[table_2], bench_index[table_2]) != -1){
            std::vector<FieldData> rep_data_1_get = data_1_get;
            std::vector<FieldData> rep_data_1_comp = data_1_comp;

            std::vector<FieldData> rep_data_2_get = data_2_get;
            std::vector<FieldData> rep_data_2_comp = data_2_comp;

            bool all_true = true;
            for (auto & constrain : cons){
                bool res = true;
                
                if (!constrain.b_tb.empty()){
                    if (constrain.tb_name == table_1){
                        res = constrain.join_judge(rep_data_1_comp.front(), rep_data_2_comp.front());
                    } else {
                        res = constrain.join_judge(rep_data_2_comp.front(), rep_data_1_comp.front());
                    }
                    rep_data_1_comp.erase(rep_data_1_comp.begin());
                    rep_data_2_comp.erase(rep_data_2_comp.begin());
                } else {
                    if (constrain.tb_name == table_1){
                        rep_data_1_comp.erase(rep_data_1_comp.begin());
                    } else {
                        rep_data_2_comp.erase(rep_data_2_comp.begin());
                    }
                }

                if (!res) all_true = false;
            }

            bool first = true;
            if (all_true){
                count += 1;
                for (auto const & print_tb : tables){
                    if (first) first = false;
                    else std::cout << ",";

                    if (print_tb == table_1){
                        std::cout << rep_data_1_get.front().to_string();
                        rep_data_1_get.erase(rep_data_1_get.begin());
                    } else {
                        std::cout << rep_data_2_get.front().to_string();
                        rep_data_2_get.erase(rep_data_2_get.begin());
                    }
                }
                std::cout << std::endl;
            }
        }
        pp = using_table[table_1].get_row(table_1_get, map[table_1], data_1_get, data_1_comp, bench_map[table_1], bench_index[table_1]);
    }
    return;
}

void DBManager::add_index(std::string tb_name, std::string index_name, std::vector<std::string> column_names){
    check_using();
    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }

    using_table[tb_name].add_index(index_name, column_names);
}

void DBManager::drop_index(std::string tb_name, std::string index_name){
    check_using();
    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }
    using_table[tb_name].drop_index(index_name);
}

void DBManager::add_pk(std::string tb_name, std::vector<std::string> columns){
    check_using();
    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }
    using_table[tb_name].add_pk(columns);
}

void DBManager::drop_pk(std::string tb_name){
    check_using();
    if (using_table.find(tb_name) == using_table.end()) {
        throw std::runtime_error("TABLE" + tb_name + "DOES NOT EXIST.");
    }
    using_table[tb_name].drop_pk();
}