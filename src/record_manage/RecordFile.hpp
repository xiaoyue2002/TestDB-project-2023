#pragma once
#include "../table/Schema.hpp"
#include "RecordSchema.hpp"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../filesystem/fileio/FileManager.h" 
#include <vector>
#include "../query/constrains.hpp"
#include <string>
#include "../index/IndexSchema.hpp"

class RecordFile{
public:
    // 
    int tot_num;
    int page_num;
    PageID page_head;
    PageID page_tail;
    PageID empty_head;
    PageID empty_tail;

    std::string meta_file ;
    std::string rec_file;

    // -- RecordSchema & data_schema -- 
    RecordSchema record_schema;
    Schema data_schema;
    RecordPageSchema page_schema;
    // -- end --

    /* file manager */
    int file_id;
    FileManager * fm;
    BufPageManager * bpm;

    bool opened;

    PageID join_now_page;
    std::vector<std::vector<FieldData>> temp_get_list;
    std::vector<std::vector<FieldData>> temp_comp_list;

public:

    RecordFile(){ opened = false;}

    void read_meta();
    void create_meta();
    void write_meta();

    void set_schema(Schema schm);
    void set_dir(std::string dirname);
    void set_bpm(FileManager * filem, BufPageManager * bufm){
        fm = filem; bpm = bufm;
    }

    // open 会打开文件注册号
    void open(){ // OPEN !
        if (fm->openFile(rec_file.c_str(), file_id)){
            opened = true;
            // std::cerr << "fileid " << file_id << " rec_file "<< rec_file << std::endl;
        } else {
            throw std::runtime_error("FAIL TO OPEN");
        }
    }

    // close只是关闭文件，不能save back
    void close(){ // CLOSE !
        if (opened){
            bpm->close();
            fm->closeFile(file_id);
        }
    }

    // data
    void insert_data(std::vector<FieldData> data);
    std::vector<RID> insert_batch_data(std::vector<std::vector<FieldData>> );

    void select(std::vector<int> select_ids, std::vector<int> compare_ids, std::vector<Constrain> cons);
    void delete_data(std::vector<int> comp_ids, std::vector<Constrain> cons);
    void update_data(std::vector<int> set_ids, std::vector<FieldData> new_data,  std::vector<int> compare_ids, std::vector<Constrain> cons);

    void init_join();
    int get_row(std::vector<int> sel_ids, std::vector<int> comp_ids, std::vector<FieldData>& data_get, std::vector<FieldData>& data_comp, std::vector<Constrain> bench, std::vector<int> bench_index);

    bool dup_pk_check(std::vector<int> data);
    bool check_unique(std::vector<int> kid);
};
