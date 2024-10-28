#include <stdexcept>
#include "../Logger.hpp"
#include "DBVisitor.hpp"
#include "../table/Schema.hpp"
#include "../query/constrains.hpp"

/* Top module of the visitor */
std::any DBVisitor::visitProgram(SQLParser::ProgramContext *ctx){
    Logger::logging("visitProgram;");
    for (auto const & child : ctx->children){
        // auto statement_ctx = dynamic_cast<SQLParser::StatementContext *>(child);
        child->accept(this);
    }
    return 0;
}

std::any DBVisitor::visitStatement(SQLParser::StatementContext *ctx){
    Logger::logging("visitStatement;");
    return ctx->children[0]->accept(this);
}

/* Database Management */
std::any DBVisitor::visitCreate_db(SQLParser::Create_dbContext *ctx){
    Logger::logging("visitCreate_db;");
    visitChildren(ctx);
    std::string db_name{ctx->Identifier()->getSymbol()->getText()};
    db_manager.create_db(db_name);
    return 0;
}

std::any DBVisitor::visitDrop_db(SQLParser::Drop_dbContext *ctx){
    std::string db_name = ctx->Identifier()->getText();
    db_manager.drop_db(db_name);
    return 0;
}

std::any DBVisitor::visitShow_dbs(SQLParser::Show_dbsContext *ctx){
    Logger::logging("visitShow_dbs;");
    return db_manager.show_db();
}

std::any DBVisitor::visitUse_db(SQLParser::Use_dbContext *ctx){
    std::string db_name = ctx->Identifier()->getText();
    db_manager.use_db(db_name);
    return 0;
}

/* Table Management */
std::any DBVisitor::visitShow_tables(SQLParser::Show_tablesContext *ctx) {
    db_manager.show_tables();
    return 0;
}

std::any DBVisitor::visitShow_indexes(SQLParser::Show_indexesContext *ctx) {
    return visitChildren(ctx);
}

std::any DBVisitor::visitCreate_table(SQLParser::Create_tableContext *ctx) {
    Logger::logging("visitCreate_table");
    std::string table_name = ctx->Identifier()->getText();
    auto schema = std::any_cast<Schema>(visit(ctx->field_list()));
    db_manager.create_table(table_name, schema);
    return 0;
}

/**
 * Create a new Schema from field_list.
 * Including : fields | foreign_keys | primary_keys
 * @return Schema
*/
std::any DBVisitor::visitField_list(SQLParser::Field_listContext *ctx){
    Logger::logging("visitField_list;");
    std::vector<FieldManager> fields;
    std::vector<ForeignKeyCons> foreign_keys;
    std::vector<std::string> primary_keys;

    for (auto &fieldCtx : ctx->field()) {
        // normal_field
        if (auto normalField = dynamic_cast<SQLParser::Normal_fieldContext*>(fieldCtx)) {
            auto new_field = visitNormal_field(normalField);
            fields.push_back(std::any_cast<FieldManager>(new_field));
        }
        // primary_key_field
        else if (auto primaryKeyField = dynamic_cast<SQLParser::Primary_key_fieldContext*>(fieldCtx)) {
            auto pk = visitPrimary_key_field(primaryKeyField);
            primary_keys = std::any_cast<std::vector<std::string>>(pk);
        }
        // foreign_key_field
        else if (auto foreignKeyField = dynamic_cast<SQLParser::Foreign_key_fieldContext*>(fieldCtx)) {
            auto fk = visitForeign_key_field(foreignKeyField);
            foreign_keys.push_back(std::any_cast<ForeignKeyCons>(fk));
        }
    }

    Schema schm(fields, primary_keys, foreign_keys);

    Logger::logging("hello1");
    return schm;
}


/**
 * Create a normal field.
 * Set : name | type(varchar_len) | null | default_value
 * @return FieldManager
*/
std::any DBVisitor::visitNormal_field(SQLParser::Normal_fieldContext *ctx){
    Logger::logging("visitNormal_filed;");
    std::string field_name = ctx->Identifier()->getText();
    std::string field_type = ctx->type_()->getText();
    
    bool null = true;
    size_t varchar_len = 0;
    FieldData default_data;

    if (ctx->type_()->Integer()){ // varchar_len
        field_type = "VARCHAR";
        varchar_len = std::stoll(ctx->type_()->Integer()->getText());
    }
    DataType dtype = string2dtype(field_type); // dtype
    if (ctx->Null()) null = false; // allow_null
    if (ctx->value()){
        default_data = FieldData(ctx->value()->getText(), dtype); // default value
    }

    FieldManager fm(field_name, dtype, null, varchar_len, default_data);
    Logger::logging("hello2");
    return fm;
}

