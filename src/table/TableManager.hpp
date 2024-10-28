#pragma once
#include <string>
#include "Schema.hpp"
#include "MetaFile.hpp"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../filesystem/fileio/FileManager.h" 
#include "../index/IndexManager.hpp"
#include "../record_manage/RecordFile.hpp"
#include "../query/constrains.hpp"
#include "../index/IndexSchema.hpp"

class TableManager{
    std::string tb_name;
    RecordSchema record_schema;

    // index 
    IndexManager index; 
    // meta
    MetaFileManager meta;
    // record
    RecordFile record_file;

    std::string dirname;

    Schema schema;
public:
    

    TableManager(){}
    // Called when loading a existing table.
    TableManager(FileManager * filem, BufPageManager * bufpm, const std::string & name, const std::string & dir){
        // large_d = false;
        // std::cerr << " LOADING... " << name << std::endl;
        tb_name = name;
        dirname = dir;
        schema = meta.load_schema(dirname);
        record_schema = RecordSchema(schema.fields);

        // record_init
        record_file.set_dir(dirname);
        record_file.set_schema(schema);
        record_file.set_bpm(filem, bufpm);
        record_file.read_meta();

        // index init
        index.set_dir(dirname);
        index.set_schema(schema);
        index.set_bpm(filem, bufpm);
        index.read(dirname); 
    };
    // Called when creating a new table.
    TableManager(FileManager * filem, BufPageManager * bufpm, const std::string & name, const Schema & schm, const std::string & dir){
        // std::cerr << " CREATING... " << name << std::endl;
    
        tb_name = name;
        dirname = dir;
        schema = schm;
        // Logger::logError("debug");
        // Logger::logError(std::to_string(schm.fields.size()));
        record_schema = RecordSchema(schm.fields);

        // meta create
        meta.create_meta_file(dirname);
        meta.write_schema(dirname, schema);

        // record
        create_record_dir();
        std::string rec_filename = dirname + "/record/data.db";
        // std::cerr << "CREATING!" << std::endl;
        filem->createFile(rec_filename.c_str());
        record_file.set_dir(dirname);
        record_file.set_schema(schema);
        record_file.set_bpm(filem, bufpm);

        record_file.create_meta();
        record_file.write_meta();

        // index init
        create_index_dir();
        index.set_dir(dirname);
        index.set_schema(schema);
        index.set_bpm(filem, bufpm);

        if (!schema.primary_key_ids.empty())
            index.create_auto_index(schema);
        index.write(dirname);
        // std::cerr << "end" << std::endl;
    }

    SlotID get_max_slot(){
        return record_file.page_schema.max_slot;
    }

    /* Open and Close */
    void open(){ 
        record_file.open();
    }
    void close(){ 
        record_file.close(); 
    }
    void save(){
    }

    /* DESC Table */
    void describe_self();

    int insert_data(const std::vector<FieldData> & data);

    void insert_batch_data(const std::vector<std::vector<std::string>> & data);

    std::vector<FieldData> trans_string(std::vector<std::string> string_list);

    void create_index_dir();
    void create_record_dir();

    std::vector<int> get_column_ids(std::vector<std::string> cols);
    void select(bool , const std::vector<std::string> &  cols, const std::vector<Constrain> & cons);
    void delete_data(const std::vector<Constrain> & cons);
    void update_data(const std::vector<std::string> & columns, const std::vector<FieldData> & new_data , const std::vector<Constrain> cons);

    void init_join();
    int get_row(std::vector<string> select_ids, std::vector<string> comp_ids, std::vector<FieldData>& data_get, std::vector<FieldData>& data_comp, std::vector<Constrain> bench, std::vector<std::string> bench_index);

    /* Index */
    void add_index(std::string index_name, std::vector<std::string> column_names);
    void drop_index(std::string index_name);

    void drop_pk();

    void check_input_valid(std::vector<FieldData> data);
    void add_pk(std::vector<std::string> columns);
};