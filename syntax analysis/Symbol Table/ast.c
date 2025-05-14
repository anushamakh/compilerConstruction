#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int tab_count = 0;
int panda=0;


typedef struct Symbol {
    char* name;
    char* type;
    char* value;
    char* base;
    int initialized;
    struct Symbol* next;
} Symbol;

typedef struct HashTable {
    Symbol* table[101];
} HashTable;

typedef struct SymbolTableStack {
    HashTable* hashTable;
} SymbolTableStack;


extern Symbol* lookupSymbol(char* name);
extern void updateSymbolValueAndBase(char* name, char* value, char* base);
extern SymbolTableStack* symbolTableStack;


int determineHighestBase(ASTNode* left, ASTNode* right) {
    int leftBase = 10, rightBase = 10;
    
    
    if (left->type == NODE_NUMBER) {
        leftBase = left->base;
    } else if (left->type == NODE_ID) {
        Symbol* sym = lookupSymbol(left->data.str_value);
        if (sym) {
            if (strcmp(sym->base, "decimal") == 0) leftBase = 10;
            else if (strcmp(sym->base, "octal") == 0) leftBase = 8;
            else if (strcmp(sym->base, "binary") == 0) leftBase = 2;
        }
    }
    
    
    if (right->type == NODE_NUMBER) {
        rightBase = right->base;
    } else if (right->type == NODE_ID) {
        Symbol* sym = lookupSymbol(right->data.str_value);
        if (sym) {
            if (strcmp(sym->base, "decimal") == 0) rightBase = 10;
            else if (strcmp(sym->base, "octal") == 0) rightBase = 8;
            else if (strcmp(sym->base, "binary") == 0) rightBase = 2;
        }
    }
    
    
    return (leftBase > rightBase) ? leftBase : rightBase;
}


static const char* get_print_arg_value(ASTNode* node) {
    if (!node) return "";
    
    switch (node->type) {
        case NODE_ID: {
            Symbol* sym = lookupSymbol(node->data.str_value);
            if (!sym) {
                fprintf(stderr, "Runtime Error: Variable '%s' not declared\n", node->data.str_value);
                exit(1);
            }
            
            if (!sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' used before initialization\n", node->data.str_value);
                exit(1);
            }
            
            return sym->value ? sym->value : "";
        }
        
        case NODE_NUMBER: {
            static char buf[64];
            if (node->base == 10) {
                snprintf(buf, sizeof(buf), "%d", node->data.value);
            } else if (node->base == 8) {
                snprintf(buf, sizeof(buf), "%o", node->data.value);
            } else if (node->base == 2) {
                int v = node->data.value, i = 0;
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
                snprintf(buf, sizeof(buf), "%s", bin);
            } else {
                snprintf(buf, sizeof(buf), "%d", node->data.value);
            }
            return buf;
        }
        
        case NODE_CHAR: {
            return node->data.str_value;
        }
        
        default:
            return "";
    }
}


static void print_format(ASTNode* format_str, ASTNode* args, int* arg_idx) {
    if (!format_str) return;
    
    if (format_str->type == NODE_STRING_CONCAT) {
        printf("%s", format_str->data.str_value);
        print_format(format_str->data.children.right, args, arg_idx);
    } else if (format_str->type == NODE_FORMAT) {
        
        ASTNode* arg_node = args;
        int idx = 0;
        while (arg_node && idx < *arg_idx) {
            arg_node = arg_node->data.children.right;
            idx++;
        }
        
        if (arg_node && arg_node->data.children.left) {
            printf("%s", get_print_arg_value(arg_node->data.children.left));
        } else {
            printf("@");
        }
        
        (*arg_idx)++;
        
        
        if (format_str->data.children.left) {
            print_format(format_str->data.children.left, args, arg_idx);
        }
    } else if (format_str->type == NODE_STRING) {
        printf("%s", format_str->data.str_value);
    }
}


