%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
ASTNode* root = NULL;
void yyerror(const char* s);
int yylex(void);
extern FILE* yyin;
extern FILE* yyout;

int scan_count=0;
int print_count=0;

#define HASH_TABLE_SIZE 101

typedef struct Symbol {
    char* name;
    char* type;
    char* value; 
     char* base; 
     int initialized;
    struct Symbol* next;
} Symbol;

typedef struct HashTable {
    Symbol* table[HASH_TABLE_SIZE];
} HashTable;

typedef struct SymbolTableStack {
    HashTable* hashTable;
} SymbolTableStack;

SymbolTableStack* symbolTableStack = NULL;
char currentType[20];


int hash(char* name) {
    unsigned long hash = 5381;
    int c;
    while ((c = *name++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_TABLE_SIZE;
}

void insertSymbol(char* name, char* type, char* value, char* base) {
    if (symbolTableStack == NULL) {
        symbolTableStack = (SymbolTableStack*)malloc(sizeof(SymbolTableStack));
        symbolTableStack->hashTable = (HashTable*)malloc(sizeof(HashTable));
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
            symbolTableStack->hashTable->table[i] = NULL;
    }

    HashTable* currentTable = symbolTableStack->hashTable;
    int index = hash(name);

    Symbol* existing = currentTable->table[index];
    while (existing != NULL) {
        if (strcmp(existing->name, name) == 0) {
            char buf[128];
            snprintf(buf, sizeof(buf), "Duplicate declaration of variable '%s'", name);
            yyerror(buf);
            return; 
        }
        existing = existing->next;
    }

    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    newSymbol->name = strdup(name);
    newSymbol->type = strdup(type);
    newSymbol->value = value ? strdup(value) : NULL;
    newSymbol->base = base ? strdup(base) : NULL;
    newSymbol->initialized = (value != NULL) ? 1 : 0;
    newSymbol->next = currentTable->table[index];
    currentTable->table[index] = newSymbol;
}



void updateSymbolValueAndBase(char* name, char* value, char* base) {
    if (!symbolTableStack) return;
    HashTable* currentTable = symbolTableStack->hashTable;
    int index = hash(name);
    Symbol* sym = currentTable->table[index];
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            if (sym->value) free(sym->value);
            if (sym->base) free(sym->base);
            sym->value = strdup(value);
            sym->base = strdup(base);
            sym->initialized = 1;
            return;
        }
        sym = sym->next;
    }
}


Symbol* lookupSymbol(char* name) {
    if (!symbolTableStack) return NULL;
    
    HashTable* currentTable = symbolTableStack->hashTable;
    int index = hash(name);
    
    Symbol* sym = currentTable->table[index];
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    
    return NULL;
}


void printSymbolTable() {
    if (symbolTableStack == NULL || symbolTableStack->hashTable == NULL) {
        printf("\nSymbol table is empty!\n");
        return;
    }

    printf("\n====================== Symbol Table ======================\n");
    printf("| %-15s | %-10s | %-10s | %-10s |\n", "Name", "Type", "Value", "Base");
    printf("----------------------------------------------------------\n");

    HashTable* globalTable = symbolTableStack->hashTable;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol* currentSymbol = globalTable->table[i];
        while (currentSymbol != NULL) {
            printf("| %-15s | %-10s | %-10s | %-10s |\n", 
                   currentSymbol->name, 
                   currentSymbol->type,
                   currentSymbol->value ? currentSymbol->value : "NULL",
                   currentSymbol->base ? currentSymbol->base : "NULL");
            currentSymbol = currentSymbol->next;
        }
    }

    printf("==========================================================\n");
}


%}

%union {
    int ival;
    char* str;
    ASTNode* ast;
}

%token <str> ID STRING_LETTER BINARY OCTAL DECIMAL ARY COMMA CHARACTER
%token INT BEGIN_VARDECL END_VARDECL CHAR SC BGN END OB CB AT
%token IF ASSIGNMENT ELSE PLUS MINUS MUL DIV MOD EQUAL GREATER LESSER GREATER_EQUAL LESSER_EQUAL NOT_EQUAL
%token FOR DO TO INC DEC WHILE BEGIN_PROGRAM END_PROGRAM PRINT 
%token TEN EIGHT TWO QUOTES PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN SCAN

