#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstring>
#include <stdexcept>
#include "IndexManager.hpp"
#include "../defines.h"
#include "../table/Schema.hpp"
#include "../Logger.hpp"

/* Open File */
void IndexManager::open_file(std::string name, IndexSchema ischm, IndexInfo iinfo){
    std::string path = index_dir + "/" + name + ".db";
    // open
    int index;
    if (!fm->openFile(path.c_str(), index)){
        throw std::runtime_error("Failed to open: " + path);
    }

    IndexFile index_file(index, bpm, ischm, iinfo);
    index_files.push_back(index_file);  
}


void IndexManager::create_file(const std::string name){
    std::string path = index_dir + "/" + name + ".db";
    if (!fm->createFile(path.c_str())){
        throw std::runtime_error("Failed to create: " + path);
    }
}

// Must get meta files before open (when initializing table_manager)
void IndexManager::open(){
    for (size_t i = 0; i < index_infos.size(); i++){
        open_file(index_schemas[i].name, index_schemas[i], index_infos[i]);
    }
}

void IndexManager::close(){
    int index; 
    for (auto const & index_f : index_files){
        index = index_f.get_file_id();
        fm->closeFile(index);
    }
}

/* Meta File */

void IndexManager::write_file(const IndexInfo & info, const IndexSchema & schema, std::ofstream & outFile){

    outFile << info.tot_num << " " << info.page_num << " " <<  info.root << " " << info.data_head << std::endl;
    
    outFile << schema.name << " " << schema.is_default << std::endl;
    for (auto const & k : schema.key_ids){
        outFile << k << ',';
    }
    outFile << std::endl;

    // internal page
    IndexPageSchema now = schema.internal_schema;
    outFile << now.header_size << " " << now.slot_size << " " << now.max_slot << std::endl;
    outFile << now.is_leaf_offset << " " << now.parent_offset << " " << now.parent_slot_offset << std::endl;
    outFile << now.slot_head_offset << " " << now.slot_tail_offset << std::endl ;

    // internal slot
    SlotSchema cur = schema.internal_slot_schema;
    for (auto const & k : cur.key_offsets){
        outFile << k << ',' ;
    }
    outFile << std::endl;
    outFile << cur.value_offset << " " << cur.prev_offset << " " << cur.next_offset << std::endl;
    
    // leaf page
    now = schema.leaf_schema;
    outFile << now.header_size << " " << now.slot_size << " " << now.max_slot << std::endl;
    outFile << now.is_leaf_offset << " " << now.parent_offset << " " << now.parent_slot_offset << std::endl;
    outFile << now.slot_head_offset << " " << now.slot_tail_offset << std::endl ;
    outFile << now.prev_page_offset << " " << now.next_page_offset << std::endl;

    // leaf slot
    cur = schema.leaf_slot_schema;
    for (auto const & k : cur.key_offsets){
        outFile << k << ',' ;
    }
    outFile << std::endl;
    outFile << cur.prev_offset << " " << cur.next_offset << " " << cur.page_id_offset << " " <<  cur.slot_id_offset << std::endl;

}
void IndexManager::read_file(std::ifstream & inFile){
    IndexInfo info;
    IndexSchema schema;

    inFile >> info.tot_num >> info.page_num >> info.root >> info.data_head;
    inFile >> schema.name >> schema.is_default ;

    int value;
    std::string line;
    std::getline(inFile, line); // endl
    std::getline(inFile, line); // key_ids
    std::istringstream iss3(line);
    while (iss3 >> value) {
        schema.key_ids.push_back(value);
        if (iss3.peek() == ',') iss3.ignore();
    }

    // internal page
    IndexPageSchema now;
    inFile >> now.header_size >> now.slot_size >> now.max_slot;
    inFile >> now.is_leaf_offset >> now.parent_offset >> now.parent_slot_offset;
    inFile >> now.slot_head_offset >> now.slot_tail_offset;
    schema.internal_schema = now;

    // internal slot
    SlotSchema cur;
    std::getline(inFile, line); // endl
    std::getline(inFile, line); // key_offsets
    std::istringstream iss(line);
    while (iss >> value) {
        cur.key_offsets.push_back(value);
        if (iss.peek() == ',') iss.ignore();
    }
    inFile >> cur.value_offset >> cur.prev_offset >> cur.next_offset;
    schema.internal_slot_schema = cur;

    // leaf page
    inFile >> now.header_size >> now.slot_size >> now.max_slot;
    inFile >> now.is_leaf_offset >> now.parent_offset >> now.parent_slot_offset;
    inFile >> now.slot_head_offset >> now.slot_tail_offset;
    inFile >> now.prev_page_offset >> now.next_page_offset;
    schema.leaf_schema = now;

    // leaf slot
    cur.key_offsets.clear();
    std::getline(inFile, line); // ednl
    std::getline(inFile, line); // key_offsets
    std::istringstream iss2(line);
    while (iss2 >> value) {
        cur.key_offsets.push_back(value);
        if (iss2.peek() == ',') iss2.ignore();
    }
    inFile >> cur.prev_offset >> cur.next_offset >> cur.page_id_offset >> cur.slot_id_offset ;
    schema.leaf_slot_schema = cur;

    index_infos.push_back(info);
    index_schemas.push_back(schema);
}

