#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <climits>
#include <cstring>
#include <iostream>
#include <regex>
#include <iomanip>
#include "../defines.h"

/*
    用来存储一条数据的struct，是一个union
*/

struct FieldData{
    union{
        int intValue;
        double floatValue;
        char varcharValue[VARCHAR_LENGTH];
    };
    bool null;
    DataType field_data_type;
    
    std::string to_string() const {
        std::stringstream ss;
        if (null){
            ss << "NULL";
        } else {
            if (field_data_type == DataType::INT){
                ss << intValue;
            } else if (field_data_type == DataType::FLOAT){
                ss << std::fixed << std::setprecision(2) << floatValue;
            } else {
                ss << varcharValue;
            }
        }
        return ss.str();
    }

    FieldData(): null(true){};
    FieldData(const int v): intValue(v), null(false), field_data_type(DataType::INT){};
    FieldData(const double v): floatValue(v), null(false), field_data_type(DataType::FLOAT){};
    FieldData(const std::string v): null(false), field_data_type(DataType::VARCHAR) {
        strncpy(varcharValue, v.c_str(), VARCHAR_LENGTH - 1); 
        varcharValue[VARCHAR_LENGTH - 1] = '\0';
    }
    FieldData(const char * v): null(false), field_data_type(DataType::VARCHAR){
       strncpy(varcharValue, v, VARCHAR_LENGTH - 1); 
       varcharValue[VARCHAR_LENGTH - 1] = '\0';
    }
    FieldData(const std::string & v, DataType dtype){
        null = false;
        if (v == "NULL"){
            null = true;
        }else if (dtype == DataType::INT){
            intValue = std::stoi(v);
        }else if (dtype == DataType::FLOAT){
            floatValue = std::stod(v);
        }else if (dtype == DataType::VARCHAR){
            strncpy(varcharValue, v.c_str(), VARCHAR_LENGTH - 1); 
            varcharValue[VARCHAR_LENGTH - 1] = '\0';
        }
    }
    FieldData(const FieldData & other){
        field_data_type = other.field_data_type;
        if (field_data_type == DataType::INT){
            intValue = other.intValue;
        } else if (field_data_type == DataType::FLOAT){
            floatValue = other.floatValue;
        } else {
            strncpy(varcharValue, other.varcharValue, VARCHAR_LENGTH - 1); 
            varcharValue[VARCHAR_LENGTH - 1] = '\0';
        }
        null = other.null; 
    }
    ~FieldData(){};
};


/*
    用来管理数据的struct
*/
struct FieldManager{
    // -- * to be stored * --
    std::string name;
    DataType type;
    bool allow_null;
    size_t varchar_len;
    FieldData default_value;
    // -- * end * --

    FieldManager(std::string n, DataType t, bool an, size_t vl, FieldData dv):
        name(n), type(t), allow_null(an), varchar_len(vl), default_value(dv){}
    FieldManager(const std::string & infos){stringto(infos);}

    // print
    void print(){
        std::cout<<tostring()<<std::endl;
    }

    size_t field_size() const {
        if (type == DataType::INT) return sizeof(int);
        else if (type == DataType::FLOAT) return sizeof(double);
        else return varchar_len * sizeof(char);
    }

    std::string string_data(const FieldData & fd) const {
        std::stringstream ss;
        if (fd.null) ss << "NULL";
        else if (type == DataType::INT) ss << fd.intValue;
        else if (type == DataType::FLOAT) ss << fd.floatValue;
        else ss << fd.varcharValue;
        return ss.str();
    }

    /* name, type(varchar_len), allow_null, default_value */
    std::string tostring_print() const {
        std::stringstream ss;
        ss << name << "," << dtype2string(type);
        if (type == DataType::VARCHAR) ss << "(" << varchar_len << ")";
        ss << ",";
        if (allow_null) ss << "YES";
        else ss << "NO";
        ss << ",";
        ss << string_data(default_value);
        return ss.str();
    }
    /* name, type varchar_len, allow_null, default_value */
    std::string tostring() const {
        std::stringstream ss;
        ss << name << "," << dtype2string(type);
        if (type == DataType::VARCHAR) ss << " " << varchar_len;
        ss << ",";
        if (allow_null) ss << "YES";
        else ss << "NO";
        ss << ",";
        ss << string_data(default_value);
        return ss.str();
    }
    
private:

    void stringto(const std::string & infos){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(infos);
        while (std::getline(tokenStream, token, ',')) {
            tokens.push_back(token);
        }
        name = tokens[0]; // name
        varchar_len = 0;
        std::vector<std::string> type_str;
        std::istringstream temp_line = std::istringstream(tokens[1]);
        while (std::getline(temp_line, token, ' ')){
            type_str.push_back(token);
        }
        type = string2dtype(type_str[0]);
        if (type == DataType::VARCHAR) varchar_len = std::stoll(type_str[1]);
        allow_null = (tokens[2] == "YES");  // null
        default_value = FieldData(tokens[3], type); // default_value
    }
};

struct ForeignKeyCons{
    // -- * to be stored * --
    std::string name;
    std::vector<std::string> field_name;
    std::string foreign_table;
    std::vector<std::string> foreign_field;
    // -- * end * --

    std::vector<size_t> field_index;

    ForeignKeyCons(const std::string & n, 
               const std::vector<std::string> & fn, 
               const std::string ftb,
               const std::vector<std::string> & ff){
        name = n; field_name = fn; foreign_table = ftb; foreign_field = ff;
    }
    ForeignKeyCons(const std::string & infos){
        stringto(infos);
    }

    void set_name(const std::string & n){
        name = n;
    }

    void set_index(const std::vector<size_t> & fidx){
        field_index = fidx;
    }

    // eg : <name> <key1>,<key2> <tb_name> <fk1>,<fk2>
    std::string tostring() const {
        std::stringstream ss; 
        ss << name << " ";
        bool first = true;
        for (auto const & n : field_name){
            if (first) {ss << n; first = false;} 
            else ss << "," << n;
        }
        ss << " " << foreign_table << " ";
        first = true;
        for (auto const & n : foreign_field){
            if (first) {ss << n; first = false;} 
            else ss << "," << n;
        }
        return ss.str();
    }

    // eg : FOREIGN KEY (PS_SUPPKEY, ALICE) REFERENCES SUPPLIER(S_SUPPKEY, BOB);
    std::string tostring_print() const {
        std::stringstream ss;
        ss << "FOREIGN KEY (";
        bool first = true;
        for (auto const& n : field_name){
            if(first){ss << n ; first=false;}
            else ss << ", " << n; 
        }
        ss << ") REFERENCES ";
        ss << foreign_table << "(";
        first = true;
        for (auto const& n : foreign_field){
            if(first){ss << n ; first=false;}
            else ss << ", " << n; 
        } 
        ss << ");";
        return ss.str();
    }
private:
    // eg : <name> <key1>,<key2> <tb_name> <fk1>,<fk2>
    void stringto(const std::string & infos){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(infos);
        while (std::getline(tokenStream, token, ' ')) {
            tokens.push_back(token);
        }
        name = tokens[0], foreign_table = tokens[2];
        field_name.clear(); foreign_field.clear();
        std::istringstream temp_line = std::istringstream(tokens[1]);
        while (std::getline(temp_line, token, ',')){
            field_name.push_back(token);
        }
        temp_line = std::istringstream(tokens[3]);
        while (std::getline(temp_line, token, ',')){
            foreign_field.push_back(token);
        }
    }

};


struct Schema{
    std::vector<std::string> field_names;
    std::vector<FieldManager> fields;
    std::vector<int> primary_key_ids;
    std::vector<ForeignKeyCons> foreign_key_cons;

    Schema(){};
    Schema(const Schema & other){
        field_names = other.field_names;
        fields = other.fields;
        primary_key_ids = other.primary_key_ids;
        foreign_key_cons = other.foreign_key_cons;
    };
    Schema(const std::vector<FieldManager> & fds, const std::vector<std::string> & primary_keys, const std::vector<ForeignKeyCons> foreign_keys);

    size_t slot_size() const {
        size_t fnum = fields.size();
        size_t slot_size = std::max(CHAR_STRIDE, sizeof(char) * ((fnum + CHAR_BIT - 1) / CHAR_BIT));
        for (auto const & f : fields){
            slot_size += f.field_size();
        }
        return slot_size;
    }

    // fields
    void write(std::ofstream& outFile) const {
        outFile << fields.size() << std::endl;
        for (auto const & f : fields){
            outFile << f.tostring() << std::endl;
        }
        // primary_key_ids
        for (auto const & idx : primary_key_ids){
            outFile << idx << " ";
        }
        outFile << std::endl;
        // foreign_keys
        outFile << foreign_key_cons.size() << std::endl;
        for (auto const &f : foreign_key_cons){
            outFile << f.tostring() << std::endl;
        }
    }
    void read(std::ifstream& inFile);
};
    