%type <ast> program var_dec decl statements statement assign expr int_const relational arith
%type <ast> str xyz tuv pqr to_part update if_stmt for_stmt while_stmt blck_stmt print_stmt scan_stmt
%type <ast> statements_1 stmt_1 additional additional_1 type data

%right ASSIGNMENT PLUS_ASSIGN MINUS_ASSIGN DIV_ASSIGN MUL_ASSIGN MOD_ASSIGN
%left EQUAL NOT_EQUAL
%left LESSER_EQUAL LESSER GREATER GREATER_EQUAL
%left PLUS MINUS
%left MUL DIV MOD
%nonassoc IF
%nonassoc IFX
%nonassoc ELSE

%%

program : BEGIN_PROGRAM var_dec statements END_PROGRAM {
    root = createProgramNode($2, $3);
    $$ = root;
    //printf("Successfully parsed !!!\n");
}
;

var_dec : BEGIN_VARDECL decl END_VARDECL { $$ = $2; }
;

decl : OB data COMMA type CB SC decl { 
    char* varName = $2->data.str_value;
        char* varType = $4->data.str_value;
        insertSymbol(varName, varType,NULL,NULL);

        $$ = createStatementListNode(
            createVarDeclNode(varName, $4),
            $7
        );
}
| { $$ = NULL; }
;

data : ID { $$ = createIDNode($1); }
| ARY { $$ = createIDNode($1);}
;

type : INT { $$ = createTypeNode("int"); }
| CHAR { $$ = createTypeNode("char"); }
;

statements : statement statements { 
    $$ = createStatementListNode($1, $2); 
}
| { $$ = NULL; }
;

statement : assign { $$ = $1; }
| if_stmt { $$ = $1; }
| for_stmt { $$ = $1; }
| while_stmt { $$ = $1; }
| blck_stmt { $$ = $1; }
| print_stmt { $$ = $1; }
| scan_stmt { $$ = $1; }
;

blck_stmt : BGN statements_1 END { $$ = $2; }
;

statements_1 : stmt_1 statements_1 { $$ = createStatementListNode($1, $2); }
| { $$ = NULL; }
;

stmt_1 : assign { $$ = $1; }
| print_stmt { $$ = $1; }
| scan_stmt { $$ = $1; }
;

if_stmt : IF OB relational CB BGN statements_1 END SC {
    $$ = createIfNode($3, $6, NULL);
}
| IF OB relational CB BGN statements_1 END ELSE BGN statements_1 END SC %prec IFX {
    $$ = createIfNode($3, $6, $10);
}
;

for_stmt : FOR ID ASSIGNMENT expr to_part update expr DO BGN statements_1 END SC {
    $$ = createForNode(
        createAssignNode(createIDNode($2), NODE_ASSIGN, $4),
        $5,
        $6,
        $7,
        $10
    );
}
;

to_part : TO expr { $$ = $2; }
| { $$ = NULL; }
;

update : INC { $$ = createIDNode("inc"); }
| DEC { $$ = createIDNode("dec"); }
;

while_stmt : WHILE OB relational CB DO BGN statements_1 END SC {
    $$ = createWhileNode($3, $7);
}
;

print_stmt : PRINT QUOTES str QUOTES additional CB SC { 
    $$ = createPrintNode($3, $5);
    if (print_count != 0) yyerror("PRINT STATEMENT ERROR\n");
}
| PRINT CB SC { $$ = createPrintNode(NULL, NULL); } 
;

str : STRING_LETTER str { 
    $$ = createStringConcatNode($1, $2); 
}
| AT str { 
    $$ = createFormatNode($2); 
    print_count += 1;
}
| { $$ = createStringNode(""); }
;

additional : COMMA xyz additional { 
    $$ = createStatementListNode2($2, $3); 
    print_count--;
}
| { $$ = NULL; }
;

xyz : ID { $$ = createIDNode($1); }
| int_const { $$ = $1; }
| CHARACTER { $$ = createCharNode($1); }
;

scan_stmt: SCAN QUOTES pqr QUOTES additional_1 CB SC {
    $$ = createScanNode($3, $5);
    if (scan_count != 0) yyerror("Invalid scan stmt");
}
;

pqr : AT tuv { 
    $$ = createFormatNode($2);
    scan_count += 1;
}
|  { $$ = createStringNode(""); }
;

