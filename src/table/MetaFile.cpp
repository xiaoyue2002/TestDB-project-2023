#include "MetaFile.hpp"

/* Schema */
void MetaFileManager::write_schema(const std::string& filename, const Schema & schm){
    std::string schema_file = filename + "/meta/schema.txt";
    Logger::logging(schema_file);
    std::ofstream outFile(schema_file);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing" << std::endl;
        exit(1);
    }
    schm.write(outFile);
    outFile.close();
}

Schema MetaFileManager::load_schema(const std::string& filename){
    std::string schema_file = filename + "/meta/schema.txt";
    std::ifstream inFile(schema_file);
    
    if (!inFile.is_open()){
        std::cerr << "Unable to open file for loading" << schema_file << std::endl;
    }
    Schema schm;
    schm.read(inFile);
    inFile.close();
    return schm;
}

void MetaFileManager::create_meta_file(const std::string & directory){
    std::string path = directory + "/meta";
 
    struct stat info;
    if (stat(path.c_str(), &info) !=0){
        // Directory does not exist, create
        if (mkdir(path.c_str(), 0777) == -1){
            throw std::runtime_error("Error creating directory (create_meta_file)!" + path);
        }
    }

    std::string index_path = path + "/index";

    struct stat info2;
    if (stat(index_path.c_str(), &info2) !=0){
        // Directory does not exist, create
        if (mkdir(index_path.c_str(), 0777) == -1){
            throw std::runtime_error("Error creating directory (create_meta_file - 2)!" + index_path);
        }
    }
        
    std::string schema_file = path + "/schema.txt";
    _create_file(schema_file) ;
}