int evaluateExpr(ASTNode* node) {
    if (!node) return 0;
    
    switch (node->type) {
        case NODE_NUMBER:
            return node->data.value;
            
        case NODE_ID: {
            Symbol* sym = lookupSymbol(node->data.str_value);
            if (!sym) {
                fprintf(stderr, "Runtime Error: Undefined variable '%s'\n", node->data.str_value);
                exit(1);
            }
            
            if (!sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' used before initialization\n", node->data.str_value);
                exit(1);
            }
            
            
            if (strcmp(sym->base, "decimal") == 0) {
                return atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                return strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                return strtol(sym->value, NULL, 2);
            } else if (strcmp(sym->base, "char") == 0) {
                
                return (int)sym->value[0];
            } else {
                return atoi(sym->value);
            }
        }

        case NODE_CHAR: {
            if (node->data.str_value[0] == '\'' && 
                strlen(node->data.str_value) >= 3 && 
                node->data.str_value[strlen(node->data.str_value)-1] == '\'') {
                
                if (node->data.str_value[1] == '\\' && strlen(node->data.str_value) >= 4) {
                    switch(node->data.str_value[2]) {
                        case 'n': return '\n';
                        case 't': return '\t';
                        default: return node->data.str_value[2];
                    }
                } else {
                    return node->data.str_value[1];
                }
            }
            return node->data.str_value[0];
        }
        
        case NODE_ADD: {
            int result = evaluateExpr(node->data.children.left) + 
                         evaluateExpr(node->data.children.right);
            
            return result;
        }
        
        case NODE_SUB: {
            int result = evaluateExpr(node->data.children.left) - 
                         evaluateExpr(node->data.children.right);
            return result;
        }
        
        case NODE_MUL: {
            int result = evaluateExpr(node->data.children.left) * 
                         evaluateExpr(node->data.children.right);
            return result;
        }
        
        case NODE_DIV: {
            int divisor = evaluateExpr(node->data.children.right);
            if (divisor == 0) {
                fprintf(stderr, "Runtime Error: Division by zero\n");
                exit(1);
            }
            int result = evaluateExpr(node->data.children.left) / divisor;
            return result;
        }
        
        case NODE_MOD: {
            int divisor = evaluateExpr(node->data.children.right);
            if (divisor == 0) {
                fprintf(stderr, "Runtime Error: Modulo by zero\n");
                exit(1);
            }
            int result = evaluateExpr(node->data.children.left) % divisor;
            return result;
        }
        
        case NODE_EQ:
            return evaluateExpr(node->data.children.left) == 
                   evaluateExpr(node->data.children.right);
                   
        case NODE_NEQ:
            return evaluateExpr(node->data.children.left) != 
                   evaluateExpr(node->data.children.right);
                   
        case NODE_GT:
            return evaluateExpr(node->data.children.left) > 
                   evaluateExpr(node->data.children.right);
                   
        case NODE_LT:
            return evaluateExpr(node->data.children.left) < 
                   evaluateExpr(node->data.children.right);
                   
        case NODE_GTE:
            return evaluateExpr(node->data.children.left) >= 
                   evaluateExpr(node->data.children.right);
                   
        case NODE_LTE:
            return evaluateExpr(node->data.children.left) <= 
                   evaluateExpr(node->data.children.right);
                   
        default:
            fprintf(stderr, "Runtime Error: Unknown expression node type: %d\n", node->type);
            return 0;
    }
}


void updateVariableValue(ASTNode* target, int value, int base) {
    if (target->type != NODE_ID) {
        fprintf(stderr, "Runtime Error: Assignment target is not an identifier\n");
        return;
    }
    
    char* varName = target->data.str_value;
    Symbol* sym = lookupSymbol(varName);
    
    if (!sym) {
        fprintf(stderr, "Runtime Error: Undefined variable '%s'\n", varName);
        return;
    }
    
    char value_str[64];
    char base_str[10] = "decimal";
    
    
    if (base == 10) {
        snprintf(value_str, sizeof(value_str), "%d", value);
        strcpy(base_str, "decimal");
    } else if (base == 8) {
        snprintf(value_str, sizeof(value_str), "%o", value);
        strcpy(base_str, "octal");
    } else if (base == 2) {
        
        int v = value, i = 0;
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
        snprintf(value_str, sizeof(value_str), "%d", value);
        strcpy(base_str, "decimal");
    }
    
    updateSymbolValueAndBase(varName, value_str, base_str);
}


