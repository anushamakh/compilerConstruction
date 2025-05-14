#ifndef AST_H
#define AST_H

typedef struct Symbol Symbol;
typedef struct HashTable HashTable;
typedef struct SymbolTableStack SymbolTableStack;
extern Symbol* lookupSymbol(char* name);
extern void updateSymbolValueAndBase(char* name, char* value, char* base);
typedef enum {
   
    NODE_NUMBER,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    NODE_VAR_DECL,
    NODE_ID,
    NODE_STRING,
    NODE_CHAR,
    NODE_TYPE,
    NODE_ASSIGN,
    NODE_WHILE,
    NODE_PRINT,
    NODE_SCAN,
    NODE_FORMAT,
    NODE_STRING_CONCAT,
    NODE_IF,
    NODE_FOR,
    NODE_EQ,
    NODE_NEQ,
    NODE_GT,
    NODE_LT,
    NODE_GTE,
    NODE_LTE,
    NODE_ADD_ASSIGN,
    NODE_SUB_ASSIGN,
    NODE_MUL_ASSIGN,
    NODE_DIV_ASSIGN,
    NODE_MOD_ASSIGN,
    NODE_PROGRAM,
    NODE_STATEMENT_LIST,
    NODE_STATEMENT_LIST_2,
    NODE_BINARY
} NodeType;

typedef struct ASTNode {
    NodeType type;
    int base;  
    union {
        int value;
        char* str_value;
        char char_value;
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
        } children;
        struct {
            char* var_name;
            struct ASTNode* var_type;
        } var_decl;
        struct {
            struct ASTNode* target;
            struct ASTNode* expr;
        } assign;
        struct {
            struct ASTNode* cond;
            struct ASTNode* then_block;
            struct ASTNode* else_block;
            struct ASTNode* update;
        } control;
        struct {
            struct ASTNode* init;
            struct ASTNode* cond;
            struct ASTNode* upd;
            struct ASTNode* amount;
            struct ASTNode* stmt;
        } for_control;
        struct {
            struct ASTNode* format_str;
            struct ASTNode* args;
        } io;
    } data;
} ASTNode;


ASTNode* createNumberNode(int value);
ASTNode* createOperatorNode(NodeType type, ASTNode* left, ASTNode* right);
void printAST(ASTNode* node);
void freeAST(ASTNode* node);

ASTNode* createVarDeclNode(const char* name, ASTNode* type);
ASTNode* createIDNode(const char* name);
ASTNode* createStringNode(const char* str);
ASTNode* createCharNode(char *c);
ASTNode* createTypeNode(const char* type);
ASTNode* createStringConcatNode(const char* str, ASTNode* next);

ASTNode* createIfNode(ASTNode* cond, ASTNode* then_block, ASTNode* else_block);
ASTNode* createForNode(ASTNode* init, ASTNode* cond, ASTNode* update, ASTNode* amount, ASTNode* body);
ASTNode* createWhileNode(ASTNode* cond, ASTNode* body);

ASTNode* createAssignNode(ASTNode* target, NodeType type, ASTNode* expr);

ASTNode* createPrintNode(ASTNode* format_str, ASTNode* args);
ASTNode* createScanNode(ASTNode* format, ASTNode* vars);
ASTNode* createFormatNode(ASTNode* node);

ASTNode* createProgramNode(ASTNode* declarations, ASTNode* statements);
ASTNode* createStatementListNode(ASTNode* stmt, ASTNode* next);
ASTNode* createStatementListNode2(ASTNode* stmt, ASTNode* next);

void interpretAST(ASTNode* node);
int evaluateExpr(ASTNode* node);
char* evaluateString(ASTNode* node);
static const char* get_print_arg_value(ASTNode* node);
static void print_format(ASTNode* format_str, ASTNode* args, int* arg_idx);
void updateVariableValue(ASTNode* target, int value, int base);

#endif