/**
 * Get all primary keys
 * @return std::vector<std::string>
*/
std::any DBVisitor::visitPrimary_key_field(SQLParser::Primary_key_fieldContext *ctx){
    Logger::logging("visitPrimary_key_field;");
    std::vector<std::string> primaryKeys;

    if (ctx->Identifier() != nullptr) {
        primaryKeys.push_back(ctx->Identifier()->getText());
    }

    if (ctx->identifiers() != nullptr) {
        for (auto idCtx : ctx->identifiers()->Identifier()) {
            primaryKeys.push_back(idCtx->getText());
        }
    }

    Logger::logging("hello3");
    return primaryKeys;
}

/** 
 * Get all foreign keys
 * @return ForeginKeyCons
*/
std::any DBVisitor::visitForeign_key_field(SQLParser::Foreign_key_fieldContext *ctx){
    Logger::logging("visitForeign_key_field;");
    std::string name = "_default";
    std::vector<std::string> fns;
    std::string ftb;
    std::vector<std::string> ffs;

    // ftb
    if (ctx->Identifier(1) != nullptr) {
        name = ctx->Identifier(0)->getText();
        ftb = ctx->Identifier(1)->getText();
    }else{
        ftb = ctx->Identifier(0)->getText();
    }

    // fns
    if (ctx->identifiers(0) != nullptr) {
        for (auto idCtx : ctx->identifiers(0)->Identifier()) {
            fns.push_back(idCtx->getText());
        }
    }

    // ffs
    if (ctx->identifiers(1) != nullptr) {
        for (auto idCtx : ctx->identifiers(1)->Identifier()) {
            ffs.push_back(idCtx->getText());
        }
    }
    // std::cout<<fns.size() << " "<<ffs.size()<<std::endl;

    return ForeignKeyCons(name, fns, ftb, ffs);
}

std::any DBVisitor::visitDrop_table(SQLParser::Drop_tableContext *ctx) {
    std::string tb_name = ctx->Identifier()->getText();
    db_manager.drop_table(tb_name);
    return 0;
}

std::any DBVisitor::visitDescribe_table(SQLParser::Describe_tableContext *ctx) {
    std::string tb_name = ctx->Identifier()->getText();
    db_manager.describe_table(tb_name);
    return 0;
}

/* Loading Data */
std::any DBVisitor::visitLoad_table(SQLParser::Load_tableContext *ctx){
    std::string filename = ctx->String(0)->getText();
    std::string tb_name = ctx->Identifier()->getText();
    std::string divider = ctx->String(1)->getText();
    db_manager.load_from_file(filename, tb_name, divider);
    return 0;
}

std::any DBVisitor::visitInsert_into_table(SQLParser::Insert_into_tableContext *ctx) {
    std::vector<std::vector<FieldData>> value_lists = std::any_cast<std::vector<std::vector<FieldData>>>(visitValue_lists(ctx->value_lists()));
    std::string tb_name = ctx->Identifier()->getText();
    db_manager.insert_data(tb_name, value_lists);
    return 0;
}

/* Value */
std::any DBVisitor::visitValue_lists(SQLParser::Value_listsContext *ctx) {
    // Logger::logError("hi");
    std::vector<std::vector<FieldData>> valueLists;
    for (auto valueListCtx : ctx->value_list()) {
        valueLists.push_back(std::any_cast<std::vector<FieldData>>(visitValue_list(valueListCtx)));
    }
    return valueLists;
}

std::any DBVisitor::visitValue_list(SQLParser::Value_listContext *ctx) {
    std::vector<FieldData> values;
    for (auto valueCtx : ctx->value()) {
        values.push_back(std::any_cast<FieldData>(visitValue(valueCtx)));
    }
    return values;
}

std::any DBVisitor::visitValue(SQLParser::ValueContext *ctx){
    if (ctx->Integer() != nullptr) {
        // Logger::logError("int");
        return FieldData(std::stoi(ctx->Integer()->getText()));
    } else if (ctx->String() != nullptr) {
        std::string path = ctx->String()->getText();
        if (!path.empty() && path.front() == '\'' && path.back() == '\'') {
            path = path.substr(1, path.length() - 2);
        }
        return FieldData(path);
    } else if (ctx->Float() != nullptr) {
        return FieldData(std::stod(ctx->Float()->getText()));
    } else if (ctx->Null() != nullptr) {
        return FieldData();
    }
    throw std::runtime_error("Unrecognized value type in visitValue");
    return 0;
}