void interpretAST(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            
            interpretAST(node->data.children.left);
            interpretAST(node->data.children.right);
            break;
            
        case NODE_STATEMENT_LIST:
        case NODE_STATEMENT_LIST_2:
            
            interpretAST(node->data.children.left);
            interpretAST(node->data.children.right);
            break;
            
        case NODE_VAR_DECL:
            
            break;
            
        case NODE_ASSIGN: {
            if (node->data.assign.expr->type == NODE_CHAR) {
                char* charValue = node->data.assign.expr->data.str_value;
                
                char* varName = node->data.assign.target->data.str_value;
                
                updateSymbolValueAndBase(varName, charValue, "NULL");
            } else {
                int value = evaluateExpr(node->data.assign.expr);
                int base = 10;
                
                if (node->data.assign.expr->type == NODE_NUMBER) {
                    base = node->data.assign.expr->base;
                } else if (node->data.assign.expr->type == NODE_ADD ||
                            node->data.assign.expr->type == NODE_SUB ||
                            node->data.assign.expr->type == NODE_MUL ||
                            node->data.assign.expr->type == NODE_DIV ||
                            node->data.assign.expr->type == NODE_MOD) {
                    base = determineHighestBase(node->data.assign.expr->data.children.left,
                                                node->data.assign.expr->data.children.right);
                }
                
                updateVariableValue(node->data.assign.target, value, base);
            }
            break;
        }
            
        case NODE_ADD_ASSIGN: {
            
            Symbol* sym = lookupSymbol(node->data.assign.target->data.str_value);
            if (!sym || !sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' not initialized for +=\n", 
                        node->data.assign.target->data.str_value);
                break;
            }
            
            int current = 0;
            
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
            
            int value = evaluateExpr(node->data.assign.expr);
            int result = current + value;
            
            
            int base = 10;
            if (strcmp(sym->base, "octal") == 0) {
                base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                base = 2;
            }
            
            
            if (node->data.assign.expr->type == NODE_NUMBER && 
                node->data.assign.expr->base > base) {
                base = node->data.assign.expr->base;
            } else if (node->data.assign.expr->type == NODE_ADD || 
                      node->data.assign.expr->type == NODE_SUB || 
                      node->data.assign.expr->type == NODE_MUL || 
                      node->data.assign.expr->type == NODE_DIV || 
                      node->data.assign.expr->type == NODE_MOD) {
                
                int exprBase = determineHighestBase(node->data.assign.expr->data.children.left, 
                                                  node->data.assign.expr->data.children.right);
                if (exprBase > base) {
                    base = exprBase;
                }
            }
            
            updateVariableValue(node->data.assign.target, result, base);
            break;
        }
            
        case NODE_SUB_ASSIGN: {
            
            Symbol* sym = lookupSymbol(node->data.assign.target->data.str_value);
            if (!sym || !sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' not initialized for -=\n", 
                        node->data.assign.target->data.str_value);
                break;
            }
            
            int current = 0;
            
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
            
            int value = evaluateExpr(node->data.assign.expr);
            int result = current - value;
            
            
            int base = 10;
            if (strcmp(sym->base, "octal") == 0) {
                base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                base = 2;
            }
            
            
            if (node->data.assign.expr->type == NODE_NUMBER && 
                node->data.assign.expr->base > base) {
                base = node->data.assign.expr->base;
            } else if (node->data.assign.expr->type == NODE_ADD || 
                      node->data.assign.expr->type == NODE_SUB || 
                      node->data.assign.expr->type == NODE_MUL || 
                      node->data.assign.expr->type == NODE_DIV || 
                      node->data.assign.expr->type == NODE_MOD) {
                
                int exprBase = determineHighestBase(node->data.assign.expr->data.children.left, 
                                                  node->data.assign.expr->data.children.right);
                if (exprBase > base) {
                    base = exprBase;
                }
            }
            
            updateVariableValue(node->data.assign.target, result, base);
            break;
        }
            
        case NODE_MUL_ASSIGN: {
            
            Symbol* sym = lookupSymbol(node->data.assign.target->data.str_value);
            if (!sym || !sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' not initialized for *=\n", 
                        node->data.assign.target->data.str_value);
                break;
            }
            
            int current = 0;
            
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
            
            int value = evaluateExpr(node->data.assign.expr);
            int result = current * value;
            
            
            int base = 10;
            if (strcmp(sym->base, "octal") == 0) {
                base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                base = 2;
            }
            
            
            if (node->data.assign.expr->type == NODE_NUMBER && 
                node->data.assign.expr->base > base) {
                base = node->data.assign.expr->base;
            } else if (node->data.assign.expr->type == NODE_ADD || 
                      node->data.assign.expr->type == NODE_SUB || 
                      node->data.assign.expr->type == NODE_MUL || 
                      node->data.assign.expr->type == NODE_DIV || 
                      node->data.assign.expr->type == NODE_MOD) {
                
                int exprBase = determineHighestBase(node->data.assign.expr->data.children.left, 
                                                  node->data.assign.expr->data.children.right);
                if (exprBase > base) {
                    base = exprBase;
                }
            }
            
            updateVariableValue(node->data.assign.target, result, base);
            break;
        }
            
        case NODE_DIV_ASSIGN: {
            
            Symbol* sym = lookupSymbol(node->data.assign.target->data.str_value);
            if (!sym || !sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' not initialized for /=\n", 
                        node->data.assign.target->data.str_value);
                break;
            }
            
            int current = 0;
            
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
            
            int value = evaluateExpr(node->data.assign.expr);
            if (value == 0) {
                fprintf(stderr, "Runtime Error: Division by zero\n");
                break;
            }
            
            int result = current / value;
            
            
            int base = 10;
            if (strcmp(sym->base, "octal") == 0) {
                base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                base = 2;
            }
            
            
            if (node->data.assign.expr->type == NODE_NUMBER && 
                node->data.assign.expr->base > base) {
                base = node->data.assign.expr->base;
            } else if (node->data.assign.expr->type == NODE_ADD || 
                      node->data.assign.expr->type == NODE_SUB || 
                      node->data.assign.expr->type == NODE_MUL || 
                      node->data.assign.expr->type == NODE_DIV || 
                      node->data.assign.expr->type == NODE_MOD) {
                
                int exprBase = determineHighestBase(node->data.assign.expr->data.children.left, 
                                                  node->data.assign.expr->data.children.right);
                if (exprBase > base) {
                    base = exprBase;
                }
            }
            
            updateVariableValue(node->data.assign.target, result, base);
            break;
        }
            
        case NODE_MOD_ASSIGN: {
            
            Symbol* sym = lookupSymbol(node->data.assign.target->data.str_value);
            if (!sym || !sym->initialized) {
                fprintf(stderr, "Runtime Error: Variable '%s' not initialized for %%=\n", 
                        node->data.assign.target->data.str_value);
                break;
            }
            
            int current = 0;
            
            if (strcmp(sym->base, "decimal") == 0) {
                current = atoi(sym->value);
            } else if (strcmp(sym->base, "octal") == 0) {
                current = strtol(sym->value, NULL, 8);
            } else if (strcmp(sym->base, "binary") == 0) {
                current = strtol(sym->value, NULL, 2);
            } else {
                current = atoi(sym->value);
            }
            
            int value = evaluateExpr(node->data.assign.expr);
            if (value == 0) {
                fprintf(stderr, "Runtime Error: Modulo by zero\n");
                break;
            }
            
            int result = current % value;
            
            
            int base = 10;
            if (strcmp(sym->base, "octal") == 0) {
                base = 8;
            } else if (strcmp(sym->base, "binary") == 0) {
                base = 2;
            }
            
            
            if (node->data.assign.expr->type == NODE_NUMBER && 
                node->data.assign.expr->base > base) {
                base = node->data.assign.expr->base;
            } else if (node->data.assign.expr->type == NODE_ADD || 
                      node->data.assign.expr->type == NODE_SUB || 
                      node->data.assign.expr->type == NODE_MUL || 
                      node->data.assign.expr->type == NODE_DIV || 
                      node->data.assign.expr->type == NODE_MOD) {
                
                int exprBase = determineHighestBase(node->data.assign.expr->data.children.left, 
                                                  node->data.assign.expr->data.children.right);
                if (exprBase > base) {
                    base = exprBase;
                }
            }
            
            updateVariableValue(node->data.assign.target, result, base);
            break;
        }
            
        case NODE_IF: {
            
            int condition = evaluateExpr(node->data.control.cond);
            
            
            if (condition) {
                interpretAST(node->data.control.then_block);
            } else if (node->data.control.else_block) {
                interpretAST(node->data.control.else_block);
            }
            break;
        }
            
        case NODE_WHILE: {
            
            while (evaluateExpr(node->data.control.cond)) {
                interpretAST(node->data.control.then_block);
            }
            break;
        }
            
        case NODE_FOR: {
            interpretAST(node->data.for_control.init);
            
            char* varName = node->data.for_control.init->data.assign.target->data.str_value;
            Symbol* sym = lookupSymbol(varName);
            if (!sym) {
                fprintf(stderr, "Runtime Error: Loop variable '%s' not declared\n", varName);
                break;
            }
            sym->initialized = 1;
        

            int isIncrement = (strcmp(node->data.for_control.upd->data.str_value, "inc") == 0);
            
            int amount = evaluateExpr(node->data.for_control.amount);
            int base_1 = node->data.for_control.amount->base;
            // printf("%d", base_1);

            int limitValue = evaluateExpr(node->data.for_control.cond);
            
            while (1) {
                int currentValue = 0;
                if (strcmp(sym->base, "decimal") == 0) {
                    currentValue = atoi(sym->value);
                } else if (strcmp(sym->base, "octal") == 0) {
                    currentValue = strtol(sym->value, NULL, 8);
                } else if (strcmp(sym->base, "binary") == 0) {
                    currentValue = strtol(sym->value, NULL, 2);
                } else {
                    currentValue = atoi(sym->value);
                }
                
                if ((isIncrement && currentValue > limitValue) || 
                    (!isIncrement && currentValue < limitValue)) {
                    break;
                }
        
                interpretAST(node->data.for_control.stmt);
                if (isIncrement) {
                    currentValue += amount;
                } else {
                    currentValue -= amount;
                }
                
                int base = 10;
                if (strcmp(sym->base, "octal") == 0) {
                    if(base_1 <= 8) {
                        base = 8;
                    }
                    else{
                        base = base_1;
                    }
                } else if (strcmp(sym->base, "binary") == 0) {
                    if(base_1 <= 2) {
                        base = 2;
                    }
                    else{
                        base = base_1;
                    }
                }
                
                updateVariableValue(node->data.for_control.init->data.assign.target, 
                                   currentValue, base);

            }
            break;
        }
            
        case NODE_PRINT: {
            break;
        }
            
        case NODE_SCAN: {
            break;
        }
            
        default:
            
            break;
    }
}

