// #pragma once
#include <string>
// #include "../linux_runtime/usr/local/include/antlr4-runtime/antlr4-runtime.h"
#include "antlr4-runtime.h"
#include <stdexcept>
#include <getopt.h>
#include "./filesystem/utils/MyBitMap.h"
#include "./db_manage/DBVisitor.hpp"
#include "./db_manage/DBManager.hpp"

#include "./parser/SQLLexer.h"
#include "./parser/SQLParser.h"

void process_input(const std::string &input_string, DBVisitor &visitor){
    try {
        antlr4::ANTLRInputStream input{input_string};
        SQLLexer lexer{&input};
        
        antlr4::CommonTokenStream tokens{&lexer};
        tokens.fill();

        SQLParser parser{&tokens};

        // 先检查一次
        // SQLParser temp_parser{&tokens};
        // try {
            // antlr4::tree::ParseTree *new_tree{temp_parser.program()};
        // } catch (const std::exception& e){
            // std::cerr << "Parsing error: " << e.what() << std::endl;
            // return ;
        // }
        // std::cerr << "hi" << std::endl;
        antlr4::tree::ParseTree *tree{parser.program()};
        // if (tree != nullptr){
        tree->accept(&visitor);
        // }
    } catch (const antlr4::ParseCancellationException& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}

int main(int argc, char * argv[]){
    MyBitMap::initConst();

    int opt;
    std::string filePath, tableName, dataBase;
    bool initFlag = false, batchFlag = false, fileFlag = false, tableFlag = false, dataBaseFlag = false;

    // 解析命令行参数
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];
        if (arg == "--init"){
            initFlag = true;
        } else if (arg == "-b" || arg == "--batch") {
            batchFlag = true;
        } else if (arg == "-f" || arg == "--file") {
            if (i + 1 < argc) { // 确保有足够的参数
                fileFlag = true;
                filePath = argv[++i];
            }
        } else if (arg == "-t" || arg == "--table"){
            if (i + 1 < argc) {
                tableFlag = true;
                tableName = argv[++i];
            }
        } else if (arg == "-d" || arg == "--database"){
            if (i + 1 < argc) {
                dataBaseFlag = true;
                dataBase = argv[++i];
            }
        }
    }

    DBManager db_manager(batchFlag);
    DBVisitor visitor(db_manager);

    // --init
    if (initFlag) { 
        return db_manager.init();
    }

    // load file, 需要 -f -t -b
    if (fileFlag && tableFlag && dataBaseFlag){
        db_manager.use_db(dataBase);
        return db_manager.load_from_file(filePath, tableName, ",");  
    }

    // -d 指定启动时使用的数据库
    if (dataBaseFlag){
        db_manager.use_db(dataBase);
    }

    
    while (true) {
        std::string input_string;
        std::getline(std::cin, input_string);
    
        if (input_string == "exit") {
            break; // Exit the loop if the user types "exit"
        }
        try{
            process_input(input_string, visitor);
        } catch (const std::exception& e) {
            std::cerr << "Error occurred: " << e.what() << std::endl;
        }

        if (batchFlag){
        std::cout<<"@"<<input_string<<std::endl;
        }else {
            if (db_manager.get_is_using()){
                std::cerr << db_manager.get_using_db() << "> " ;
            }
        }
    }

    db_manager.close();
   
    // process_input(input_string, visitor);
    return 0;
}