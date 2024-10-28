#pragma once

#include "../parser/SQLBaseVisitor.h"
#include "DBManager.hpp"



/*
    DBVisitor 继承了 SQLBaseVisitor
*/
class  DBVisitor : public SQLBaseVisitor {
    DBManager &db_manager;


public:

    DBVisitor(DBManager & dbm): db_manager(dbm){}

    std::any visitProgram(SQLParser::ProgramContext *ctx) override;

    std::any visitStatement(SQLParser::StatementContext *ctx) override;

    /* Database Management */
    std::any visitCreate_db(SQLParser::Create_dbContext *ctx) override ; 

    std::any visitDrop_db(SQLParser::Drop_dbContext *ctx) override ; 

    std::any visitShow_dbs(SQLParser::Show_dbsContext *ctx) override ; 

    std::any visitUse_db(SQLParser::Use_dbContext *ctx) override; 

    /* Table Management */
    std::any visitShow_tables(SQLParser::Show_tablesContext *ctx) override ;

    std::any visitShow_indexes(SQLParser::Show_indexesContext *ctx) override ;

    std::any visitCreate_table(SQLParser::Create_tableContext *ctx) override ;

    std::any visitDrop_table(SQLParser::Drop_tableContext *ctx) override ;

    std::any visitDescribe_table(SQLParser::Describe_tableContext *ctx) override ;

    std::any visitField_list(SQLParser::Field_listContext *ctx) override ;

    std::any visitNormal_field(SQLParser::Normal_fieldContext *ctx) override ;

    std::any visitPrimary_key_field(SQLParser::Primary_key_fieldContext *ctx) override ;

    std::any visitForeign_key_field(SQLParser::Foreign_key_fieldContext *ctx) override ;

    /* Record Management */
    std::any visitLoad_table(SQLParser::Load_tableContext *ctx) override ;
     
     /* insert */
    std::any visitInsert_into_table(SQLParser::Insert_into_tableContext *ctx) override ;

    std::any visitDelete_from_table(SQLParser::Delete_from_tableContext *ctx) override ;

    std::any visitUpdate_table(SQLParser::Update_tableContext *ctx) override ;

    std::any visitSelect_table_(SQLParser::Select_table_Context *ctx) override ;

    std::any visitSelect_table(SQLParser::Select_tableContext *ctx) override ;

     /* index */
    std::any visitAlter_add_index(SQLParser::Alter_add_indexContext *ctx) override ;

    std::any visitAlter_drop_index(SQLParser::Alter_drop_indexContext *ctx) override ;

    /* pk */
    std::any visitAlter_table_drop_pk(SQLParser::Alter_table_drop_pkContext *ctx) override ;

    std::any visitAlter_table_drop_foreign_key(SQLParser::Alter_table_drop_foreign_keyContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitAlter_table_add_pk(SQLParser::Alter_table_add_pkContext *ctx) override ;

    std::any visitAlter_table_add_foreign_key(SQLParser::Alter_table_add_foreign_keyContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitAlter_table_add_unique(SQLParser::Alter_table_add_uniqueContext *ctx) override {
    return visitChildren(ctx);
  }


    std::any visitType_(SQLParser::Type_Context *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitOrder(SQLParser::OrderContext *ctx) override {
    return visitChildren(ctx);
  }

    /* Value */
    std::any visitValue_lists(SQLParser::Value_listsContext *ctx) override; 

    std::any visitValue_list(SQLParser::Value_listContext *ctx) override; 

    std::any visitValue(SQLParser::ValueContext *ctx) override ;

    /* Where */
    std::any visitWhere_and_clause(SQLParser::Where_and_clauseContext *ctx) override ; 

    std::any visitWhere_operator_expression(SQLParser::Where_operator_expressionContext *ctx) override ;

    /* */

    std::any visitWhere_operator_select(SQLParser::Where_operator_selectContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitWhere_null(SQLParser::Where_nullContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitWhere_in_list(SQLParser::Where_in_listContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitWhere_in_select(SQLParser::Where_in_selectContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitWhere_like_string(SQLParser::Where_like_stringContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitColumn(SQLParser::ColumnContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitExpression(SQLParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitSet_clause(SQLParser::Set_clauseContext *ctx) override ;

    std::any visitSelectors(SQLParser::SelectorsContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitSelector(SQLParser::SelectorContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitIdentifiers(SQLParser::IdentifiersContext *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitOperator_(SQLParser::Operator_Context *ctx) override {
    return visitChildren(ctx);
  }

    std::any visitAggregator(SQLParser::AggregatorContext *ctx) override {
    return visitChildren(ctx);
  }


};

