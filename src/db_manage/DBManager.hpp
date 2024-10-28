/*
    DDL (Data Definition Language) provides the ability to define, 
    create and modify database objects such as tables, views, indexes, 
    and users.
    DML (Data Manipulation Language) allows for manipulating data in
    a database, such as inserting, updating, and deleting records.

*/
/*
    DBManager 是数据库管理的顶层模块
    支持: 数据库的增删，数据表的增删改

    TODO:
        1. 与前端交互的工作之后会开发新的模块来做，因为还需要处理输入之类的, 前端模块的工作依赖dbmanager提供的借口
        2. 也许dbmanager还会支持数据库的查询，但是这个我们之后再处理
*/
#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <unordered_map>
#include "../table/Schema.hpp"
#include "../table/TableManager.hpp"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../filesystem/fileio/FileManager.h" 
#include "../query/constrains.hpp"


class DBManager{
private:

    // 数据文件夹
    std::string data_path;

    // buffer manager
    FileManager * fm ;
    BufPageManager * bpm ;

    // 输出模式
    bool batch_mode ; 

    // use_db 管理
    bool is_using;
    std::string using_db_name;
    void check_using();
   
    std::unordered_map<std::string, TableManager> using_table;

    /* Functions */

    // 打开和关闭数据库, 修改using_db_name和using_table, 关闭和打开文件
    void load_database();
    void close_database();

public:
    // bool is_using;
    // std::string using_db_name;

    DBManager(bool batchFlag): batch_mode(batchFlag){
        // 解析/data路径
        char result[PATH_MAX];
        readlink("/proc/self/exe", result, PATH_MAX);
        std::string now_path = std::string(result);
        // std::cerr << "now_path" << now_path << std::endl;
        
        std::string marker = "dbs-project-20";
        size_t pos = now_path.find(marker);

        if (pos != std::string::npos) {
            // 找到了子字符串，删除它之后的所有内容
            now_path.erase(pos + marker.size());
        }

        is_using = false;
        data_path = now_path + "/data";
        data_path = "./data";
        // std::cerr << "data_path" << data_path << std::endl;

        // create buffer manager
        fm = new FileManager();
        bpm = new BufPageManager(fm);
    };

    ~DBManager(){
        delete fm;  fm = nullptr;
        delete bpm; bpm = nullptr;
    }

    /*
     * --init 启动, 初始化数据库, 删除数据文件夹里的数据
    */
    int init();

    void close(){
        close_database();
    }
    
    // manage databases
    void create_db(const std::string &db_name);
    void drop_db(const std::string &db_name);
    std::vector<std::string> show_db();
    void use_db(const std::string &db_name);
    
    // manage the using database
    void create_table(const std::string &tb_name, const Schema & schm);
    void show_tables();
    void show_indexes();
    void drop_table(const std::string &tb_name);
    void describe_table(const std::string &tb_name);

    // load data
    int load_from_file(const std::string filename, const std::string tb_name, const std::string divider);
    void insert_data(std::string tb_name, std::vector<std::vector<FieldData>> data_list);
    
    // query
    void select(bool, std::vector<std::string> column, std::string table, std::vector<Constrain> cons);
    void delete_data(std::string tb_name, std::vector<Constrain> cons);
    void update_data(std::string tb_name, std::vector<std::string> colums, std::vector<FieldData> new_data, std::vector<Constrain> cons);
    void join_select(std::vector<std::string> tables, std::vector<std::string> columns, std::vector<std::string> names, std::vector<Constrain> cons);

    // index
    void add_index(std::string tb_name, std::string index_name, std::vector<std::string> column_name);
    void drop_index(std::string tb_name, std::string index_name);

    void drop_pk(std::string tb_name);
    void add_pk(std::string tb_name, std::vector<std::string> columns);

    bool get_is_using(){return is_using;};
    std::string get_using_db(){return using_db_name;};
};