/* SELECT FROM TABLE */
std::any DBVisitor::visitSelect_table_(SQLParser::Select_table_Context *ctx) {
    return visitSelect_table(ctx->select_table());
}

//select_table
//    : 'SELECT' selectors 'FROM' identifiers ('WHERE' where_and_clause)? ('GROUP' 'BY' column)? ('ORDER' 'BY' column (order)?)? ('LIMIT' Integer ('OFFSET' Integer)?)?
//    ;

std::any DBVisitor::visitSelect_table(SQLParser::Select_tableContext *ctx) {
    std::vector<std::string> columns;
    std::vector<std::string> tables;
    bool join = false;
    bool select_all = false;

    // 处理 selectors
    if (ctx->selectors()->getText() == "*"){
        // std::cerr << "select all" << std::endl;
        select_all = true;
    } else {
        for (auto selector : ctx->selectors()->selector()) {
            if (selector->column()) {
                // 处理 column 类型
                if (selector->column()->Identifier().size() == 2) {
                    // 有表名和列名
                    std::string tableName = selector->column()->Identifier(0)->getText();
                    std::string columnName = selector->column()->Identifier(1)->getText();
                    columns.push_back(columnName);
                    tables.push_back(tableName);
                } else {
                    // 只有列名
                    std::string columnName = selector->column()->Identifier(0)->getText();
                    columns.push_back(columnName);
                }
            } else {
                throw std::runtime_error("Not Implemented (Aggregator).");
            }
        }
    }

    // 处理 identifiers
    std::vector<std::string> selecting_table;
    for (auto identifier : ctx->identifiers()->Identifier()) {
        selecting_table.push_back(identifier->getText());
    }
    if (selecting_table.size() > 1){
        join = true;
    }
    
    // 处理 where and cause
    std::vector<Constrain> constrains;
    if (ctx->where_and_clause() != nullptr) {
        constrains = std::any_cast<std::vector<Constrain>>(visit(ctx->where_and_clause()));
    }

    if (!join){
        // std::cerr << "SELECT" << std::endl;
        db_manager.select(select_all, columns, selecting_table[0], constrains);
    } else {
        // std::cerr << "JOIN" << std::endl;
        db_manager.join_select(tables, columns, selecting_table, constrains);
    }
    // std::cerr << "Hi AGIAIN" <<std::endl;

    return 0;   
}

// where_and_clause
    // : where_clause ('AND' where_clause)*
    // ;
std::any DBVisitor::visitWhere_and_clause(SQLParser::Where_and_clauseContext *ctx){
    std::vector<Constrain> constrains;

    for (auto& clause : ctx->where_clause()) {
        Constrain cond = std::any_cast<Constrain>(visit(clause));
        constrains.push_back(cond);
    }
    // std::cerr << "visit_where_and_clause" << std::endl;
    return constrains;
}

//  column operator_ expression            # where_operator_expression
std::any DBVisitor::visitWhere_operator_expression(SQLParser::Where_operator_expressionContext *ctx){
    Constrain cons;

    // column
    if (ctx->column()->Identifier().size() == 2) {
        // 有表名和列名
        cons.tb_name = ctx->column()->Identifier(0)->getText();
        cons.column_name = ctx->column()->Identifier(1)->getText();
    } else {
        // 只有列名
        cons.column_name = ctx->column()->Identifier(0)->getText();
    }

    // operator
    if (ctx->operator_()->EqualOrAssign() != nullptr) {
        cons.query_op = QueryType::EQ ;
    } else if (ctx->operator_()->Less() != nullptr) {
        cons.query_op = QueryType::LESS ;
    } else if (ctx->operator_()->LessEqual() != nullptr) {
        cons.query_op = QueryType::LE ;
    } else if (ctx->operator_()->Greater() != nullptr) {
        cons.query_op = QueryType::GREATER ;
    } else if (ctx->operator_()->GreaterEqual() != nullptr) {
        cons.query_op = QueryType::GE ;
    } else if (ctx->operator_()->NotEqual() != nullptr) {
        cons.query_op = QueryType::NEQ ;
    }

    // expression
    if (ctx->expression()->value() != nullptr){
        cons.bench_data = std::any_cast<FieldData>(visitValue(ctx->expression()->value()));
    } else if (ctx->expression()->column() != nullptr){
        cons.b_tb = ctx->expression()->column()->Identifier(0)->getText();
        cons.b_column = ctx->expression()->column()->Identifier(1)->getText();
    }

    // cons.print();

    return cons;
}

