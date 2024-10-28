
// Generated from ./src/grammar/SQL.g4 by ANTLR 4.13.1


#include "SQLVisitor.h"

#include "SQLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SQLParserStaticData final {
  SQLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SQLParserStaticData(const SQLParserStaticData&) = delete;
  SQLParserStaticData(SQLParserStaticData&&) = delete;
  SQLParserStaticData& operator=(const SQLParserStaticData&) = delete;
  SQLParserStaticData& operator=(SQLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sqlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
SQLParserStaticData *sqlParserStaticData = nullptr;

void sqlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sqlParserStaticData != nullptr) {
    return;
  }
#else
  assert(sqlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SQLParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "db_statement", "table_statement", "select_table", 
      "alter_statement", "field_list", "field", "type_", "order", "value_lists", 
      "value_list", "value", "where_and_clause", "where_clause", "column", 
      "expression", "set_clause", "selectors", "selector", "identifiers", 
      "operator_", "aggregator"
    },
    std::vector<std::string>{
      "", "';'", "'CREATE'", "'DATABASE'", "'DROP'", "'SHOW'", "'DATABASES'", 
      "'USE'", "'TABLES'", "'INDEXES'", "'TABLE'", "'('", "')'", "'DESC'", 
      "'LOAD'", "'DATA'", "'INFILE'", "'INTO'", "'FIELDS'", "'TERMINATED'", 
      "'BY'", "'INSERT'", "'VALUES'", "'DELETE'", "'FROM'", "'WHERE'", "'UPDATE'", 
      "'SET'", "'SELECT'", "'GROUP'", "'ORDER'", "'LIMIT'", "'OFFSET'", 
      "'ALTER'", "'ADD'", "'INDEX'", "'PRIMARY'", "'KEY'", "'FOREIGN'", 
      "'CONSTRAINT'", "'REFERENCES'", "'UNIQUE'", "','", "'NOT'", "'DEFAULT'", 
      "'INT'", "'VARCHAR'", "'FLOAT'", "'ASC'", "'AND'", "'IS'", "'IN'", 
      "'LIKE'", "'.'", "'*'", "'='", "'<'", "'<='", "'>'", "'>='", "'<>'", 
      "'COUNT'", "'AVG'", "'MAX'", "'MIN'", "'SUM'", "'NULL'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "EqualOrAssign", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "NotEqual", "Count", "Average", "Max", "Min", "Sum", "Null", "Identifier", 
      "Integer", "String", "Float", "Whitespace", "Annotation"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,72,417,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,1,0,5,0,48,8,0,10,0,12,0,51,9,0,1,0,1,0,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,68,8,1,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,84,8,2,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,119,8,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,3,3,129,8,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,137,8,4,1,4,1,4,1,
  	4,3,4,142,8,4,1,4,1,4,1,4,1,4,3,4,148,8,4,3,4,150,8,4,1,4,1,4,1,4,1,4,
  	3,4,156,8,4,3,4,158,8,4,1,5,1,5,1,5,1,5,1,5,1,5,3,5,166,8,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,185,8,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,200,8,5,3,5,202,
  	8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,216,8,5,3,5,218,
  	8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,3,5,237,8,5,1,5,1,5,1,5,1,5,3,5,243,8,5,1,6,1,6,1,6,5,6,248,8,6,10,
  	6,12,6,251,9,6,1,7,1,7,1,7,1,7,3,7,257,8,7,1,7,1,7,3,7,261,8,7,1,7,1,
  	7,1,7,3,7,266,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,275,8,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,3,7,286,8,7,1,8,1,8,1,8,1,8,1,8,1,8,3,8,294,8,
  	8,1,9,1,9,1,10,1,10,1,10,5,10,301,8,10,10,10,12,10,304,9,10,1,11,1,11,
  	1,11,1,11,5,11,310,8,11,10,11,12,11,313,9,11,1,11,1,11,1,12,1,12,1,13,
  	1,13,1,13,5,13,322,8,13,10,13,12,13,325,9,13,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,340,8,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,
  	358,8,14,1,15,1,15,3,15,362,8,15,1,15,1,15,1,16,1,16,3,16,368,8,16,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,5,17,377,8,17,10,17,12,17,380,9,17,1,
  	18,1,18,1,18,1,18,5,18,386,8,18,10,18,12,18,389,9,18,3,18,391,8,18,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,403,8,19,1,20,1,
  	20,1,20,5,20,408,8,20,10,20,12,20,411,9,20,1,21,1,21,1,22,1,22,1,22,0,
  	0,23,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	0,4,2,0,13,13,48,48,2,0,66,66,68,70,1,0,55,60,1,0,61,65,456,0,49,1,0,
  	0,0,2,67,1,0,0,0,4,83,1,0,0,0,6,128,1,0,0,0,8,130,1,0,0,0,10,242,1,0,
  	0,0,12,244,1,0,0,0,14,285,1,0,0,0,16,293,1,0,0,0,18,295,1,0,0,0,20,297,
  	1,0,0,0,22,305,1,0,0,0,24,316,1,0,0,0,26,318,1,0,0,0,28,357,1,0,0,0,30,
  	361,1,0,0,0,32,367,1,0,0,0,34,369,1,0,0,0,36,390,1,0,0,0,38,402,1,0,0,
  	0,40,404,1,0,0,0,42,412,1,0,0,0,44,414,1,0,0,0,46,48,3,2,1,0,47,46,1,
  	0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,52,1,0,0,0,51,49,1,
  	0,0,0,52,53,5,0,0,1,53,1,1,0,0,0,54,55,3,4,2,0,55,56,5,1,0,0,56,68,1,
  	0,0,0,57,58,3,6,3,0,58,59,5,1,0,0,59,68,1,0,0,0,60,61,3,10,5,0,61,62,
  	5,1,0,0,62,68,1,0,0,0,63,64,5,72,0,0,64,68,5,1,0,0,65,66,5,66,0,0,66,
  	68,5,1,0,0,67,54,1,0,0,0,67,57,1,0,0,0,67,60,1,0,0,0,67,63,1,0,0,0,67,
  	65,1,0,0,0,68,3,1,0,0,0,69,70,5,2,0,0,70,71,5,3,0,0,71,84,5,67,0,0,72,
  	73,5,4,0,0,73,74,5,3,0,0,74,84,5,67,0,0,75,76,5,5,0,0,76,84,5,6,0,0,77,
  	78,5,7,0,0,78,84,5,67,0,0,79,80,5,5,0,0,80,84,5,8,0,0,81,82,5,5,0,0,82,
  	84,5,9,0,0,83,69,1,0,0,0,83,72,1,0,0,0,83,75,1,0,0,0,83,77,1,0,0,0,83,
  	79,1,0,0,0,83,81,1,0,0,0,84,5,1,0,0,0,85,86,5,2,0,0,86,87,5,10,0,0,87,
  	88,5,67,0,0,88,89,5,11,0,0,89,90,3,12,6,0,90,91,5,12,0,0,91,129,1,0,0,
  	0,92,93,5,4,0,0,93,94,5,10,0,0,94,129,5,67,0,0,95,96,5,13,0,0,96,129,
  	5,67,0,0,97,98,5,14,0,0,98,99,5,15,0,0,99,100,5,16,0,0,100,101,5,69,0,
  	0,101,102,5,17,0,0,102,103,5,10,0,0,103,104,5,67,0,0,104,105,5,18,0,0,
  	105,106,5,19,0,0,106,107,5,20,0,0,107,129,5,69,0,0,108,109,5,21,0,0,109,
  	110,5,17,0,0,110,111,5,67,0,0,111,112,5,22,0,0,112,129,3,20,10,0,113,
  	114,5,23,0,0,114,115,5,24,0,0,115,118,5,67,0,0,116,117,5,25,0,0,117,119,
  	3,26,13,0,118,116,1,0,0,0,118,119,1,0,0,0,119,129,1,0,0,0,120,121,5,26,
  	0,0,121,122,5,67,0,0,122,123,5,27,0,0,123,124,3,34,17,0,124,125,5,25,
  	0,0,125,126,3,26,13,0,126,129,1,0,0,0,127,129,3,8,4,0,128,85,1,0,0,0,
  	128,92,1,0,0,0,128,95,1,0,0,0,128,97,1,0,0,0,128,108,1,0,0,0,128,113,
  	1,0,0,0,128,120,1,0,0,0,128,127,1,0,0,0,129,7,1,0,0,0,130,131,5,28,0,
  	0,131,132,3,36,18,0,132,133,5,24,0,0,133,136,3,40,20,0,134,135,5,25,0,
  	0,135,137,3,26,13,0,136,134,1,0,0,0,136,137,1,0,0,0,137,141,1,0,0,0,138,
  	139,5,29,0,0,139,140,5,20,0,0,140,142,3,30,15,0,141,138,1,0,0,0,141,142,
  	1,0,0,0,142,149,1,0,0,0,143,144,5,30,0,0,144,145,5,20,0,0,145,147,3,30,
  	15,0,146,148,3,18,9,0,147,146,1,0,0,0,147,148,1,0,0,0,148,150,1,0,0,0,
  	149,143,1,0,0,0,149,150,1,0,0,0,150,157,1,0,0,0,151,152,5,31,0,0,152,
  	155,5,68,0,0,153,154,5,32,0,0,154,156,5,68,0,0,155,153,1,0,0,0,155,156,
  	1,0,0,0,156,158,1,0,0,0,157,151,1,0,0,0,157,158,1,0,0,0,158,9,1,0,0,0,
  	159,160,5,33,0,0,160,161,5,10,0,0,161,162,5,67,0,0,162,163,5,34,0,0,163,
  	165,5,35,0,0,164,166,5,67,0,0,165,164,1,0,0,0,165,166,1,0,0,0,166,167,
  	1,0,0,0,167,168,5,11,0,0,168,169,3,40,20,0,169,170,5,12,0,0,170,243,1,
  	0,0,0,171,172,5,33,0,0,172,173,5,10,0,0,173,174,5,67,0,0,174,175,5,4,
  	0,0,175,176,5,35,0,0,176,243,5,67,0,0,177,178,5,33,0,0,178,179,5,10,0,
  	0,179,180,5,67,0,0,180,181,5,4,0,0,181,182,5,36,0,0,182,184,5,37,0,0,
  	183,185,5,67,0,0,184,183,1,0,0,0,184,185,1,0,0,0,185,243,1,0,0,0,186,
  	187,5,33,0,0,187,188,5,10,0,0,188,189,5,67,0,0,189,190,5,4,0,0,190,191,
  	5,38,0,0,191,192,5,37,0,0,192,243,5,67,0,0,193,194,5,33,0,0,194,195,5,
  	10,0,0,195,196,5,67,0,0,196,201,5,34,0,0,197,199,5,39,0,0,198,200,5,67,
  	0,0,199,198,1,0,0,0,199,200,1,0,0,0,200,202,1,0,0,0,201,197,1,0,0,0,201,
  	202,1,0,0,0,202,203,1,0,0,0,203,204,5,36,0,0,204,205,5,37,0,0,205,206,
  	5,11,0,0,206,207,3,40,20,0,207,208,5,12,0,0,208,243,1,0,0,0,209,210,5,
  	33,0,0,210,211,5,10,0,0,211,212,5,67,0,0,212,217,5,34,0,0,213,215,5,39,
  	0,0,214,216,5,67,0,0,215,214,1,0,0,0,215,216,1,0,0,0,216,218,1,0,0,0,
  	217,213,1,0,0,0,217,218,1,0,0,0,218,219,1,0,0,0,219,220,5,38,0,0,220,
  	221,5,37,0,0,221,222,5,11,0,0,222,223,3,40,20,0,223,224,5,12,0,0,224,
  	225,5,40,0,0,225,226,5,67,0,0,226,227,5,11,0,0,227,228,3,40,20,0,228,
  	229,5,12,0,0,229,243,1,0,0,0,230,231,5,33,0,0,231,232,5,10,0,0,232,233,
  	5,67,0,0,233,234,5,34,0,0,234,236,5,41,0,0,235,237,5,67,0,0,236,235,1,
  	0,0,0,236,237,1,0,0,0,237,238,1,0,0,0,238,239,5,11,0,0,239,240,3,40,20,
  	0,240,241,5,12,0,0,241,243,1,0,0,0,242,159,1,0,0,0,242,171,1,0,0,0,242,
  	177,1,0,0,0,242,186,1,0,0,0,242,193,1,0,0,0,242,209,1,0,0,0,242,230,1,
  	0,0,0,243,11,1,0,0,0,244,249,3,14,7,0,245,246,5,42,0,0,246,248,3,14,7,
  	0,247,245,1,0,0,0,248,251,1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,
  	13,1,0,0,0,251,249,1,0,0,0,252,253,5,67,0,0,253,256,3,16,8,0,254,255,
  	5,43,0,0,255,257,5,66,0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,260,1,0,
  	0,0,258,259,5,44,0,0,259,261,3,24,12,0,260,258,1,0,0,0,260,261,1,0,0,
  	0,261,286,1,0,0,0,262,263,5,36,0,0,263,265,5,37,0,0,264,266,5,67,0,0,
  	265,264,1,0,0,0,265,266,1,0,0,0,266,267,1,0,0,0,267,268,5,11,0,0,268,
  	269,3,40,20,0,269,270,5,12,0,0,270,286,1,0,0,0,271,272,5,38,0,0,272,274,
  	5,37,0,0,273,275,5,67,0,0,274,273,1,0,0,0,274,275,1,0,0,0,275,276,1,0,
  	0,0,276,277,5,11,0,0,277,278,3,40,20,0,278,279,5,12,0,0,279,280,5,40,
  	0,0,280,281,5,67,0,0,281,282,5,11,0,0,282,283,3,40,20,0,283,284,5,12,
  	0,0,284,286,1,0,0,0,285,252,1,0,0,0,285,262,1,0,0,0,285,271,1,0,0,0,286,
  	15,1,0,0,0,287,294,5,45,0,0,288,289,5,46,0,0,289,290,5,11,0,0,290,291,
  	5,68,0,0,291,294,5,12,0,0,292,294,5,47,0,0,293,287,1,0,0,0,293,288,1,
  	0,0,0,293,292,1,0,0,0,294,17,1,0,0,0,295,296,7,0,0,0,296,19,1,0,0,0,297,
  	302,3,22,11,0,298,299,5,42,0,0,299,301,3,22,11,0,300,298,1,0,0,0,301,
  	304,1,0,0,0,302,300,1,0,0,0,302,303,1,0,0,0,303,21,1,0,0,0,304,302,1,
  	0,0,0,305,306,5,11,0,0,306,311,3,24,12,0,307,308,5,42,0,0,308,310,3,24,
  	12,0,309,307,1,0,0,0,310,313,1,0,0,0,311,309,1,0,0,0,311,312,1,0,0,0,
  	312,314,1,0,0,0,313,311,1,0,0,0,314,315,5,12,0,0,315,23,1,0,0,0,316,317,
  	7,1,0,0,317,25,1,0,0,0,318,323,3,28,14,0,319,320,5,49,0,0,320,322,3,28,
  	14,0,321,319,1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,0,323,324,1,0,0,0,
  	324,27,1,0,0,0,325,323,1,0,0,0,326,327,3,30,15,0,327,328,3,42,21,0,328,
  	329,3,32,16,0,329,358,1,0,0,0,330,331,3,30,15,0,331,332,3,42,21,0,332,
  	333,5,11,0,0,333,334,3,8,4,0,334,335,5,12,0,0,335,358,1,0,0,0,336,337,
  	3,30,15,0,337,339,5,50,0,0,338,340,5,43,0,0,339,338,1,0,0,0,339,340,1,
  	0,0,0,340,341,1,0,0,0,341,342,5,66,0,0,342,358,1,0,0,0,343,344,3,30,15,
  	0,344,345,5,51,0,0,345,346,3,22,11,0,346,358,1,0,0,0,347,348,3,30,15,
  	0,348,349,5,51,0,0,349,350,5,11,0,0,350,351,3,8,4,0,351,352,5,12,0,0,
  	352,358,1,0,0,0,353,354,3,30,15,0,354,355,5,52,0,0,355,356,5,69,0,0,356,
  	358,1,0,0,0,357,326,1,0,0,0,357,330,1,0,0,0,357,336,1,0,0,0,357,343,1,
  	0,0,0,357,347,1,0,0,0,357,353,1,0,0,0,358,29,1,0,0,0,359,360,5,67,0,0,
  	360,362,5,53,0,0,361,359,1,0,0,0,361,362,1,0,0,0,362,363,1,0,0,0,363,
  	364,5,67,0,0,364,31,1,0,0,0,365,368,3,24,12,0,366,368,3,30,15,0,367,365,
  	1,0,0,0,367,366,1,0,0,0,368,33,1,0,0,0,369,370,5,67,0,0,370,371,5,55,
  	0,0,371,378,3,24,12,0,372,373,5,42,0,0,373,374,5,67,0,0,374,375,5,55,
  	0,0,375,377,3,24,12,0,376,372,1,0,0,0,377,380,1,0,0,0,378,376,1,0,0,0,
  	378,379,1,0,0,0,379,35,1,0,0,0,380,378,1,0,0,0,381,391,5,54,0,0,382,387,
  	3,38,19,0,383,384,5,42,0,0,384,386,3,38,19,0,385,383,1,0,0,0,386,389,
  	1,0,0,0,387,385,1,0,0,0,387,388,1,0,0,0,388,391,1,0,0,0,389,387,1,0,0,
  	0,390,381,1,0,0,0,390,382,1,0,0,0,391,37,1,0,0,0,392,403,3,30,15,0,393,
  	394,3,44,22,0,394,395,5,11,0,0,395,396,3,30,15,0,396,397,5,12,0,0,397,
  	403,1,0,0,0,398,399,5,61,0,0,399,400,5,11,0,0,400,401,5,54,0,0,401,403,
  	5,12,0,0,402,392,1,0,0,0,402,393,1,0,0,0,402,398,1,0,0,0,403,39,1,0,0,
  	0,404,409,5,67,0,0,405,406,5,42,0,0,406,408,5,67,0,0,407,405,1,0,0,0,
  	408,411,1,0,0,0,409,407,1,0,0,0,409,410,1,0,0,0,410,41,1,0,0,0,411,409,
  	1,0,0,0,412,413,7,2,0,0,413,43,1,0,0,0,414,415,7,3,0,0,415,45,1,0,0,0,
  	38,49,67,83,118,128,136,141,147,149,155,157,165,184,199,201,215,217,236,
  	242,249,256,260,265,274,285,293,302,311,323,339,357,361,367,378,387,390,
  	402,409
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sqlParserStaticData = staticData.release();
}

}

