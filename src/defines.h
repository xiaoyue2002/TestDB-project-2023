#ifndef DEFINES_H
#define DEFINES_H
#include <cstdint>
#include <string>
#include <iostream>

typedef int32_t TableID;
typedef int32_t PageID;
typedef int32_t SlotID;
typedef int32_t RecordSize;
typedef int32_t IndexPageSize;

typedef int32_t KeyType;
typedef int32_t PageType;

typedef char * BytePtr;

// constexpr int BUFFPTR_SIZE = sizeof(unsigned int);
// constexpr int INT_LENGTH = 4;       // 例如，4个字节
// constexpr int FLOAT_LENGTH = 8;     // 例如，8个字节
constexpr int VARCHAR_LENGTH = 500; // 例如，最大100个字节
constexpr char DIVIDING[30] = "------------------------";

// constexpr size_t BFPTR_STRIDE = sizeof(unsigned int);
constexpr size_t CHAR_STRIDE = sizeof(char);
constexpr size_t INT_STRIDE = sizeof(int);
constexpr size_t DOUBLE_STRIDE = sizeof(double);

// constexpr size_t PAGE_SIZE = 8192;

enum class OPType { CREATE = 0, OPEN = 1, DELETE = 2, UPDATE = 3 };
enum class OPResult { SUCCESS = 1, FAILED = 0, SPLIT = 2, DELETE = 3, UPDATE=4,};
enum class DataType { INT = 0, FLOAT = 1, VARCHAR = 2};
enum class CompResult {LARGER = 0, EQ = 1, SMALLER = 2};

enum class TARGET {SELECT = 0, DELETE = 1, UPDATE = 2};
enum class QueryType {EQ = 0, NEQ = 1, GREATER = 2,  LESS = 3, GE = 4, LE = 5};

inline DataType string2dtype(const std::string& ss){
    if (ss == "INT")
        return DataType::INT;
    else if (ss == "FLOAT")
        return DataType::FLOAT;
    else if (ss == "VARCHAR")
        return DataType::VARCHAR;
    else{
        std::cout<<"Error in string2dtype"<<std::endl;
        exit(0);
    }
}
inline std::string dtype2string(const DataType & dtype){
    if (dtype == DataType::INT)
        return "INT";
    else if (dtype == DataType::FLOAT)
        return "FLOAT";
    else 
        return "VARCHAR";
}
#endif

