#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "IndexFile.hpp"
#include "IndexSchema.hpp"
#include "../table/Schema.hpp"
#include "../record_manage/RecordSlot.hpp"
#include "../defines.h"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../filesystem/fileio/FileManager.h" 


class IndexManager{
public:
    /* index file schemas */
    std::string index_dir; // index 文件夹
    std::string meta_dir;
    std::vector<IndexInfo> index_infos; 
    std::vector<IndexSchema> index_schemas;
    
    /* files */
    std::vector<IndexFile> index_files;

    /* schema */
    Schema data_schema;

    /* file manager */
    FileManager * fm;
    BufPageManager * bpm;

    /* Functions */

    // Meta file
    void write_file(const IndexInfo & , const IndexSchema & , std::ofstream & outFile);
    void read_file(std::ifstream & inFile);
    
    // Open & Close
    void create_file(const std::string);
    void open_file(const std::string, IndexSchema ischm, IndexInfo iinfo);

    bool opened;    

public:

    IndexManager(){ opened = false;};

    /* Set */
    void set_dir(std::string table_dir){
        index_dir = table_dir + "/index";
        meta_dir = table_dir ; 
    }

    void set_bpm(FileManager * filem, BufPageManager * bufm){
        fm = filem; bpm = bufm;
    }

    void set_schema(Schema shcm){
        data_schema = shcm;
    }

    /* insert data */
    void insert_data(const std::vector<FieldData> new_data, const RID & rid){
        if (!opened){
            open(); 
        }
        Logger::logError("finised opening");
        opened = true;
        // check_insert_valid(new_data);

        Logger::logError(std::to_string(index_files.size()));
        for (size_t i = 0 ; i < index_files.size(); i++){
            index_files[i].insert_data(new_data, rid);

            index_infos[i].tot_num = index_files[i].tot_num;
            index_infos[i].page_num = index_files[i].page_num;
            index_infos[i].root = index_files[i].root;
            index_infos[i].data_head = index_files[i].data_head;
        }
        // bpm->close();
        write(meta_dir);
    }

    /* Create Index */
    void create_auto_index(const Schema & table_schema );
    void create_index_on(std::string, bool, const Schema & table_schema , const std::vector<std::string> & fields);

    /* Meta File */
    void write(const std::string metadir);
    void read(const std::string metadir);

    /* Open and Close */
    void open();
    void close();

    void drop_index(std::string index_name);
};