// 'DELETE' 'FROM' Identifier ('WHERE' where_and_clause)?                                        # delete_from_table
std::any DBVisitor::visitDelete_from_table(SQLParser::Delete_from_tableContext *ctx){
    std::string table_name = ctx->Identifier()->getText();
    std::vector<Constrain> constrains;
    
    if (ctx->where_and_clause() != nullptr) {
        constrains = std::any_cast<std::vector<Constrain>>(visit(ctx->where_and_clause()));
    }

    db_manager.delete_data(table_name, constrains);
    return 0;
}

// 'UPDATE' Identifier 'SET' set_clause 'WHERE' where_and_clause                                 # update_table
std::any DBVisitor::visitUpdate_table(SQLParser::Update_tableContext *ctx){
    // Identifier
    std::string table_name = ctx->Identifier()->getText();

    // set_clause
    std::vector<std::pair<std::string, FieldData>> assignments;
    assignments = std::any_cast<std::vector<std::pair<std::string, FieldData>>>(visit(ctx->set_clause()));

    std::vector<std::string> columns;
    std::vector<FieldData> new_datas;

    for (const auto& pair : assignments) {
        columns.push_back(pair.first);
        new_datas.push_back(pair.second);
    }

    // cons
    std::vector<Constrain> constrains;
    if (ctx->where_and_clause() != nullptr) {
        constrains = std::any_cast<std::vector<Constrain>>(visit(ctx->where_and_clause()));
    }

    db_manager.update_data(table_name, columns, new_datas, constrains);
    
    return 0;
}

//set_clause
//   : Identifier EqualOrAssign value (',' Identifier EqualOrAssign value)*
//  ;

std::any DBVisitor::visitSet_clause(SQLParser::Set_clauseContext *ctx){
    std::vector<std::pair<std::string, FieldData>> assignments;

    for (int i = 0; i < ctx->Identifier().size(); ++i) {
        std::string field = ctx->Identifier(i)->getText();
        FieldData val = std::any_cast<FieldData>(visit(ctx->value(i)));  // 假设已经实现了visitValue

        assignments.push_back(std::make_pair(field, val));
    }

    return assignments;
}

/* inde */
// 'ALTER' 'TABLE' Identifier 'ADD' 'INDEX' (Identifier)? '(' identifiers ')'
std::any DBVisitor::visitAlter_add_index(SQLParser::Alter_add_indexContext *ctx){
    // table name
    std::string table_name = ctx->Identifier(0)->getText();

    std::string index_name;
    std::vector<std::string> column_names;

    // index_name
    if (ctx->Identifier().size() > 1) {
        index_name = ctx->Identifier(1)->getText();
    }

    // column_names
    auto identifiers = ctx->identifiers()->Identifier();
    for (auto id_ctx : identifiers) {
        column_names.push_back(id_ctx->getText());
    }   

    db_manager.add_index(table_name, index_name, column_names);
    return 0;
}


// 'ALTER' 'TABLE' Identifier 'DROP' 'INDEX' Identifier                                   
std::any DBVisitor::visitAlter_drop_index(SQLParser::Alter_drop_indexContext *ctx){
    std::string table_name = ctx->Identifier(0)->getText();
    std::string index_name = ctx->Identifier(1)->getText();
    db_manager.drop_index(table_name, index_name);
    return 0;
}

// 'ALTER' 'TABLE' Identifier 'ADD' ('CONSTRAINT' (Identifier)?)? 'PRIMARY' 'KEY' '(' identifiers ')'
std::any DBVisitor::visitAlter_table_drop_pk(SQLParser::Alter_table_drop_pkContext *ctx){
    std::string table_name = ctx->Identifier(0)->getText();
    db_manager.drop_pk(table_name);
    return 0;
}


// 'ALTER' 'TABLE' Identifier 'DROP' 'PRIMARY' 'KEY' (Identifier)?                                       # alter_table_drop_pk
std::any DBVisitor::visitAlter_table_add_pk(SQLParser::Alter_table_add_pkContext *ctx) {
    std::string table_name = ctx->Identifier(0)->getText();
    std::vector<std::string> columns;
    auto identifiers = ctx->identifiers()->Identifier();
    for (auto id_ctx : identifiers) {
        columns.push_back(id_ctx->getText());
    }
    db_manager.add_pk(table_name, columns);
    return 0;
}