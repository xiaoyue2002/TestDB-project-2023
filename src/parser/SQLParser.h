
// Generated from ./src/grammar/SQL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
// #include "../../linux_runtime/usr/local/include/antlr4-runtime/antlr4-runtime.h"




class  SQLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, EqualOrAssign = 55, 
    Less = 56, LessEqual = 57, Greater = 58, GreaterEqual = 59, NotEqual = 60, 
    Count = 61, Average = 62, Max = 63, Min = 64, Sum = 65, Null = 66, Identifier = 67, 
    Integer = 68, String = 69, Float = 70, Whitespace = 71, Annotation = 72
  };

  enum {
    RuleProgram = 0, RuleStatement = 1, RuleDb_statement = 2, RuleTable_statement = 3, 
    RuleSelect_table = 4, RuleAlter_statement = 5, RuleField_list = 6, RuleField = 7, 
    RuleType_ = 8, RuleOrder = 9, RuleValue_lists = 10, RuleValue_list = 11, 
    RuleValue = 12, RuleWhere_and_clause = 13, RuleWhere_clause = 14, RuleColumn = 15, 
    RuleExpression = 16, RuleSet_clause = 17, RuleSelectors = 18, RuleSelector = 19, 
    RuleIdentifiers = 20, RuleOperator_ = 21, RuleAggregator = 22
  };

  explicit SQLParser(antlr4::TokenStream *input);

  SQLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~SQLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class StatementContext;
  class Db_statementContext;
  class Table_statementContext;
  class Select_tableContext;
  class Alter_statementContext;
  class Field_listContext;
  class FieldContext;
  class Type_Context;
  class OrderContext;
  class Value_listsContext;
  class Value_listContext;
  class ValueContext;
  class Where_and_clauseContext;
  class Where_clauseContext;
  class ColumnContext;
  class ExpressionContext;
  class Set_clauseContext;
  class SelectorsContext;
  class SelectorContext;
  class IdentifiersContext;
  class Operator_Context;
  class AggregatorContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Db_statementContext *db_statement();
    Table_statementContext *table_statement();
    Alter_statementContext *alter_statement();
    antlr4::tree::TerminalNode *Annotation();
    antlr4::tree::TerminalNode *Null();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  Db_statementContext : public antlr4::ParserRuleContext {
  public:
    Db_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Db_statementContext() = default;
    void copyFrom(Db_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Show_dbsContext : public Db_statementContext {
  public:
    Show_dbsContext(Db_statementContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Drop_dbContext : public Db_statementContext {
  public:
    Drop_dbContext(Db_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Show_tablesContext : public Db_statementContext {
  public:
    Show_tablesContext(Db_statementContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Create_dbContext : public Db_statementContext {
  public:
    Create_dbContext(Db_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Use_dbContext : public Db_statementContext {
  public:
    Use_dbContext(Db_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Show_indexesContext : public Db_statementContext {
  public:
    Show_indexesContext(Db_statementContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Db_statementContext* db_statement();

  class  Table_statementContext : public antlr4::ParserRuleContext {
  public:
    Table_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Table_statementContext() = default;
    void copyFrom(Table_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Load_tableContext : public Table_statementContext {
  public:
    Load_tableContext(Table_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> String();
    antlr4::tree::TerminalNode* String(size_t i);
    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Delete_from_tableContext : public Table_statementContext {
  public:
    Delete_from_tableContext(Table_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();
    Where_and_clauseContext *where_and_clause();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Insert_into_tableContext : public Table_statementContext {
  public:
    Insert_into_tableContext(Table_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();
    Value_listsContext *value_lists();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Create_tableContext : public Table_statementContext {
  public:
    Create_tableContext(Table_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();
    Field_listContext *field_list();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Describe_tableContext : public Table_statementContext {
  public:
    Describe_tableContext(Table_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Select_table_Context : public Table_statementContext {
  public:
    Select_table_Context(Table_statementContext *ctx);

    Select_tableContext *select_table();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Drop_tableContext : public Table_statementContext {
  public:
    Drop_tableContext(Table_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Update_tableContext : public Table_statementContext {
  public:
    Update_tableContext(Table_statementContext *ctx);

    antlr4::tree::TerminalNode *Identifier();
    Set_clauseContext *set_clause();
    Where_and_clauseContext *where_and_clause();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Table_statementContext* table_statement();

  class  Select_tableContext : public antlr4::ParserRuleContext {
  public:
    Select_tableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorsContext *selectors();
    IdentifiersContext *identifiers();
    Where_and_clauseContext *where_and_clause();
    std::vector<ColumnContext *> column();
    ColumnContext* column(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Integer();
    antlr4::tree::TerminalNode* Integer(size_t i);
    OrderContext *order();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Select_tableContext* select_table();

  class  Alter_statementContext : public antlr4::ParserRuleContext {
  public:
    Alter_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Alter_statementContext() = default;
    void copyFrom(Alter_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Alter_table_drop_pkContext : public Alter_statementContext {
  public:
    Alter_table_drop_pkContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Alter_table_add_foreign_keyContext : public Alter_statementContext {
  public:
    Alter_table_add_foreign_keyContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<IdentifiersContext *> identifiers();
    IdentifiersContext* identifiers(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Alter_table_add_uniqueContext : public Alter_statementContext {
  public:
    Alter_table_add_uniqueContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    IdentifiersContext *identifiers();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Alter_drop_indexContext : public Alter_statementContext {
  public:
    Alter_drop_indexContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Alter_add_indexContext : public Alter_statementContext {
  public:
    Alter_add_indexContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    IdentifiersContext *identifiers();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Alter_table_drop_foreign_keyContext : public Alter_statementContext {
  public:
    Alter_table_drop_foreign_keyContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Alter_table_add_pkContext : public Alter_statementContext {
  public:
    Alter_table_add_pkContext(Alter_statementContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    IdentifiersContext *identifiers();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Alter_statementContext* alter_statement();

  class  Field_listContext : public antlr4::ParserRuleContext {
  public:
    Field_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FieldContext *> field();
    FieldContext* field(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Field_listContext* field_list();

  class  FieldContext : public antlr4::ParserRuleContext {
  public:
    FieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FieldContext() = default;
    void copyFrom(FieldContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Primary_key_fieldContext : public FieldContext {
  public:
    Primary_key_fieldContext(FieldContext *ctx);

    IdentifiersContext *identifiers();
    antlr4::tree::TerminalNode *Identifier();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Foreign_key_fieldContext : public FieldContext {
  public:
    Foreign_key_fieldContext(FieldContext *ctx);

    std::vector<IdentifiersContext *> identifiers();
    IdentifiersContext* identifiers(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Normal_fieldContext : public FieldContext {
  public:
    Normal_fieldContext(FieldContext *ctx);

    antlr4::tree::TerminalNode *Identifier();
    Type_Context *type_();
    antlr4::tree::TerminalNode *Null();
    ValueContext *value();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FieldContext* field();

  class  Type_Context : public antlr4::ParserRuleContext {
  public:
    Type_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Integer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_Context* type_();

  class  OrderContext : public antlr4::ParserRuleContext {
  public:
    OrderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrderContext* order();

  class  Value_listsContext : public antlr4::ParserRuleContext {
  public:
    Value_listsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Value_listContext *> value_list();
    Value_listContext* value_list(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Value_listsContext* value_lists();

  class  Value_listContext : public antlr4::ParserRuleContext {
  public:
    Value_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Value_listContext* value_list();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Integer();
    antlr4::tree::TerminalNode *String();
    antlr4::tree::TerminalNode *Float();
    antlr4::tree::TerminalNode *Null();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueContext* value();

  class  Where_and_clauseContext : public antlr4::ParserRuleContext {
  public:
    Where_and_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Where_clauseContext *> where_clause();
    Where_clauseContext* where_clause(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Where_and_clauseContext* where_and_clause();

  class  Where_clauseContext : public antlr4::ParserRuleContext {
  public:
    Where_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Where_clauseContext() = default;
    void copyFrom(Where_clauseContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Where_in_listContext : public Where_clauseContext {
  public:
    Where_in_listContext(Where_clauseContext *ctx);

    ColumnContext *column();
    Value_listContext *value_list();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Where_operator_selectContext : public Where_clauseContext {
  public:
    Where_operator_selectContext(Where_clauseContext *ctx);

    ColumnContext *column();
    Operator_Context *operator_();
    Select_tableContext *select_table();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Where_nullContext : public Where_clauseContext {
  public:
    Where_nullContext(Where_clauseContext *ctx);

    ColumnContext *column();
    antlr4::tree::TerminalNode *Null();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Where_operator_expressionContext : public Where_clauseContext {
  public:
    Where_operator_expressionContext(Where_clauseContext *ctx);

    ColumnContext *column();
    Operator_Context *operator_();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Where_in_selectContext : public Where_clauseContext {
  public:
    Where_in_selectContext(Where_clauseContext *ctx);

    ColumnContext *column();
    Select_tableContext *select_table();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Where_like_stringContext : public Where_clauseContext {
  public:
    Where_like_stringContext(Where_clauseContext *ctx);

    ColumnContext *column();
    antlr4::tree::TerminalNode *String();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Where_clauseContext* where_clause();

  class  ColumnContext : public antlr4::ParserRuleContext {
  public:
    ColumnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnContext* column();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ValueContext *value();
    ColumnContext *column();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  Set_clauseContext : public antlr4::ParserRuleContext {
  public:
    Set_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EqualOrAssign();
    antlr4::tree::TerminalNode* EqualOrAssign(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Set_clauseContext* set_clause();

  class  SelectorsContext : public antlr4::ParserRuleContext {
  public:
    SelectorsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SelectorContext *> selector();
    SelectorContext* selector(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorsContext* selectors();

  class  SelectorContext : public antlr4::ParserRuleContext {
  public:
    SelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ColumnContext *column();
    AggregatorContext *aggregator();
    antlr4::tree::TerminalNode *Count();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorContext* selector();

  class  IdentifiersContext : public antlr4::ParserRuleContext {
  public:
    IdentifiersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifiersContext* identifiers();

  class  Operator_Context : public antlr4::ParserRuleContext {
  public:
    Operator_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EqualOrAssign();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *GreaterEqual();
    antlr4::tree::TerminalNode *NotEqual();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Operator_Context* operator_();

  class  AggregatorContext : public antlr4::ParserRuleContext {
  public:
    AggregatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Count();
    antlr4::tree::TerminalNode *Average();
    antlr4::tree::TerminalNode *Max();
    antlr4::tree::TerminalNode *Min();
    antlr4::tree::TerminalNode *Sum();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AggregatorContext* aggregator();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