tuv : COMMA AT tuv { 
    $$ = createStringConcatNode($1, createFormatNode($3)); 
    scan_count += 1;
}
| { $$ = NULL; }
;

additional_1 : COMMA ID additional_1 { 
    $$ = createStatementListNode2(createIDNode($2), $3); 
    scan_count -= 1;
}
| { $$ = NULL; }
;

assign : ID ASSIGNMENT expr SC {
    // Check if variable exists
    Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    // Type checking
    if ($3->type == NODE_NUMBER && strcmp(sym->type, "char") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot assign int to char variable '%s'", $1);
        yyerror(buf);
    }
    
    $$ = createAssignNode(createIDNode($1), NODE_ASSIGN, $3);
    
    
    char value_str[64];
    char base_str[10] = "decimal"; 
    
    if ($3->type == NODE_NUMBER) {
        int val = $3->data.value;
        int base = $3->base;
        
        
        if (base == 10) {
            snprintf(value_str, sizeof(value_str), "%d", val);
            strcpy(base_str, "decimal");
        } else if (base == 8) {
            snprintf(value_str, sizeof(value_str), "%o", val);
            strcpy(base_str, "octal");
        } else if (base == 2) {
            
            int v = val, i = 0;
            char bin[33];
            if (v == 0) {
                strcpy(bin, "0");
            } else {
                while (v > 0) {
                    bin[i++] = (v % 2) + '0';
                    v /= 2;
                }
                bin[i] = '\0';
                
                for (int j = 0; j < i / 2; j++) {
                    char tmp = bin[j];
                    bin[j] = bin[i - j - 1];
                    bin[i - j - 1] = tmp;
                }
            }
            snprintf(value_str, sizeof(value_str), "%s", bin);
            strcpy(base_str, "binary");
        } else {
            snprintf(value_str, sizeof(value_str), "%d", val);
            strcpy(base_str, "decimal");
        }
        strcpy(base_str, "NULL");
        strcpy(value_str, "NULL");
        updateSymbolValueAndBase($1, value_str, base_str);
    }
}
| ID PLUS_ASSIGN expr SC {
    
    
    Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (strcmp(sym->type, "char") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot use += on char variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (!sym->initialized) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Variable '%s' used before initialization", $1);
        yyerror(buf);
    }
 $$ = createAssignNode(createIDNode($1), NODE_ADD_ASSIGN, $3);
    if (sym && sym->value && $3->type == NODE_NUMBER) {
        int current = 0;
        int val = $3->data.value;
        int new_base = 10;
        char base_str[10] = "decimal";
        
        
        if (sym->base) {
            if (strcmp(sym->base, "decimal") == 0) {
                new_base = 10;
            } else if (strcmp(sym->base, "octal") == 0) {
                new_base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                new_base = 2;
            }
        }
        
        
        if ($3->base > new_base) {
            new_base = $3->base;
        }
        
        
        if (sym->value) {
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
        }
        
        
        int result = current + val;
        char value_str[64];
        
        
        if (new_base == 10) {
            snprintf(value_str, sizeof(value_str), "%d", result);
            strcpy(base_str, "decimal");
        } else if (new_base == 8) {
            snprintf(value_str, sizeof(value_str), "%o", result);
            strcpy(base_str, "octal");
        } else if (new_base == 2) {
            
            int v = result, i = 0;
            char bin[33];
            if (v == 0) {
                strcpy(bin, "0");
            } else {
                while (v > 0) {
                    bin[i++] = (v % 2) + '0';
                    v /= 2;
                }
                bin[i] = '\0';
                
                for (int j = 0; j < i / 2; j++) {
                    char tmp = bin[j];
                    bin[j] = bin[i - j - 1];
                    bin[i - j - 1] = tmp;
                }
            }
            snprintf(value_str, sizeof(value_str), "%s", bin);
            strcpy(base_str, "binary");
        }
        strcpy(base_str, "NULL");
        strcpy(value_str, "NULL");
        updateSymbolValueAndBase($1, value_str, base_str);
    }
}
| ID MINUS_ASSIGN expr SC {
  Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (strcmp(sym->type, "char") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot use -= on char variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (!sym->initialized) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Variable '%s' used before initialization", $1);
        yyerror(buf);
    }
    $$ = createAssignNode(createIDNode($1), NODE_SUB_ASSIGN, $3);
  
    if (sym && sym->value && $3->type == NODE_NUMBER) {
        int current = 0;
        int val = $3->data.value;
        int new_base = 10; 
        char base_str[10] = "decimal";
        
        
        if (sym->base) {
            if (strcmp(sym->base, "decimal") == 0) {
                new_base = 10;
            } else if (strcmp(sym->base, "octal") == 0) {
                new_base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                new_base = 2;
            }
        }
        
        
        if ($3->base > new_base) {
            new_base = $3->base;
        }
        
        
        if (sym->value) {
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
        }
        
        
        int result = current - val;
        char value_str[64];
        
        
        if (new_base == 10) {
            snprintf(value_str, sizeof(value_str), "%d", result);
            strcpy(base_str, "decimal");
        } else if (new_base == 8) {
            snprintf(value_str, sizeof(value_str), "%o", result);
            strcpy(base_str, "octal");
        } else if (new_base == 2) {
            
            int v = result, i = 0;
            char bin[33];
            if (v == 0) {
                strcpy(bin, "0");
            } else {
                while (v > 0) {
                    bin[i++] = (v % 2) + '0';
                    v /= 2;
                }
                bin[i] = '\0';
                
                for (int j = 0; j < i / 2; j++) {
                    char tmp = bin[j];
                    bin[j] = bin[i - j - 1];
                    bin[i - j - 1] = tmp;
                }
            }
            snprintf(value_str, sizeof(value_str), "%s", bin);
            strcpy(base_str, "binary");
        }
        strcpy(base_str, "NULL");
        strcpy(value_str, "NULL");
        updateSymbolValueAndBase($1, value_str, base_str);
    }
}
| ID MUL_ASSIGN expr SC {
  Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (strcmp(sym->type, "char") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot use *= on char variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (!sym->initialized) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Variable '%s' used before initialization", $1);
        yyerror(buf);
    }
    $$ = createAssignNode(createIDNode($1), NODE_MUL_ASSIGN, $3);
    if (sym && sym->value && $3->type == NODE_NUMBER) {
        int current = 0;
        int val = $3->data.value;
        int new_base = 10;
        char base_str[10] = "decimal";
        
        
        if (sym->base) {
            if (strcmp(sym->base, "decimal") == 0) {
                new_base = 10;
            } else if (strcmp(sym->base, "octal") == 0) {
                new_base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                new_base = 2;
            }
        }
        
        
        if ($3->base > new_base) {
            new_base = $3->base;
        }
        
        
        if (sym->value) {
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
        }
        
        
        int result = current * val;
        char value_str[64];
        
        
        if (new_base == 10) {
            snprintf(value_str, sizeof(value_str), "%d", result);
            strcpy(base_str, "decimal");
        } else if (new_base == 8) {
            snprintf(value_str, sizeof(value_str), "%o", result);
            strcpy(base_str, "octal");
        } else if (new_base == 2) {
            
            int v = result, i = 0;
            char bin[33];
            if (v == 0) {
                strcpy(bin, "0");
            } else {
                while (v > 0) {
                    bin[i++] = (v % 2) + '0';
                    v /= 2;
                }
                bin[i] = '\0';
                
                for (int j = 0; j < i / 2; j++) {
                    char tmp = bin[j];
                    bin[j] = bin[i - j - 1];
                    bin[i - j - 1] = tmp;
                }
            }
            snprintf(value_str, sizeof(value_str), "%s", bin);
            strcpy(base_str, "binary");
        }
        strcpy(base_str, "NULL");
        strcpy(value_str, "NULL");
        updateSymbolValueAndBase($1, value_str, base_str);
    }
}
| ID DIV_ASSIGN expr SC {
  Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (strcmp(sym->type, "char") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot use /= on char variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (!sym->initialized) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Variable '%s' used before initialization", $1);
        yyerror(buf);
    }
    $$ = createAssignNode(createIDNode($1), NODE_DIV_ASSIGN, $3);
    
    if (sym && sym->value && $3->type == NODE_NUMBER) {
        int current = 0;
        int val = $3->data.value;
        
        if (val == 0) { 
            char buf[128];
            snprintf(buf, sizeof(buf), "Division by zero in variable '%s'", $1);
            yyerror(buf);
        } else {
            int new_base = 10;
            char base_str[10] = "decimal";
            
            
            if (sym->base) {
                if (strcmp(sym->base, "decimal") == 0) {
                    new_base = 10;
                } else if (strcmp(sym->base, "octal") == 0) {
                    new_base = 8;
                } else if (strcmp(sym->base, "binary") == 0) {
                    new_base = 2;
                }
            }
            
            
            if ($3->base > new_base) {
                new_base = $3->base;
            }
            
            
            if (sym->value) {
                if (strcmp(sym->base, "decimal") == 0) {
                    current = atoi(sym->value);
                } else if (strcmp(sym->base, "octal") == 0) {
                    current = strtol(sym->value, NULL, 8);
                } else if (strcmp(sym->base, "binary") == 0) {
                    current = strtol(sym->value, NULL, 2);
                } else {
                    current = atoi(sym->value);
                }
            }
            
            
            int result = current / val;
            char value_str[64];
            
            
            if (new_base == 10) {
                snprintf(value_str, sizeof(value_str), "%d", result);
                strcpy(base_str, "decimal");
            } else if (new_base == 8) {
                snprintf(value_str, sizeof(value_str), "%o", result);
                strcpy(base_str, "octal");
            } else if (new_base == 2) {
                
                int v = result, i = 0;
                char bin[33];
                if (v == 0) {
                    strcpy(bin, "0");
                } else {
                    while (v > 0) {
                        bin[i++] = (v % 2) + '0';
                        v /= 2;
                    }
                    bin[i] = '\0';
                    
                    for (int j = 0; j < i / 2; j++) {
                        char tmp = bin[j];
                        bin[j] = bin[i - j - 1];
                        bin[i - j - 1] = tmp;
                    }
                }
                snprintf(value_str, sizeof(value_str), "%s", bin);
                strcpy(base_str, "binary");
            }
            strcpy(base_str, "NULL");
        strcpy(value_str, "NULL");
            updateSymbolValueAndBase($1, value_str, base_str);
        }
    }
}
| ID MOD_ASSIGN expr SC {
  Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (strcmp(sym->type, "char") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot use mod= on char variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (!sym->initialized) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Variable '%s' used before initialization", $1);
        yyerror(buf);
    }
    $$ = createAssignNode(createIDNode($1), NODE_MOD_ASSIGN, $3);
    
    if (sym && sym->value && $3->type == NODE_NUMBER) {
        int current = 0;
        int val = $3->data.value;
        
        if (val == 0) { 
            char buf[128];
            snprintf(buf, sizeof(buf), "Modulo by zero in variable '%s'", $1);
            yyerror(buf);
        } else {
            int new_base = 10;
            char base_str[10] = "decimal";
            
            
            if (sym->base) {
                if (strcmp(sym->base, "decimal") == 0) {
                    new_base = 10;
                } else if (strcmp(sym->base, "octal") == 0) {
                    new_base = 8;
                } else if (strcmp(sym->base, "binary") == 0) {
                    new_base = 2;
                }
            }
            
            
            if ($3->base > new_base) {
                new_base = $3->base;
            }
            
            
            if (sym->value) {
                if (strcmp(sym->base, "decimal") == 0) {
                    current = atoi(sym->value);
                } else if (strcmp(sym->base, "octal") == 0) {
                    current = strtol(sym->value, NULL, 8);
                } else if (strcmp(sym->base, "binary") == 0) {
                    current = strtol(sym->value, NULL, 2);
                } else {
                    current = atoi(sym->value);
                }
            }
            
            
            int result = current % val;
            char value_str[64];
            
            
            if (new_base == 10) {
                snprintf(value_str, sizeof(value_str), "%d", result);
                strcpy(base_str, "decimal");
            } else if (new_base == 8) {
                snprintf(value_str, sizeof(value_str), "%o", result);
                strcpy(base_str, "octal");
            } else if (new_base == 2) {
                
                int v = result, i = 0;
                char bin[33];
                if (v == 0) {
                    strcpy(bin, "0");
                } else {
                    while (v > 0) {
                        bin[i++] = (v % 2) + '0';
                        v /= 2;
                    }
                    bin[i] = '\0';
                    
                    for (int j = 0; j < i / 2; j++) {
                        char tmp = bin[j];
                        bin[j] = bin[i - j - 1];
                        bin[i - j - 1] = tmp;
                    }
                }
                snprintf(value_str, sizeof(value_str), "%s", bin);
                strcpy(base_str, "binary");
            }
            strcpy(base_str, "NULL");
        strcpy(value_str, "NULL");
            updateSymbolValueAndBase($1, value_str, base_str);
        }
    }
}
| ID ASSIGNMENT CHARACTER SC {
    
    Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    }
    
    
    if (strcmp(sym->type, "int") == 0) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Type mismatch: Cannot assign character to int variable '%s'", $1);
        yyerror(buf);
    }
    
    $$ = createAssignNode(createIDNode($1), NODE_ASSIGN, createCharNode($3));
    
    
    char value_str[64];
    if (strlen($3) >= 3) {
        if ($3[0] == '\'' && $3[strlen($3)-1] == '\'') {
            
            if (strlen($3) == 4 && $3[1] == '\\') {
                switch($3[2]) {
                    case 'n': snprintf(value_str, sizeof(value_str), "\\n"); break;
                    case 't': snprintf(value_str, sizeof(value_str), "\\t"); break;
                    default: snprintf(value_str, sizeof(value_str), "%c", $3[2]);
                }
            } else {
                snprintf(value_str, sizeof(value_str), "%c", $3[1]);
            }
          
            strcpy(value_str, "NULL");
            updateSymbolValueAndBase($1, value_str, "NULL");
        }
    }
}
;