ASTNode *createNumberNode(int value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocate nhi ho rhi\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_NUMBER;
    node->data.value = value;
    node->base = 10;
    return node;
}

ASTNode *createOperatorNode(NodeType type, ASTNode *left, ASTNode *right)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocate nhi ho rhi\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->data.children.right = right;
    node->data.children.left = left;
    return node;
}

ASTNode *createVarDeclNode(const char *name, ASTNode *type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_VAR_DECL;
    node->data.var_decl.var_name = strdup(name);
    node->data.var_decl.var_type = type;
    return node;
}

ASTNode *createIDNode(const char *name)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data.str_value = strdup(name);
    node->type = NODE_ID;
    return node;
}

ASTNode *createTypeNode(const char *type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_TYPE;
    node->data.str_value = strdup(type);
    return node;
}

ASTNode *createStringNode(const char *str)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_STRING;
    node->data.str_value = strdup(str);
    return node;
}

ASTNode *createStringConcatNode(const char *str, ASTNode *next)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_STRING_CONCAT;
    node->data.str_value = strdup(str);
    node->data.children.right = next;
    return node;
}

ASTNode *createCharNode(char *c)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_CHAR;
    node->data.str_value = c;
    return node;
}

ASTNode *createAssignNode(ASTNode *target, NodeType type, ASTNode *expr)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->data.assign.target = target;
    node->data.assign.expr = expr;
    return node;
}