SQLParser::SQLParser(TokenStream *input) : SQLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SQLParser::SQLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SQLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sqlParserStaticData->atn, sqlParserStaticData->decisionToDFA, sqlParserStaticData->sharedContextCache, options);
}

SQLParser::~SQLParser() {
  delete _interpreter;
}

const atn::ATN& SQLParser::getATN() const {
  return *sqlParserStaticData->atn;
}

std::string SQLParser::getGrammarFileName() const {
  return "SQL.g4";
}

const std::vector<std::string>& SQLParser::getRuleNames() const {
  return sqlParserStaticData->ruleNames;
}

const dfa::Vocabulary& SQLParser::getVocabulary() const {
  return sqlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SQLParser::getSerializedATN() const {
  return sqlParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

SQLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::ProgramContext::EOF() {
  return getToken(SQLParser::EOF, 0);
}

std::vector<SQLParser::StatementContext *> SQLParser::ProgramContext::statement() {
  return getRuleContexts<SQLParser::StatementContext>();
}

SQLParser::StatementContext* SQLParser::ProgramContext::statement(size_t i) {
  return getRuleContext<SQLParser::StatementContext>(i);
}


size_t SQLParser::ProgramContext::getRuleIndex() const {
  return SQLParser::RuleProgram;
}


std::any SQLParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ProgramContext* SQLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, SQLParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8935989428) != 0) || _la == SQLParser::Null

    || _la == SQLParser::Annotation) {
      setState(46);
      statement();
      setState(51);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(52);
    match(SQLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

SQLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::Db_statementContext* SQLParser::StatementContext::db_statement() {
  return getRuleContext<SQLParser::Db_statementContext>(0);
}

SQLParser::Table_statementContext* SQLParser::StatementContext::table_statement() {
  return getRuleContext<SQLParser::Table_statementContext>(0);
}

SQLParser::Alter_statementContext* SQLParser::StatementContext::alter_statement() {
  return getRuleContext<SQLParser::Alter_statementContext>(0);
}

tree::TerminalNode* SQLParser::StatementContext::Annotation() {
  return getToken(SQLParser::Annotation, 0);
}

tree::TerminalNode* SQLParser::StatementContext::Null() {
  return getToken(SQLParser::Null, 0);
}


size_t SQLParser::StatementContext::getRuleIndex() const {
  return SQLParser::RuleStatement;
}


std::any SQLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::StatementContext* SQLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, SQLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(67);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(54);
      db_statement();
      setState(55);
      match(SQLParser::T__0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(57);
      table_statement();
      setState(58);
      match(SQLParser::T__0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(60);
      alter_statement();
      setState(61);
      match(SQLParser::T__0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(63);
      match(SQLParser::Annotation);
      setState(64);
      match(SQLParser::T__0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(65);
      match(SQLParser::Null);
      setState(66);
      match(SQLParser::T__0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Db_statementContext ------------------------------------------------------------------

SQLParser::Db_statementContext::Db_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::Db_statementContext::getRuleIndex() const {
  return SQLParser::RuleDb_statement;
}

void SQLParser::Db_statementContext::copyFrom(Db_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Show_dbsContext ------------------------------------------------------------------

SQLParser::Show_dbsContext::Show_dbsContext(Db_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Show_dbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitShow_dbs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Drop_dbContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Drop_dbContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Drop_dbContext::Drop_dbContext(Db_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Drop_dbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDrop_db(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Show_tablesContext ------------------------------------------------------------------

SQLParser::Show_tablesContext::Show_tablesContext(Db_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Show_tablesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitShow_tables(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Create_dbContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Create_dbContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Create_dbContext::Create_dbContext(Db_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Create_dbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCreate_db(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Use_dbContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Use_dbContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Use_dbContext::Use_dbContext(Db_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Use_dbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitUse_db(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Show_indexesContext ------------------------------------------------------------------

SQLParser::Show_indexesContext::Show_indexesContext(Db_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Show_indexesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitShow_indexes(this);
  else
    return visitor->visitChildren(this);
}
SQLParser::Db_statementContext* SQLParser::db_statement() {
  Db_statementContext *_localctx = _tracker.createInstance<Db_statementContext>(_ctx, getState());
  enterRule(_localctx, 4, SQLParser::RuleDb_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(83);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SQLParser::Create_dbContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(69);
      match(SQLParser::T__1);
      setState(70);
      match(SQLParser::T__2);
      setState(71);
      match(SQLParser::Identifier);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SQLParser::Drop_dbContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(72);
      match(SQLParser::T__3);
      setState(73);
      match(SQLParser::T__2);
      setState(74);
      match(SQLParser::Identifier);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SQLParser::Show_dbsContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(75);
      match(SQLParser::T__4);
      setState(76);
      match(SQLParser::T__5);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SQLParser::Use_dbContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(77);
      match(SQLParser::T__6);
      setState(78);
      match(SQLParser::Identifier);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SQLParser::Show_tablesContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(79);
      match(SQLParser::T__4);
      setState(80);
      match(SQLParser::T__7);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SQLParser::Show_indexesContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(81);
      match(SQLParser::T__4);
      setState(82);
      match(SQLParser::T__8);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Table_statementContext ------------------------------------------------------------------

SQLParser::Table_statementContext::Table_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::Table_statementContext::getRuleIndex() const {
  return SQLParser::RuleTable_statement;
}

void SQLParser::Table_statementContext::copyFrom(Table_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Load_tableContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Load_tableContext::String() {
  return getTokens(SQLParser::String);
}

tree::TerminalNode* SQLParser::Load_tableContext::String(size_t i) {
  return getToken(SQLParser::String, i);
}

tree::TerminalNode* SQLParser::Load_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Load_tableContext::Load_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Load_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitLoad_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Delete_from_tableContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Delete_from_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Where_and_clauseContext* SQLParser::Delete_from_tableContext::where_and_clause() {
  return getRuleContext<SQLParser::Where_and_clauseContext>(0);
}

SQLParser::Delete_from_tableContext::Delete_from_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Delete_from_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDelete_from_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Insert_into_tableContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Insert_into_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Value_listsContext* SQLParser::Insert_into_tableContext::value_lists() {
  return getRuleContext<SQLParser::Value_listsContext>(0);
}

SQLParser::Insert_into_tableContext::Insert_into_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Insert_into_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitInsert_into_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Create_tableContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Create_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Field_listContext* SQLParser::Create_tableContext::field_list() {
  return getRuleContext<SQLParser::Field_listContext>(0);
}

SQLParser::Create_tableContext::Create_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Create_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCreate_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Describe_tableContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Describe_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Describe_tableContext::Describe_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Describe_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDescribe_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Select_table_Context ------------------------------------------------------------------

SQLParser::Select_tableContext* SQLParser::Select_table_Context::select_table() {
  return getRuleContext<SQLParser::Select_tableContext>(0);
}

SQLParser::Select_table_Context::Select_table_Context(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Select_table_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitSelect_table_(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Drop_tableContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Drop_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Drop_tableContext::Drop_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Drop_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDrop_table(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Update_tableContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Update_tableContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Set_clauseContext* SQLParser::Update_tableContext::set_clause() {
  return getRuleContext<SQLParser::Set_clauseContext>(0);
}

SQLParser::Where_and_clauseContext* SQLParser::Update_tableContext::where_and_clause() {
  return getRuleContext<SQLParser::Where_and_clauseContext>(0);
}

SQLParser::Update_tableContext::Update_tableContext(Table_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Update_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitUpdate_table(this);
  else
    return visitor->visitChildren(this);
}
SQLParser::Table_statementContext* SQLParser::table_statement() {
  Table_statementContext *_localctx = _tracker.createInstance<Table_statementContext>(_ctx, getState());
  enterRule(_localctx, 6, SQLParser::RuleTable_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(128);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::T__1: {
        _localctx = _tracker.createInstance<SQLParser::Create_tableContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(85);
        match(SQLParser::T__1);
        setState(86);
        match(SQLParser::T__9);
        setState(87);
        match(SQLParser::Identifier);
        setState(88);
        match(SQLParser::T__10);
        setState(89);
        field_list();
        setState(90);
        match(SQLParser::T__11);
        break;
      }

      case SQLParser::T__3: {
        _localctx = _tracker.createInstance<SQLParser::Drop_tableContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(92);
        match(SQLParser::T__3);
        setState(93);
        match(SQLParser::T__9);
        setState(94);
        match(SQLParser::Identifier);
        break;
      }

      case SQLParser::T__12: {
        _localctx = _tracker.createInstance<SQLParser::Describe_tableContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(95);
        match(SQLParser::T__12);
        setState(96);
        match(SQLParser::Identifier);
        break;
      }

      case SQLParser::T__13: {
        _localctx = _tracker.createInstance<SQLParser::Load_tableContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(97);
        match(SQLParser::T__13);
        setState(98);
        match(SQLParser::T__14);
        setState(99);
        match(SQLParser::T__15);
        setState(100);
        match(SQLParser::String);
        setState(101);
        match(SQLParser::T__16);
        setState(102);
        match(SQLParser::T__9);
        setState(103);
        match(SQLParser::Identifier);
        setState(104);
        match(SQLParser::T__17);
        setState(105);
        match(SQLParser::T__18);
        setState(106);
        match(SQLParser::T__19);
        setState(107);
        match(SQLParser::String);
        break;
      }

      case SQLParser::T__20: {
        _localctx = _tracker.createInstance<SQLParser::Insert_into_tableContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(108);
        match(SQLParser::T__20);
        setState(109);
        match(SQLParser::T__16);
        setState(110);
        match(SQLParser::Identifier);
        setState(111);
        match(SQLParser::T__21);
        setState(112);
        value_lists();
        break;
      }

      case SQLParser::T__22: {
        _localctx = _tracker.createInstance<SQLParser::Delete_from_tableContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(113);
        match(SQLParser::T__22);
        setState(114);
        match(SQLParser::T__23);
        setState(115);
        match(SQLParser::Identifier);
        setState(118);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::T__24) {
          setState(116);
          match(SQLParser::T__24);
          setState(117);
          where_and_clause();
        }
        break;
      }

      case SQLParser::T__25: {
        _localctx = _tracker.createInstance<SQLParser::Update_tableContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(120);
        match(SQLParser::T__25);
        setState(121);
        match(SQLParser::Identifier);
        setState(122);
        match(SQLParser::T__26);
        setState(123);
        set_clause();
        setState(124);
        match(SQLParser::T__24);
        setState(125);
        where_and_clause();
        break;
      }

      case SQLParser::T__27: {
        _localctx = _tracker.createInstance<SQLParser::Select_table_Context>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(127);
        select_table();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Select_tableContext ------------------------------------------------------------------

SQLParser::Select_tableContext::Select_tableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::SelectorsContext* SQLParser::Select_tableContext::selectors() {
  return getRuleContext<SQLParser::SelectorsContext>(0);
}

SQLParser::IdentifiersContext* SQLParser::Select_tableContext::identifiers() {
  return getRuleContext<SQLParser::IdentifiersContext>(0);
}

SQLParser::Where_and_clauseContext* SQLParser::Select_tableContext::where_and_clause() {
  return getRuleContext<SQLParser::Where_and_clauseContext>(0);
}

std::vector<SQLParser::ColumnContext *> SQLParser::Select_tableContext::column() {
  return getRuleContexts<SQLParser::ColumnContext>();
}

SQLParser::ColumnContext* SQLParser::Select_tableContext::column(size_t i) {
  return getRuleContext<SQLParser::ColumnContext>(i);
}

std::vector<tree::TerminalNode *> SQLParser::Select_tableContext::Integer() {
  return getTokens(SQLParser::Integer);
}

tree::TerminalNode* SQLParser::Select_tableContext::Integer(size_t i) {
  return getToken(SQLParser::Integer, i);
}

SQLParser::OrderContext* SQLParser::Select_tableContext::order() {
  return getRuleContext<SQLParser::OrderContext>(0);
}


size_t SQLParser::Select_tableContext::getRuleIndex() const {
  return SQLParser::RuleSelect_table;
}


std::any SQLParser::Select_tableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitSelect_table(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Select_tableContext* SQLParser::select_table() {
  Select_tableContext *_localctx = _tracker.createInstance<Select_tableContext>(_ctx, getState());
  enterRule(_localctx, 8, SQLParser::RuleSelect_table);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(SQLParser::T__27);
    setState(131);
    selectors();
    setState(132);
    match(SQLParser::T__23);
    setState(133);
    identifiers();
    setState(136);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__24) {
      setState(134);
      match(SQLParser::T__24);
      setState(135);
      where_and_clause();
    }
    setState(141);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__28) {
      setState(138);
      match(SQLParser::T__28);
      setState(139);
      match(SQLParser::T__19);
      setState(140);
      column();
    }
    setState(149);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__29) {
      setState(143);
      match(SQLParser::T__29);
      setState(144);
      match(SQLParser::T__19);
      setState(145);
      column();
      setState(147);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::T__12

      || _la == SQLParser::T__47) {
        setState(146);
        order();
      }
    }
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__30) {
      setState(151);
      match(SQLParser::T__30);
      setState(152);
      match(SQLParser::Integer);
      setState(155);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::T__31) {
        setState(153);
        match(SQLParser::T__31);
        setState(154);
        match(SQLParser::Integer);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Alter_statementContext ------------------------------------------------------------------

SQLParser::Alter_statementContext::Alter_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::Alter_statementContext::getRuleIndex() const {
  return SQLParser::RuleAlter_statement;
}

void SQLParser::Alter_statementContext::copyFrom(Alter_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Alter_table_drop_pkContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_table_drop_pkContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_table_drop_pkContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::Alter_table_drop_pkContext::Alter_table_drop_pkContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_table_drop_pkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_drop_pk(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_add_foreign_keyContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_table_add_foreign_keyContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_table_add_foreign_keyContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

std::vector<SQLParser::IdentifiersContext *> SQLParser::Alter_table_add_foreign_keyContext::identifiers() {
  return getRuleContexts<SQLParser::IdentifiersContext>();
}

SQLParser::IdentifiersContext* SQLParser::Alter_table_add_foreign_keyContext::identifiers(size_t i) {
  return getRuleContext<SQLParser::IdentifiersContext>(i);
}

SQLParser::Alter_table_add_foreign_keyContext::Alter_table_add_foreign_keyContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_table_add_foreign_keyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_add_foreign_key(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_add_uniqueContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_table_add_uniqueContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_table_add_uniqueContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::IdentifiersContext* SQLParser::Alter_table_add_uniqueContext::identifiers() {
  return getRuleContext<SQLParser::IdentifiersContext>(0);
}

SQLParser::Alter_table_add_uniqueContext::Alter_table_add_uniqueContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_table_add_uniqueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_add_unique(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_drop_indexContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_drop_indexContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_drop_indexContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::Alter_drop_indexContext::Alter_drop_indexContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_drop_indexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_drop_index(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_add_indexContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_add_indexContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_add_indexContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::IdentifiersContext* SQLParser::Alter_add_indexContext::identifiers() {
  return getRuleContext<SQLParser::IdentifiersContext>(0);
}

SQLParser::Alter_add_indexContext::Alter_add_indexContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_add_indexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_add_index(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_drop_foreign_keyContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_table_drop_foreign_keyContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_table_drop_foreign_keyContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::Alter_table_drop_foreign_keyContext::Alter_table_drop_foreign_keyContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_table_drop_foreign_keyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_drop_foreign_key(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Alter_table_add_pkContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> SQLParser::Alter_table_add_pkContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Alter_table_add_pkContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::IdentifiersContext* SQLParser::Alter_table_add_pkContext::identifiers() {
  return getRuleContext<SQLParser::IdentifiersContext>(0);
}

SQLParser::Alter_table_add_pkContext::Alter_table_add_pkContext(Alter_statementContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Alter_table_add_pkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAlter_table_add_pk(this);
  else
    return visitor->visitChildren(this);
}
SQLParser::Alter_statementContext* SQLParser::alter_statement() {
  Alter_statementContext *_localctx = _tracker.createInstance<Alter_statementContext>(_ctx, getState());
  enterRule(_localctx, 10, SQLParser::RuleAlter_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SQLParser::Alter_add_indexContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(159);
      match(SQLParser::T__32);
      setState(160);
      match(SQLParser::T__9);
      setState(161);
      match(SQLParser::Identifier);
      setState(162);
      match(SQLParser::T__33);
      setState(163);
      match(SQLParser::T__34);
      setState(165);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::Identifier) {
        setState(164);
        match(SQLParser::Identifier);
      }
      setState(167);
      match(SQLParser::T__10);
      setState(168);
      identifiers();
      setState(169);
      match(SQLParser::T__11);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SQLParser::Alter_drop_indexContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(171);
      match(SQLParser::T__32);
      setState(172);
      match(SQLParser::T__9);
      setState(173);
      match(SQLParser::Identifier);
      setState(174);
      match(SQLParser::T__3);
      setState(175);
      match(SQLParser::T__34);
      setState(176);
      match(SQLParser::Identifier);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SQLParser::Alter_table_drop_pkContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(177);
      match(SQLParser::T__32);
      setState(178);
      match(SQLParser::T__9);
      setState(179);
      match(SQLParser::Identifier);
      setState(180);
      match(SQLParser::T__3);
      setState(181);
      match(SQLParser::T__35);
      setState(182);
      match(SQLParser::T__36);
      setState(184);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::Identifier) {
        setState(183);
        match(SQLParser::Identifier);
      }
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SQLParser::Alter_table_drop_foreign_keyContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(186);
      match(SQLParser::T__32);
      setState(187);
      match(SQLParser::T__9);
      setState(188);
      match(SQLParser::Identifier);
      setState(189);
      match(SQLParser::T__3);
      setState(190);
      match(SQLParser::T__37);
      setState(191);
      match(SQLParser::T__36);
      setState(192);
      match(SQLParser::Identifier);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SQLParser::Alter_table_add_pkContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(193);
      match(SQLParser::T__32);
      setState(194);
      match(SQLParser::T__9);
      setState(195);
      match(SQLParser::Identifier);
      setState(196);
      match(SQLParser::T__33);
      setState(201);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::T__38) {
        setState(197);
        match(SQLParser::T__38);
        setState(199);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::Identifier) {
          setState(198);
          match(SQLParser::Identifier);
        }
      }
      setState(203);
      match(SQLParser::T__35);
      setState(204);
      match(SQLParser::T__36);
      setState(205);
      match(SQLParser::T__10);
      setState(206);
      identifiers();
      setState(207);
      match(SQLParser::T__11);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SQLParser::Alter_table_add_foreign_keyContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(209);
      match(SQLParser::T__32);
      setState(210);
      match(SQLParser::T__9);
      setState(211);
      match(SQLParser::Identifier);
      setState(212);
      match(SQLParser::T__33);
      setState(217);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::T__38) {
        setState(213);
        match(SQLParser::T__38);
        setState(215);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::Identifier) {
          setState(214);
          match(SQLParser::Identifier);
        }
      }
      setState(219);
      match(SQLParser::T__37);
      setState(220);
      match(SQLParser::T__36);
      setState(221);
      match(SQLParser::T__10);
      setState(222);
      identifiers();
      setState(223);
      match(SQLParser::T__11);
      setState(224);
      match(SQLParser::T__39);
      setState(225);
      match(SQLParser::Identifier);
      setState(226);
      match(SQLParser::T__10);
      setState(227);
      identifiers();
      setState(228);
      match(SQLParser::T__11);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SQLParser::Alter_table_add_uniqueContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(230);
      match(SQLParser::T__32);
      setState(231);
      match(SQLParser::T__9);
      setState(232);
      match(SQLParser::Identifier);
      setState(233);
      match(SQLParser::T__33);
      setState(234);
      match(SQLParser::T__40);
      setState(236);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::Identifier) {
        setState(235);
        match(SQLParser::Identifier);
      }
      setState(238);
      match(SQLParser::T__10);
      setState(239);
      identifiers();
      setState(240);
      match(SQLParser::T__11);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Field_listContext ------------------------------------------------------------------

SQLParser::Field_listContext::Field_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::FieldContext *> SQLParser::Field_listContext::field() {
  return getRuleContexts<SQLParser::FieldContext>();
}

SQLParser::FieldContext* SQLParser::Field_listContext::field(size_t i) {
  return getRuleContext<SQLParser::FieldContext>(i);
}


size_t SQLParser::Field_listContext::getRuleIndex() const {
  return SQLParser::RuleField_list;
}


std::any SQLParser::Field_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitField_list(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Field_listContext* SQLParser::field_list() {
  Field_listContext *_localctx = _tracker.createInstance<Field_listContext>(_ctx, getState());
  enterRule(_localctx, 12, SQLParser::RuleField_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    field();
    setState(249);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__41) {
      setState(245);
      match(SQLParser::T__41);
      setState(246);
      field();
      setState(251);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldContext ------------------------------------------------------------------

SQLParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::FieldContext::getRuleIndex() const {
  return SQLParser::RuleField;
}

void SQLParser::FieldContext::copyFrom(FieldContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Primary_key_fieldContext ------------------------------------------------------------------

SQLParser::IdentifiersContext* SQLParser::Primary_key_fieldContext::identifiers() {
  return getRuleContext<SQLParser::IdentifiersContext>(0);
}

tree::TerminalNode* SQLParser::Primary_key_fieldContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Primary_key_fieldContext::Primary_key_fieldContext(FieldContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Primary_key_fieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitPrimary_key_field(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Foreign_key_fieldContext ------------------------------------------------------------------

std::vector<SQLParser::IdentifiersContext *> SQLParser::Foreign_key_fieldContext::identifiers() {
  return getRuleContexts<SQLParser::IdentifiersContext>();
}

SQLParser::IdentifiersContext* SQLParser::Foreign_key_fieldContext::identifiers(size_t i) {
  return getRuleContext<SQLParser::IdentifiersContext>(i);
}

std::vector<tree::TerminalNode *> SQLParser::Foreign_key_fieldContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Foreign_key_fieldContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

SQLParser::Foreign_key_fieldContext::Foreign_key_fieldContext(FieldContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Foreign_key_fieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitForeign_key_field(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Normal_fieldContext ------------------------------------------------------------------

tree::TerminalNode* SQLParser::Normal_fieldContext::Identifier() {
  return getToken(SQLParser::Identifier, 0);
}

SQLParser::Type_Context* SQLParser::Normal_fieldContext::type_() {
  return getRuleContext<SQLParser::Type_Context>(0);
}

tree::TerminalNode* SQLParser::Normal_fieldContext::Null() {
  return getToken(SQLParser::Null, 0);
}

SQLParser::ValueContext* SQLParser::Normal_fieldContext::value() {
  return getRuleContext<SQLParser::ValueContext>(0);
}

SQLParser::Normal_fieldContext::Normal_fieldContext(FieldContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Normal_fieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitNormal_field(this);
  else
    return visitor->visitChildren(this);
}
SQLParser::FieldContext* SQLParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 14, SQLParser::RuleField);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(285);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::Identifier: {
        _localctx = _tracker.createInstance<SQLParser::Normal_fieldContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(252);
        match(SQLParser::Identifier);
        setState(253);
        type_();
        setState(256);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::T__42) {
          setState(254);
          match(SQLParser::T__42);
          setState(255);
          match(SQLParser::Null);
        }
        setState(260);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::T__43) {
          setState(258);
          match(SQLParser::T__43);
          setState(259);
          value();
        }
        break;
      }

      case SQLParser::T__35: {
        _localctx = _tracker.createInstance<SQLParser::Primary_key_fieldContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(262);
        match(SQLParser::T__35);
        setState(263);
        match(SQLParser::T__36);
        setState(265);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::Identifier) {
          setState(264);
          match(SQLParser::Identifier);
        }
        setState(267);
        match(SQLParser::T__10);
        setState(268);
        identifiers();
        setState(269);
        match(SQLParser::T__11);
        break;
      }

      case SQLParser::T__37: {
        _localctx = _tracker.createInstance<SQLParser::Foreign_key_fieldContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(271);
        match(SQLParser::T__37);
        setState(272);
        match(SQLParser::T__36);
        setState(274);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::Identifier) {
          setState(273);
          match(SQLParser::Identifier);
        }
        setState(276);
        match(SQLParser::T__10);
        setState(277);
        identifiers();
        setState(278);
        match(SQLParser::T__11);
        setState(279);
        match(SQLParser::T__39);
        setState(280);
        match(SQLParser::Identifier);
        setState(281);
        match(SQLParser::T__10);
        setState(282);
        identifiers();
        setState(283);
        match(SQLParser::T__11);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_Context ------------------------------------------------------------------

SQLParser::Type_Context::Type_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::Type_Context::Integer() {
  return getToken(SQLParser::Integer, 0);
}


size_t SQLParser::Type_Context::getRuleIndex() const {
  return SQLParser::RuleType_;
}


std::any SQLParser::Type_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitType_(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Type_Context* SQLParser::type_() {
  Type_Context *_localctx = _tracker.createInstance<Type_Context>(_ctx, getState());
  enterRule(_localctx, 16, SQLParser::RuleType_);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(293);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::T__44: {
        enterOuterAlt(_localctx, 1);
        setState(287);
        match(SQLParser::T__44);
        break;
      }

      case SQLParser::T__45: {
        enterOuterAlt(_localctx, 2);
        setState(288);
        match(SQLParser::T__45);
        setState(289);
        match(SQLParser::T__10);
        setState(290);
        match(SQLParser::Integer);
        setState(291);
        match(SQLParser::T__11);
        break;
      }

      case SQLParser::T__46: {
        enterOuterAlt(_localctx, 3);
        setState(292);
        match(SQLParser::T__46);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderContext ------------------------------------------------------------------

SQLParser::OrderContext::OrderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::OrderContext::getRuleIndex() const {
  return SQLParser::RuleOrder;
}


std::any SQLParser::OrderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitOrder(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::OrderContext* SQLParser::order() {
  OrderContext *_localctx = _tracker.createInstance<OrderContext>(_ctx, getState());
  enterRule(_localctx, 18, SQLParser::RuleOrder);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    _la = _input->LA(1);
    if (!(_la == SQLParser::T__12

    || _la == SQLParser::T__47)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_listsContext ------------------------------------------------------------------

SQLParser::Value_listsContext::Value_listsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::Value_listContext *> SQLParser::Value_listsContext::value_list() {
  return getRuleContexts<SQLParser::Value_listContext>();
}

SQLParser::Value_listContext* SQLParser::Value_listsContext::value_list(size_t i) {
  return getRuleContext<SQLParser::Value_listContext>(i);
}


size_t SQLParser::Value_listsContext::getRuleIndex() const {
  return SQLParser::RuleValue_lists;
}


std::any SQLParser::Value_listsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitValue_lists(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Value_listsContext* SQLParser::value_lists() {
  Value_listsContext *_localctx = _tracker.createInstance<Value_listsContext>(_ctx, getState());
  enterRule(_localctx, 20, SQLParser::RuleValue_lists);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    value_list();
    setState(302);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__41) {
      setState(298);
      match(SQLParser::T__41);
      setState(299);
      value_list();
      setState(304);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_listContext ------------------------------------------------------------------

SQLParser::Value_listContext::Value_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::ValueContext *> SQLParser::Value_listContext::value() {
  return getRuleContexts<SQLParser::ValueContext>();
}

SQLParser::ValueContext* SQLParser::Value_listContext::value(size_t i) {
  return getRuleContext<SQLParser::ValueContext>(i);
}


size_t SQLParser::Value_listContext::getRuleIndex() const {
  return SQLParser::RuleValue_list;
}


std::any SQLParser::Value_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitValue_list(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Value_listContext* SQLParser::value_list() {
  Value_listContext *_localctx = _tracker.createInstance<Value_listContext>(_ctx, getState());
  enterRule(_localctx, 22, SQLParser::RuleValue_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    match(SQLParser::T__10);
    setState(306);
    value();
    setState(311);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__41) {
      setState(307);
      match(SQLParser::T__41);
      setState(308);
      value();
      setState(313);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(314);
    match(SQLParser::T__11);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

SQLParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::ValueContext::Integer() {
  return getToken(SQLParser::Integer, 0);
}

tree::TerminalNode* SQLParser::ValueContext::String() {
  return getToken(SQLParser::String, 0);
}

tree::TerminalNode* SQLParser::ValueContext::Float() {
  return getToken(SQLParser::Float, 0);
}

tree::TerminalNode* SQLParser::ValueContext::Null() {
  return getToken(SQLParser::Null, 0);
}


size_t SQLParser::ValueContext::getRuleIndex() const {
  return SQLParser::RuleValue;
}


std::any SQLParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ValueContext* SQLParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 24, SQLParser::RuleValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    _la = _input->LA(1);
    if (!(((((_la - 66) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 66)) & 29) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Where_and_clauseContext ------------------------------------------------------------------

SQLParser::Where_and_clauseContext::Where_and_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::Where_clauseContext *> SQLParser::Where_and_clauseContext::where_clause() {
  return getRuleContexts<SQLParser::Where_clauseContext>();
}

SQLParser::Where_clauseContext* SQLParser::Where_and_clauseContext::where_clause(size_t i) {
  return getRuleContext<SQLParser::Where_clauseContext>(i);
}


size_t SQLParser::Where_and_clauseContext::getRuleIndex() const {
  return SQLParser::RuleWhere_and_clause;
}


std::any SQLParser::Where_and_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_and_clause(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Where_and_clauseContext* SQLParser::where_and_clause() {
  Where_and_clauseContext *_localctx = _tracker.createInstance<Where_and_clauseContext>(_ctx, getState());
  enterRule(_localctx, 26, SQLParser::RuleWhere_and_clause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(318);
    where_clause();
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__48) {
      setState(319);
      match(SQLParser::T__48);
      setState(320);
      where_clause();
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Where_clauseContext ------------------------------------------------------------------

SQLParser::Where_clauseContext::Where_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::Where_clauseContext::getRuleIndex() const {
  return SQLParser::RuleWhere_clause;
}

void SQLParser::Where_clauseContext::copyFrom(Where_clauseContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Where_in_listContext ------------------------------------------------------------------

SQLParser::ColumnContext* SQLParser::Where_in_listContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

SQLParser::Value_listContext* SQLParser::Where_in_listContext::value_list() {
  return getRuleContext<SQLParser::Value_listContext>(0);
}

SQLParser::Where_in_listContext::Where_in_listContext(Where_clauseContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Where_in_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_in_list(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_operator_selectContext ------------------------------------------------------------------

SQLParser::ColumnContext* SQLParser::Where_operator_selectContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

SQLParser::Operator_Context* SQLParser::Where_operator_selectContext::operator_() {
  return getRuleContext<SQLParser::Operator_Context>(0);
}

SQLParser::Select_tableContext* SQLParser::Where_operator_selectContext::select_table() {
  return getRuleContext<SQLParser::Select_tableContext>(0);
}

SQLParser::Where_operator_selectContext::Where_operator_selectContext(Where_clauseContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Where_operator_selectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_operator_select(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_nullContext ------------------------------------------------------------------

SQLParser::ColumnContext* SQLParser::Where_nullContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

tree::TerminalNode* SQLParser::Where_nullContext::Null() {
  return getToken(SQLParser::Null, 0);
}

SQLParser::Where_nullContext::Where_nullContext(Where_clauseContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Where_nullContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_null(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_operator_expressionContext ------------------------------------------------------------------

SQLParser::ColumnContext* SQLParser::Where_operator_expressionContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

SQLParser::Operator_Context* SQLParser::Where_operator_expressionContext::operator_() {
  return getRuleContext<SQLParser::Operator_Context>(0);
}

SQLParser::ExpressionContext* SQLParser::Where_operator_expressionContext::expression() {
  return getRuleContext<SQLParser::ExpressionContext>(0);
}

SQLParser::Where_operator_expressionContext::Where_operator_expressionContext(Where_clauseContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Where_operator_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_operator_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_in_selectContext ------------------------------------------------------------------

SQLParser::ColumnContext* SQLParser::Where_in_selectContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

SQLParser::Select_tableContext* SQLParser::Where_in_selectContext::select_table() {
  return getRuleContext<SQLParser::Select_tableContext>(0);
}

SQLParser::Where_in_selectContext::Where_in_selectContext(Where_clauseContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Where_in_selectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_in_select(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Where_like_stringContext ------------------------------------------------------------------

SQLParser::ColumnContext* SQLParser::Where_like_stringContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

tree::TerminalNode* SQLParser::Where_like_stringContext::String() {
  return getToken(SQLParser::String, 0);
}

SQLParser::Where_like_stringContext::Where_like_stringContext(Where_clauseContext *ctx) { copyFrom(ctx); }


std::any SQLParser::Where_like_stringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhere_like_string(this);
  else
    return visitor->visitChildren(this);
}
SQLParser::Where_clauseContext* SQLParser::where_clause() {
  Where_clauseContext *_localctx = _tracker.createInstance<Where_clauseContext>(_ctx, getState());
  enterRule(_localctx, 28, SQLParser::RuleWhere_clause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(357);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SQLParser::Where_operator_expressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(326);
      column();
      setState(327);
      operator_();
      setState(328);
      expression();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SQLParser::Where_operator_selectContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(330);
      column();
      setState(331);
      operator_();
      setState(332);
      match(SQLParser::T__10);
      setState(333);
      select_table();
      setState(334);
      match(SQLParser::T__11);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SQLParser::Where_nullContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(336);
      column();
      setState(337);
      match(SQLParser::T__49);
      setState(339);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SQLParser::T__42) {
        setState(338);
        match(SQLParser::T__42);
      }
      setState(341);
      match(SQLParser::Null);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SQLParser::Where_in_listContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(343);
      column();
      setState(344);
      match(SQLParser::T__50);
      setState(345);
      value_list();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SQLParser::Where_in_selectContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(347);
      column();
      setState(348);
      match(SQLParser::T__50);
      setState(349);
      match(SQLParser::T__10);
      setState(350);
      select_table();
      setState(351);
      match(SQLParser::T__11);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SQLParser::Where_like_stringContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(353);
      column();
      setState(354);
      match(SQLParser::T__51);
      setState(355);
      match(SQLParser::String);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnContext ------------------------------------------------------------------

SQLParser::ColumnContext::ColumnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SQLParser::ColumnContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::ColumnContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}


size_t SQLParser::ColumnContext::getRuleIndex() const {
  return SQLParser::RuleColumn;
}


std::any SQLParser::ColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitColumn(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ColumnContext* SQLParser::column() {
  ColumnContext *_localctx = _tracker.createInstance<ColumnContext>(_ctx, getState());
  enterRule(_localctx, 30, SQLParser::RuleColumn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(359);
      match(SQLParser::Identifier);
      setState(360);
      match(SQLParser::T__52);
      break;
    }

    default:
      break;
    }
    setState(363);
    match(SQLParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

SQLParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::ValueContext* SQLParser::ExpressionContext::value() {
  return getRuleContext<SQLParser::ValueContext>(0);
}

SQLParser::ColumnContext* SQLParser::ExpressionContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}


size_t SQLParser::ExpressionContext::getRuleIndex() const {
  return SQLParser::RuleExpression;
}


std::any SQLParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ExpressionContext* SQLParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, SQLParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(367);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::Null:
      case SQLParser::Integer:
      case SQLParser::String:
      case SQLParser::Float: {
        enterOuterAlt(_localctx, 1);
        setState(365);
        value();
        break;
      }

      case SQLParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(366);
        column();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Set_clauseContext ------------------------------------------------------------------

SQLParser::Set_clauseContext::Set_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SQLParser::Set_clauseContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::Set_clauseContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}

std::vector<tree::TerminalNode *> SQLParser::Set_clauseContext::EqualOrAssign() {
  return getTokens(SQLParser::EqualOrAssign);
}

tree::TerminalNode* SQLParser::Set_clauseContext::EqualOrAssign(size_t i) {
  return getToken(SQLParser::EqualOrAssign, i);
}

std::vector<SQLParser::ValueContext *> SQLParser::Set_clauseContext::value() {
  return getRuleContexts<SQLParser::ValueContext>();
}

SQLParser::ValueContext* SQLParser::Set_clauseContext::value(size_t i) {
  return getRuleContext<SQLParser::ValueContext>(i);
}


size_t SQLParser::Set_clauseContext::getRuleIndex() const {
  return SQLParser::RuleSet_clause;
}


std::any SQLParser::Set_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitSet_clause(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Set_clauseContext* SQLParser::set_clause() {
  Set_clauseContext *_localctx = _tracker.createInstance<Set_clauseContext>(_ctx, getState());
  enterRule(_localctx, 34, SQLParser::RuleSet_clause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    match(SQLParser::Identifier);
    setState(370);
    match(SQLParser::EqualOrAssign);
    setState(371);
    value();
    setState(378);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__41) {
      setState(372);
      match(SQLParser::T__41);
      setState(373);
      match(SQLParser::Identifier);
      setState(374);
      match(SQLParser::EqualOrAssign);
      setState(375);
      value();
      setState(380);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorsContext ------------------------------------------------------------------

SQLParser::SelectorsContext::SelectorsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::SelectorContext *> SQLParser::SelectorsContext::selector() {
  return getRuleContexts<SQLParser::SelectorContext>();
}

SQLParser::SelectorContext* SQLParser::SelectorsContext::selector(size_t i) {
  return getRuleContext<SQLParser::SelectorContext>(i);
}


size_t SQLParser::SelectorsContext::getRuleIndex() const {
  return SQLParser::RuleSelectors;
}


std::any SQLParser::SelectorsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitSelectors(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::SelectorsContext* SQLParser::selectors() {
  SelectorsContext *_localctx = _tracker.createInstance<SelectorsContext>(_ctx, getState());
  enterRule(_localctx, 36, SQLParser::RuleSelectors);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(390);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::T__53: {
        enterOuterAlt(_localctx, 1);
        setState(381);
        match(SQLParser::T__53);
        break;
      }

      case SQLParser::Count:
      case SQLParser::Average:
      case SQLParser::Max:
      case SQLParser::Min:
      case SQLParser::Sum:
      case SQLParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(382);
        selector();
        setState(387);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SQLParser::T__41) {
          setState(383);
          match(SQLParser::T__41);
          setState(384);
          selector();
          setState(389);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContext ------------------------------------------------------------------

SQLParser::SelectorContext::SelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::ColumnContext* SQLParser::SelectorContext::column() {
  return getRuleContext<SQLParser::ColumnContext>(0);
}

SQLParser::AggregatorContext* SQLParser::SelectorContext::aggregator() {
  return getRuleContext<SQLParser::AggregatorContext>(0);
}

tree::TerminalNode* SQLParser::SelectorContext::Count() {
  return getToken(SQLParser::Count, 0);
}


size_t SQLParser::SelectorContext::getRuleIndex() const {
  return SQLParser::RuleSelector;
}


std::any SQLParser::SelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitSelector(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::SelectorContext* SQLParser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 38, SQLParser::RuleSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(402);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(392);
      column();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(393);
      aggregator();
      setState(394);
      match(SQLParser::T__10);
      setState(395);
      column();
      setState(396);
      match(SQLParser::T__11);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(398);
      match(SQLParser::Count);
      setState(399);
      match(SQLParser::T__10);
      setState(400);
      match(SQLParser::T__53);
      setState(401);
      match(SQLParser::T__11);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifiersContext ------------------------------------------------------------------

SQLParser::IdentifiersContext::IdentifiersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SQLParser::IdentifiersContext::Identifier() {
  return getTokens(SQLParser::Identifier);
}

tree::TerminalNode* SQLParser::IdentifiersContext::Identifier(size_t i) {
  return getToken(SQLParser::Identifier, i);
}


size_t SQLParser::IdentifiersContext::getRuleIndex() const {
  return SQLParser::RuleIdentifiers;
}


std::any SQLParser::IdentifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitIdentifiers(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::IdentifiersContext* SQLParser::identifiers() {
  IdentifiersContext *_localctx = _tracker.createInstance<IdentifiersContext>(_ctx, getState());
  enterRule(_localctx, 40, SQLParser::RuleIdentifiers);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(404);
    match(SQLParser::Identifier);
    setState(409);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__41) {
      setState(405);
      match(SQLParser::T__41);
      setState(406);
      match(SQLParser::Identifier);
      setState(411);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Operator_Context ------------------------------------------------------------------

SQLParser::Operator_Context::Operator_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::Operator_Context::EqualOrAssign() {
  return getToken(SQLParser::EqualOrAssign, 0);
}

tree::TerminalNode* SQLParser::Operator_Context::Less() {
  return getToken(SQLParser::Less, 0);
}

tree::TerminalNode* SQLParser::Operator_Context::LessEqual() {
  return getToken(SQLParser::LessEqual, 0);
}

tree::TerminalNode* SQLParser::Operator_Context::Greater() {
  return getToken(SQLParser::Greater, 0);
}

tree::TerminalNode* SQLParser::Operator_Context::GreaterEqual() {
  return getToken(SQLParser::GreaterEqual, 0);
}

tree::TerminalNode* SQLParser::Operator_Context::NotEqual() {
  return getToken(SQLParser::NotEqual, 0);
}


size_t SQLParser::Operator_Context::getRuleIndex() const {
  return SQLParser::RuleOperator_;
}


std::any SQLParser::Operator_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitOperator_(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::Operator_Context* SQLParser::operator_() {
  Operator_Context *_localctx = _tracker.createInstance<Operator_Context>(_ctx, getState());
  enterRule(_localctx, 42, SQLParser::RuleOperator_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(412);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2269814212194729984) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregatorContext ------------------------------------------------------------------

SQLParser::AggregatorContext::AggregatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::AggregatorContext::Count() {
  return getToken(SQLParser::Count, 0);
}

tree::TerminalNode* SQLParser::AggregatorContext::Average() {
  return getToken(SQLParser::Average, 0);
}

tree::TerminalNode* SQLParser::AggregatorContext::Max() {
  return getToken(SQLParser::Max, 0);
}

tree::TerminalNode* SQLParser::AggregatorContext::Min() {
  return getToken(SQLParser::Min, 0);
}

tree::TerminalNode* SQLParser::AggregatorContext::Sum() {
  return getToken(SQLParser::Sum, 0);
}


size_t SQLParser::AggregatorContext::getRuleIndex() const {
  return SQLParser::RuleAggregator;
}


std::any SQLParser::AggregatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAggregator(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::AggregatorContext* SQLParser::aggregator() {
  AggregatorContext *_localctx = _tracker.createInstance<AggregatorContext>(_ctx, getState());
  enterRule(_localctx, 44, SQLParser::RuleAggregator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    _la = _input->LA(1);
    if (!(((((_la - 61) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 61)) & 31) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void SQLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sqlParserInitialize();
#else
  ::antlr4::internal::call_once(sqlParserOnceFlag, sqlParserInitialize);
#endif
}
