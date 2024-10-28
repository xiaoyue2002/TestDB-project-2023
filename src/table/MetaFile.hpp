#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Schema.hpp"
#include <sys/stat.h> 
#include "../Logger.hpp"

/*
 * MetaFile: a directory containing 3 files
 * Record : page_num, slot_size, max_slot_per_page
 * Index  : index_num, (index_name, cons_field) ... 
 * Schema : 
*/ 

struct MetaFileManager{
    MetaFileManager(){}
    
    void create_meta_file(const std::string & directory);

    /* Schema */
    void write_schema(const std::string& filename, const Schema & schm);
    Schema load_schema(const std::string& filename);
    
    /* Index */

private:
    void _create_file(const std::string & filename){
        std::ofstream newFile(filename);
        newFile.close();
    }
};