expr : arith { $$ = $1; }
;

arith : arith PLUS arith { $$ = createOperatorNode(NODE_ADD, $1, $3); }
| arith MINUS arith { $$ = createOperatorNode(NODE_SUB, $1, $3); }
| arith MUL arith { $$ = createOperatorNode(NODE_MUL, $1, $3); }
| arith DIV arith { $$ = createOperatorNode(NODE_DIV, $1, $3); }
| arith MOD arith { $$ = createOperatorNode(NODE_MOD, $1, $3); }
| ID { Symbol* sym = lookupSymbol($1);
    if (!sym) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Undeclared variable '%s'", $1);
        yyerror(buf);
    } else if (!sym->initialized) {
        char buf[128];
        snprintf(buf, sizeof(buf), "Variable '%s' used before initialization", $1);
        yyerror(buf);
    }
  $$ = createIDNode($1); }
| int_const { $$ = $1; }
;

int_const : OB DECIMAL COMMA TEN CB { $$ = createNumberNode(atoi($2)); $$->base = 10; }
| OB OCTAL COMMA EIGHT CB {  $$ = createNumberNode(strtol($2, NULL, 8)); $$->base = 8; }
| OB BINARY COMMA TWO CB { $$ = createNumberNode(strtol($2, NULL, 2)); $$->base = 2;}
| OB BINARY COMMA EIGHT CB { $$ = createNumberNode(strtol($2, NULL, 8)); $$->base = 8;}
| OB BINARY COMMA TEN CB { $$ = createNumberNode(strtol($2, NULL, 10));$$->base = 10; }
| OB OCTAL COMMA TEN CB { $$ = createNumberNode(strtol($2, NULL, 10)); $$->base = 10;}
;

relational : relational EQUAL relational { $$ = createOperatorNode(NODE_EQ, $1, $3); }
| relational NOT_EQUAL relational { $$ = createOperatorNode(NODE_NEQ, $1, $3); }
| relational GREATER relational { $$ = createOperatorNode(NODE_GT, $1, $3); }
| relational LESSER relational { $$ = createOperatorNode(NODE_LT, $1, $3); }
| relational GREATER_EQUAL relational { $$ = createOperatorNode(NODE_GTE, $1, $3); }
| relational LESSER_EQUAL relational { $$ = createOperatorNode(NODE_LTE, $1, $3); }
| arith { $$ = $1; }
;

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Maaf karo nhi khul rhi file tumhari\n");
        return 1;
    }

    yyparse();
    /* printSymbolTable(); */
    if(root) {
    /* printf("\nGeneralized List AST:\n");
    printAST(root);
    printf("\n=== Program Output ===\n"); */
    
    interpretAST(root);
    /* printf("=== End of Output ===\n"); */
    freeAST(root);
}
  printSymbolTable();

    fclose(yyin);
    return 0;
}

void yyerror(const char* s){
    printf("Error: %s!!!\n", s);
    exit(1);
}