ASTNode *createIfNode(ASTNode *cond, ASTNode *then_block, ASTNode *else_block)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_IF;
    node->data.control.cond = cond;
    node->data.control.then_block = then_block;
    node->data.control.else_block = else_block;
    return node;
}

ASTNode *createForNode(ASTNode *init, ASTNode *cond, ASTNode *update, ASTNode *amount, ASTNode *body)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_FOR;
    node->data.for_control.init = init;
    node->data.for_control.cond = cond;
    node->data.for_control.upd = update;
    node->data.for_control.amount = amount;
    node->data.for_control.stmt = body;
    return node;
}

ASTNode *createWhileNode(ASTNode *cond, ASTNode *body)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_WHILE;
    node->data.control.cond = cond;
    node->data.control.then_block = body;
    node->data.control.else_block = NULL;
    return node;
}

ASTNode *createPrintNode(ASTNode *format_str, ASTNode *args)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_PRINT;
    node->data.io.format_str = format_str;
    node->data.io.args = args;
    return node;
}

ASTNode *createScanNode(ASTNode *format, ASTNode *vars)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_SCAN;
    node->data.io.format_str = format;
    node->data.io.args = vars;
    return node;
}

ASTNode *createFormatNode(ASTNode *node)
{
    ASTNode *format_node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!format_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    format_node->type = NODE_FORMAT;
    format_node->data.children.left = node;
    return format_node;
}

