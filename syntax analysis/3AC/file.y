%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qind = 0;
char* l;
char* l2;
char cid[100];
char cidf[100];
char eee[5];
char temps[10]; 
char tp[100];
char up[3];
char upe[100];
char up2[3];
int flag;
struct quadruple {
    char operator[20], operand1[20], operand2[20], result[20];
} quad[100];
void addQuadruple(char op1[], char op[], char op2[], char result[]) {
    strcpy(quad[qind].operator, op);
    strcpy(quad[qind].operand1, op1);
    strcpy(quad[qind].operand2, op2);
    strcpy(quad[qind].result, result);
    qind++;
}
int printed_header = 0;
void display_Quad() {
    printf("%s := %s %s %s\n", quad[qind-1].result,
    quad[qind-1].operand1,
    quad[qind-1].operator,
    quad[qind-1].operand2);
}
int temp_char = 1;
char* tempVar() {
    static char temp[20];
    sprintf(temp, "t%d", temp_char++);
    return temp;
}

int temp_label=1;
char* tempLabel() {
    static char label[20];
    sprintf(label, "L%d", temp_label++);
    return label;
}

int tos = -1;
struct stack {
    char c[20];
} stk[100];

void push(char *c) {
    strcpy(stk[++tos].c, c);
}

char* pop() {
    return stk[tos--].c;
}


void yyerror(const char* s);
int yylex(void);
extern FILE* yyin;

int scan_count=0;
int print_count=0;
%}

%union {
    int ival;
    char* str;
}

%token <str> ID STRING_LETTER BINARY OCTAL DECIMAL ARY COMMA CHARACTER
%token INT BEGIN_VARDECL END_VARDECL CHAR SC BGN END OB CB AT
%token IF ASSIGNMENT ELSE PLUS MINUS MUL DIV MOD EQUAL GREATER LESSER GREATER_EQUAL LESSER_EQUAL NOT_EQUAL
%token FOR DO TO INC DEC WHILE BEGIN_PROGRAM END_PROGRAM PRINT 
%token TEN EIGHT TWO QUOTES PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN SCAN

%right ASSIGNMENT PLUS_ASSIGN MINUS_ASSIGN DIV_ASSIGN MUL_ASSIGN MOD_ASSIGN
%left EQUAL NOT_EQUAL
%left LESSER_EQUAL LESSER GREATER GREATER_EQUAL
%left PLUS MINUS
%left MUL DIV MOD
%nonassoc IF
%nonassoc IFX
%nonassoc ELSE

%type<str> arith int_const assignment_op_2


%%

assignment : BEGIN_PROGRAM var_dec statements END_PROGRAM {printf("\nSuccessfully parsed!\n"); return 0;}
    ;
    
var_dec : BEGIN_VARDECL decl END_VARDECL {}
    ;

decl : OB data COMMA type CB SC decl {}
    | {}
    ;

data : ID {}
    | ARY {}
    ;
    
type : INT {}
    | CHAR {}
    ;

statements : statement statements {}
    | {}
    ;
    
statement : assign {}
    | if_stmt {}
    | for_stmt {}
    | while_stmt {}
    | blck_stmt {}
    | print_stmt {}
    | scan_stmt {}
    ;

blck_stmt : BGN statements_1 END {}
    ;
    
statements_1 : stmt_1 statements_1 {}
    | {}
    ;
    
stmt_1 : assign {}
    | print_stmt {}
    | scan_stmt {}
    ;

if_stmt : IF OB relational CB tp1 BGN statements_1 END SC tp2 {}
    | IF OB relational CB tp1 BGN statements_1 END tp3 ELSE BGN statements_1 END SC tp2 %prec IFX {}
    ;
    
tp1 :  {l = tempLabel(); printf("if %s == %s goto %s\n", pop(), "0\0", l);}
    ;
    
tp2 : {printf("%s:\n",l); } 
    ;
    
tp3 : {strcpy(temps,l);l2=tempLabel(); printf("goto %s\n",l2); printf("%s:\n",temps);}
    ;
    
for_stmt : FOR idf ASSIGNMENT expr fw to_part fw2 update expr fw3 DO BGN statements_1 END SC fw4 {}
    ;

idf : ID {strcpy(cidf,$1);}
    ;

fw : {printf("%s := %s\n", cidf, pop()); 
l = tempLabel(); printf("%s:\n",l); 
strcpy(temps,l);
flag=0;
}
    ;

fw2 : { if(flag==0)
{char* temp = tempVar(); printf("%s := %s\n", temp, pop()); push(temp);}
strcpy(tp,pop());
flag=0;
}
    ;
    
fw3 : { if(flag==0)
{char* temp = tempVar(); printf("%s := %s\n", temp, pop()); push(temp);}
strcpy(upe,pop());
char* temp = tempVar();
addQuadruple(cidf, up, tp, temp);
display_Quad();
push(temp);

l = tempLabel(); printf("if %s == %s goto %s\n", pop(), "1\0", l);

}
    ;
    
fw4 : {char* temp = tempVar();
addQuadruple(cidf, up2, upe, temp);
display_Quad();
push(temp);

printf("%s := %s\n", cidf, pop());

printf("goto %s\n",temps); printf("%s:\n",l); 

}
    ;
    
to_part : TO expr {}
    ;
    
