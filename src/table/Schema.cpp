#include "Schema.hpp"


Schema::Schema(const std::vector<FieldManager> & fds, const std::vector<std::string> & primary_keys, const std::vector<ForeignKeyCons> foreign_keys){
    // field_names
    for (auto const& fd : fds) field_names.push_back(fd.name);
    fields = fds; // fields
    // primary_key_ids 
    for (auto const& pk : primary_keys){
        auto it = std::find(field_names.begin(), field_names.end(), pk);
        size_t index = std::distance(field_names.begin(), it);
        primary_key_ids.push_back(index);
        fields[index].allow_null = false;
    } 
    // foreign_key_cons;
    for (auto fk : foreign_keys){
        std::vector<size_t> fidx;
        for (auto const & n : fk.field_name){
            auto it = std::find(field_names.begin(), field_names.end(), n);
            size_t idx = std::distance(field_names.begin(), it);
            fidx.push_back(idx);
        }
        fk.set_index(fidx);
        if (fk.name == "_default")
            fk.set_name(std::to_string(foreign_key_cons.size()));
        foreign_key_cons.push_back(fk);
    }
}

void Schema::read(std::ifstream& inFile){
    // clear existing vectors
    field_names.clear() ; fields.clear(); 
    primary_key_ids.clear(); foreign_key_cons.clear();

    // get lines
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inFile, line)){
        lines.push_back(line);
    }
    // split the lines
    size_t field_size = std::stoll(lines[0]);
    std::string primary_key_line = lines[1 + field_size];
    size_t foreign_keys_size = std::stoll(lines[2 + field_size]);

    // fileds
    // std::cerr << field_size << std::endl;
    if (field_size > 0){
        std::vector<std::string> field_lines(lines.begin() + 1, lines.begin() + 1 + field_size);
        for (auto const & l : field_lines){
            fields.push_back(FieldManager(l));
        }
    }
    // field_names
    for (auto const& fd : fields) field_names.push_back(fd.name);
    // primary_keys
    std::string idx; 
    std::istringstream temp_line = std::istringstream(primary_key_line);
    while (std::getline(temp_line, idx, ' ')){
        primary_key_ids.push_back(std::stoll(idx));
    }
    // foreign_keys
    if (foreign_keys_size > 0){
        std::vector<std::string> foreign_lines(lines.begin() + 3 + field_size, lines.begin() + 3 + field_size + foreign_keys_size);
        for (auto const & l : foreign_lines){
            foreign_key_cons.push_back(ForeignKeyCons(l));
        }
    }
}    