/* Create Index */

void IndexManager::create_auto_index(const Schema & table_schema){
    std::vector<std::string> names;
    for (const auto & pkid : table_schema.primary_key_ids){
        names.push_back(table_schema.field_names[pkid]);
    }
    // std::cerr << "create_auto_index" <<std::endl;
    create_index_on("default", true, table_schema, names);
}


void IndexManager::create_index_on(std::string name, bool is_default, const Schema & schema, const std::vector<std::string> & fields){
    std::vector<int> key_ids;

    // first get all keys
    for (const auto& field : fields) {
        auto it = std::find(schema.field_names.begin(), schema.field_names.end(), field);
        if (it != schema.field_names.end()) {
            int _id = std::distance(schema.field_names.begin(), it);
            if (schema.fields[_id].type != DataType::INT){
                throw std::runtime_error("Index Field " + field + " Is Not INT.");
            }
            key_ids.push_back(_id);
        } else {
            throw std::runtime_error("Index Field " + field + " Does not exist.");
        }
    }


    // create internal slot schema
    std::vector<size_t> key_offsets;
    SlotSchema inslot_schema;
    size_t fsize;
    size_t offset = 0;
    for (auto const & kid : key_ids){
        key_offsets.push_back(offset);
        fsize = schema.fields[kid].field_size();
        offset += fsize;
    }
    inslot_schema.key_offsets = key_offsets;
    inslot_schema.value_offset = offset;
    inslot_schema.prev_offset = inslot_schema.value_offset + sizeof(PageID);
    inslot_schema.next_offset = inslot_schema.prev_offset + sizeof(SlotID);

    // create internal page schema
    IndexPageSchema inpage_schema;
    inpage_schema.slot_size = inslot_schema.next_offset + sizeof(SlotID);
    size_t head_max = sizeof(char) + sizeof(SlotID) * 4 + sizeof(bool) + sizeof(PageID);
    
    inpage_schema.max_slot = (PAGE_SIZE - head_max) / (inpage_schema.slot_size + 1);
    inpage_schema.is_leaf_offset = 0 ;   // leaf 改到最前面了, 和Bitmap交换了位置
    size_t slot_header_size = std::max(CHAR_STRIDE, sizeof(char) * ((inpage_schema.max_slot + CHAR_BIT - 1) / CHAR_BIT) + sizeof(SlotID));
    inpage_schema.parent_offset = slot_header_size + sizeof(bool);
    inpage_schema.parent_slot_offset = inpage_schema.parent_offset + sizeof(PageID);
    inpage_schema.slot_head_offset = inpage_schema.parent_slot_offset + sizeof(SlotID);
    inpage_schema.slot_tail_offset = inpage_schema.slot_head_offset + sizeof(SlotID);
    inpage_schema.header_size = inpage_schema.slot_tail_offset + sizeof(SlotID);

    // create leaf slot schema
    key_offsets.clear();
    for (size_t i = 0 ; i < key_ids.size(); i++){
        key_offsets.push_back( i * sizeof(int));
    }
    SlotSchema leafslot_schema;
    leafslot_schema.key_offsets = key_offsets;
    leafslot_schema.page_id_offset = key_ids.size() * sizeof(int);
    leafslot_schema.slot_id_offset = leafslot_schema.page_id_offset + sizeof(PageID);
    leafslot_schema.prev_offset = leafslot_schema.slot_id_offset + sizeof(SlotID);
    leafslot_schema.next_offset = leafslot_schema.prev_offset + sizeof(SlotID);

    // std::cerr << "leaf_slot " << leafslot_schema.page_id_offset << std::endl;

    // creat leaf page schema
    IndexPageSchema leafpage_schema;
    leafpage_schema.slot_size = leafslot_schema.next_offset + sizeof(SlotID);
    
    head_max = sizeof(char) + sizeof(SlotID) * 4 + sizeof(bool) + sizeof(PageID) * 3;
    leafpage_schema.max_slot = (PAGE_SIZE - head_max) / (leafpage_schema.slot_size + 1);
    leafpage_schema.is_leaf_offset = 0 ; // leaf 和 bitmap交换位置
    size_t leaf_slot_header_size = std::max(CHAR_STRIDE, sizeof(char) * ((leafpage_schema.max_slot + CHAR_BIT - 1) / CHAR_BIT) + sizeof(SlotID));
    leafpage_schema.parent_offset = leaf_slot_header_size + sizeof(bool);
    leafpage_schema.parent_slot_offset = leafpage_schema.parent_offset + sizeof(PageID);
    leafpage_schema.slot_head_offset = leafpage_schema.parent_slot_offset + sizeof(SlotID);
    leafpage_schema.slot_tail_offset = leafpage_schema.slot_head_offset + sizeof(SlotID);
    leafpage_schema.prev_page_offset = leafpage_schema.slot_tail_offset + sizeof(SlotID);
    leafpage_schema.next_page_offset = leafpage_schema.prev_page_offset + sizeof(PageID);
    leafpage_schema.header_size = leafpage_schema.next_page_offset + sizeof(PageID);

    IndexSchema index_schema(name, is_default, key_ids, inpage_schema, leafpage_schema, inslot_schema, leafslot_schema);
    
    // create file
    create_file(name);

    // add schema
    index_schemas.push_back(index_schema);

    // add info
    IndexInfo info(0, 0, -1, -1);
    index_infos.push_back(info);

    // open
    open_file(name, index_schema, info);
}

void IndexManager::write(const std::string table_dir){
    for (size_t i = 0 ; i < index_schemas.size(); i++){
        std::string index_name = table_dir + "/meta/index/" + index_schemas[i].name + ".txt";
        std::ofstream outFile(index_name);
        write_file(index_infos[i], index_schemas[i], outFile);
        outFile.close();
    }
}

void IndexManager::read(const std::string table_dir){
    std::string path = table_dir + "/meta/index";

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream inFile(entry.path());
            if (!inFile) {
                std::cerr << "Failed to open : " << entry.path() << std::endl;
                continue;
            }
            read_file(inFile);
            inFile.close();
        }
    }
}  

void IndexManager::drop_index(std::string index_name){
    for (size_t i = 0; i < index_infos.size(); i++){
        if (index_schemas[i].name == index_name){
            index_infos.erase(index_infos.begin() + i);
            index_files.erase(index_files.begin() + i);
            index_schemas.erase(index_schemas.begin() + i);
            break;
        }
    }
}