update : INC {strcpy(up,">"); strcpy(up2,"+");}
    | DEC {strcpy(up,"<");strcpy(up2,"-");}
    ;
    
while_stmt : WHILE OB tppw relational CB tpw DO BGN statements_1 END SC tpw2 {}
    ;

tppw : {l = tempLabel(); printf("%s:\n",l); 
strcpy(temps,l);
l2=tempLabel();}

tpw : {
printf("if %s == %s goto %s\n", pop(), "0\0", l2);}
    ;
    
tpw2 : {printf("goto %s\n",temps); printf("%s:\n",l2); }

print_stmt : PRINT QUOTES str QUOTES additional CB SC {if (print_count!=0) yyerror("PRINT STATEMENT ERROR\n");}
    | PRINT CB SC {} 
    ;
    
str : STRING_LETTER str {}
    | AT str {print_count+=1;}
    |  {}
    ;
    
additional : COMMA xyz additional {print_count--;}
    |  {}
    ;

xyz : ID {}
    | int_const {}
    | CHARACTER {}
    ;
    
scan_stmt: SCAN QUOTES pqr QUOTES additional_1 CB SC {if (scan_count!=0) yyerror("Invalid scan stmt");}
    ;

pqr : AT tuv {scan_count+=1;}
    ;

tuv : COMMA AT tuv {scan_count+=1;}
    |  {}
    ;

additional_1 : COMMA ID additional_1 {scan_count-=1;}
    |  {}
    ;
        
assign : id t2 {}
    ;

id : ID {strcpy(cid,$1);}
;

t2 : assignment_op_2 expr emp SC {printf("%s := %s\n", cid, pop());}
| ASSIGNMENT expr SC {printf("%s := %s\n", cid, pop());}
| ASSIGNMENT CHARACTER SC {printf("%s := %s\n", cid, $2);}
;

emp : {char* temp = tempVar();
addQuadruple(cid, eee, pop(), temp);
display_Quad();
push(temp);} 
    ;
    
assignment_op_2 : PLUS_ASSIGN {strcpy(eee,"+");}
    | MINUS_ASSIGN {strcpy(eee,"-");}
    | MUL_ASSIGN {strcpy(eee,"*");}
    | DIV_ASSIGN {strcpy(eee,"/");}
    | MOD_ASSIGN {strcpy(eee,"%");}
    ;
    
expr : arith {}
    ;
    
arith : arith PLUS arith {char* temp = tempVar();
addQuadruple(pop(), "+", pop(), temp);
display_Quad();
push(temp);flag=1;}
    | arith MINUS arith {char* temp = tempVar();
addQuadruple(pop(), "-", pop(), temp);
display_Quad();
push(temp);flag=1;}
    | arith MUL arith {char* temp = tempVar();
addQuadruple(pop(), "*", pop(), temp);
display_Quad();
push(temp);flag=1;}
    | arith DIV arith {char* temp = tempVar();
addQuadruple(pop(), "/", pop(), temp);
display_Quad();
push(temp);flag=1;}
    | arith MOD arith {char* temp = tempVar();
addQuadruple(pop(), "%", pop(), temp);
display_Quad();
push(temp);flag=1;}
    | ID {push($1);}
    | int_const {push($1);}
    ;

int_const : OB DECIMAL COMMA TEN CB {char* temp =(char*)malloc(30);
sprintf(temp, "(%s,10)", $2);$$=temp;}
   | OB OCTAL COMMA EIGHT CB {char* temp =(char*)malloc(30);
sprintf(temp, "(%s,8)", $2);$$=temp;}
   | OB BINARY COMMA TWO CB {char* temp =(char*)malloc(30);
sprintf(temp, "(%s,2)", $2);$$=temp;}
   | OB BINARY COMMA EIGHT CB {char* temp =(char*)malloc(30);
sprintf(temp, "(%s,8)", $2);$$=temp;}
   | OB BINARY COMMA TEN CB {char* temp =(char*)malloc(30);
sprintf(temp, "(%s,10)", $2);$$=temp;}
   | OB OCTAL COMMA TEN CB {char* temp =(char*)malloc(30);
sprintf(temp, "(%s,10)", $2);$$=temp;}
   ;
    
relational : relational EQUAL relational {char* temp = tempVar();
addQuadruple(pop(), "=", pop(), temp);
display_Quad();
push(temp);}
    | relational NOT_EQUAL relational {char* temp = tempVar();
addQuadruple(pop(), "<>", pop(), temp);
display_Quad();
push(temp);} 
    | relational GREATER relational {char* temp = tempVar();
addQuadruple(pop(), ">", pop(), temp);
display_Quad();
push(temp);}
    | relational LESSER relational {char* temp = tempVar();
addQuadruple(pop(), "<", pop(), temp);
display_Quad();
push(temp);}
    | relational GREATER_EQUAL relational {char* temp = tempVar();
addQuadruple(pop(), ">=", pop(), temp);
display_Quad();
push(temp);}
    | relational LESSER_EQUAL relational {char* temp = tempVar();
addQuadruple(pop(), "<=", pop(), temp);
display_Quad();
push(temp);}
    | arith {}
    ;

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    yyparse();
    fclose(yyin);
    return 0;
}

void yyerror(const char* s){
    printf("\nSyntax Error !!!\n");
    exit(1);
}