ASTNode *createProgramNode(ASTNode *declarations, ASTNode *statements)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_PROGRAM;
    node->data.children.left = declarations;
    node->data.children.right = statements;
    return node;
}

ASTNode *createStatementListNode(ASTNode *stmt, ASTNode *next)
{
    if (!stmt)
        return next;
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_STATEMENT_LIST;
    node->data.children.left = stmt;
    node->data.children.right = next;
    return node;
}

ASTNode *createStatementListNode2(ASTNode *stmt, ASTNode *next)
{
    if (!stmt)
        return next;
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = NODE_STATEMENT_LIST_2;
    node->data.children.left = stmt;
    node->data.children.right = next;
    return node;
}

void printAST(ASTNode *node)
{
    if (node == NULL)
        return;
    switch (node->type)
    {
    case NODE_NUMBER:
        if (node->base == 10)
        {
            printf("(%d %d)", node->data.value, node->base);
        }
        else if (node->base == 2)
        {
            char binary[33];
            int val = node->data.value;
            int i = 0;
            while (val > 0)
            {
                binary[i++] = (val % 2) + '0';
                val /= 2;
            }
            binary[i] = '\0';
            for (int j = 0; j < i / 2; j++)
            {
                char temp = binary[j];
                binary[j] = binary[i - j - 1];
                binary[i - j - 1] = temp;
            }
            printf("(%s %d)", binary, node->base);
        }
        else if (node->base == 8)
        {
            printf("(%o %d)", node->data.value, node->base);
        }
        else
        {
            printf("(%d %d)", node->data.value, node->base);
        }
        break;
    case NODE_ID:
        printf("%s", node->data.str_value);
        break;
    case NODE_STRING:
        printf("%s\"", node->data.str_value);
        break;
    case NODE_CHAR:
        printf("%s", node->data.str_value);
        break;
    case NODE_TYPE:
        printf("%s", node->data.str_value);
        break;
    case NODE_VAR_DECL:
        
        printf("(decl %s ", node->data.var_decl.var_name);
        printAST(node->data.var_decl.var_type);
        printf(")");
        break;
    case NODE_ASSIGN:
        
        printf("(= ");
        printAST(node->data.assign.target);
        printf(" ");
        printAST(node->data.assign.expr);
        printf(")");
        break;
    case NODE_ADD_ASSIGN:
        printf("(\n");
        tab_count++;
        printf("(+= ");
        printAST(node->data.assign.target);
        printf(" ");
        printAST(node->data.assign.expr);
        printf(")");
        break;
    case NODE_MUL_ASSIGN:
        printf("(\n");
        tab_count++;
        printf("(*= ");
        printAST(node->data.assign.target);
        printf(" ");
        printAST(node->data.assign.expr);
        printf(")");
        break;
    case NODE_SUB_ASSIGN:
        printf("(\n");
        tab_count++;
        printf("(-= ");
        printAST(node->data.assign.target);
        printf(" ");
        printAST(node->data.assign.expr);
        printf(")");
        break;
    case NODE_DIV_ASSIGN:
        printf("(\n");
        tab_count++;
        printf("(/= ");
        printAST(node->data.assign.target);
        printf(" ");
        printAST(node->data.assign.expr);
        printf(")");
        break;
    case NODE_MOD_ASSIGN:
        printf("(\n");
        tab_count++;
        printf("(%%= ");
        printAST(node->data.assign.target);
        printf(" ");
        printAST(node->data.assign.expr);
        printf(")");
        break;
    case NODE_PROGRAM:
        
        
        printAST(node->data.children.left);
        printf("\n");
        printAST(node->data.children.right);
        for (int tc = tab_count; tc > 0; tc--)
        {
            printf("\n)");
        }
        break;
    case NODE_STATEMENT_LIST:
        
        
        printAST(node->data.children.left);
        if (node->data.children.right)
        {
            printf("\n");
            printAST(node->data.children.right);
        }
        break;
    case NODE_STATEMENT_LIST_2:
        printAST(node->data.children.left);
        if (node->data.children.right)
        {
            printf(" ");
            printAST(node->data.children.right);
        }
        break;
    case NODE_ADD:
        printf("(+ ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_SUB:
        printf("(- ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_MUL:
        printf("(* ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_DIV:
        printf("(/ ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_MOD:
        printf("(%% ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_EQ:
        printf("(= ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_NEQ:
        printf("(<> ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_GT:
        printf("(> ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_LT:
        printf("(< ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_GTE:
        printf("(>= ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_LTE:
        printf("(<= ");
        printAST(node->data.children.left);
        printf(" ");
        printAST(node->data.children.right);
        printf(")");
        break;
    case NODE_IF:
        printf("(\n");
        tab_count++;
        printf("(if\n");
        panda = tab_count;
        printAST(node->data.control.cond);
        printf("\n");
        printAST(node->data.control.then_block);
        
        while (tab_count > panda)
        {
            printf("\n)");
            tab_count--;
        }
        panda = tab_count;
        if (node->data.control.else_block)
        {
            printf("\n");
            printAST(node->data.control.else_block);
        }
        while (tab_count > panda)
        {
            printf("\n)");
            tab_count--;
        }
        printf("\n)");
        break;
    case NODE_WHILE:
        printf("(\n");
        tab_count++;
        printf("(while\n");
        printAST(node->data.control.cond);
        printf("\n");
        panda = tab_count;
        printAST(node->data.control.then_block);
        while (tab_count > panda)
        {
            printf("\n)");
            tab_count--;
        }
        printf("\n)");
        break;
    case NODE_FOR:
        printf("(\n");
        tab_count++;
        printf("(for\n");
        printAST(node->data.for_control.init);
        printf("\n");
        printAST(node->data.for_control.cond);
        panda = tab_count;
        printf("\n(");
        printAST(node->data.for_control.upd);
        printf(" ");
        printAST(node->data.for_control.amount);
        printf(")\n");
        printAST(node->data.for_control.stmt);
        while (tab_count > panda)
        {
            printf("\n)");
            tab_count--;
        }
        printf("\n)\n)");
        break;
    case NODE_PRINT:
        printf("(\n");
        tab_count++;
        printf("(print ");
        if (node->data.io.format_str)
        {
            printf("\"");
            printAST(node->data.io.format_str);
        }
        if (node->data.io.args)
        {
            printf(" ");
            printAST(node->data.io.args);
        }
        printf(")");
        break;
    case NODE_SCAN:
        printf("(\n");
        tab_count++;
        printf("(scan \"");
        if (node->data.io.format_str)
        {
            printAST(node->data.io.format_str);
            printf("\"");
        }
        if (node->data.io.args)
        {
            printf(" ");
            printAST(node->data.io.args);
        }
        printf(")");
        break;
    case NODE_FORMAT:
        printf("@");
        if (node->data.children.left)
        {
            printAST(node->data.children.left);
        }
        break;
    case NODE_STRING_CONCAT:
        printf("%s", node->data.str_value);
        if (node->data.children.right)
        {
            printAST(node->data.children.right);
        }
        break;
    default:
        
        break;
    }
}

void freeAST(ASTNode *node)
{
    if (!node)
        return;
    switch (node->type)
    {
    case NODE_ID:
    case NODE_STRING:
    case NODE_TYPE:
    case NODE_STRING_CONCAT:
        free(node->data.str_value);
        break;
    case NODE_VAR_DECL:
        free(node->data.var_decl.var_name);
        freeAST(node->data.var_decl.var_type);
        break;
    case NODE_ASSIGN:
    case NODE_ADD_ASSIGN:
    case NODE_SUB_ASSIGN:
    case NODE_MUL_ASSIGN:
    case NODE_DIV_ASSIGN:
    case NODE_MOD_ASSIGN:
        freeAST(node->data.assign.target);
        freeAST(node->data.assign.expr);
        break;
    case NODE_IF:
    case NODE_WHILE:
        freeAST(node->data.control.cond);
        freeAST(node->data.control.then_block);
        if (node->data.control.else_block)
            freeAST(node->data.control.else_block);
        break;
    case NODE_FOR:
        freeAST(node->data.control.cond);
        freeAST(node->data.control.then_block);
        freeAST(node->data.control.else_block);
        freeAST(node->data.control.update);
        break;
    case NODE_PRINT:
    case NODE_SCAN:
        freeAST(node->data.io.format_str);
        freeAST(node->data.io.args);
        break;
    case NODE_FORMAT:
    case NODE_ADD:
    case NODE_SUB:
    case NODE_MUL:
    case NODE_DIV:
    case NODE_MOD:
    case NODE_EQ:
    case NODE_NEQ:
    case NODE_GT:
    case NODE_LT:
    case NODE_GTE:
    case NODE_LTE:
    case NODE_STATEMENT_LIST:
    case NODE_STATEMENT_LIST_2:
    case NODE_PROGRAM:
        freeAST(node->data.children.left);
        freeAST(node->data.children.right);
        break;
    default:
        break;
    }
    free(node);
}
