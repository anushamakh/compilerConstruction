%{
#include "ast.h"
#include "ast.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char* s);
int m_comment=0;
static char *ary[50];
int ary_count=0;
%}

%x COMMENT
%x VAR_1
%x VAR_COMMENT
%x BI
%x STRINGS
%x SCANS1
%x SCANS

lowercase [a-z]
digits [0-9]
space [ ]
keywords (int)|(char)|(if)|(else)|(while)|(for)|(main)|(begin)|(end)|(print)|(scan)|(VarDecl)|(program)|(inc)|(dec)
identifier {lowercase}({lowercase}|{digits})*[_]?({lowercase}|{digits})*
inv_identifier ({lowercase}|{digits}|_)*
oct_inv_const \({space}*{digits}*(9){digits}*{space}*,{space}*8{space}*\)
bin_inv_const \({space}*{digits}*[3-9]{digits}*{space}*,{space}*2{space}*\)
invalid_const \({space}*{digits}*{space}*,{space}*(((0|2-9){digits}*)|((1){digits}{digits}+)|((1)[1-9])){space}*\)


%%
"to" {return TO;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"for" {return FOR;}
"inc" {return INC;}
"dec" {return DEC;}
"int" {return INT;}
"char" {return CHAR;}
"begin"{space}*"program"{space}*":" { return BEGIN_PROGRAM;}
"end"{space}*"program" {return END_PROGRAM;}
"begin" {return BGN;}
"end" {return END;}
"do" {return DO;}
[0-1]+/"," {yylval.str = strdup(yytext); BEGIN(BI); return BINARY;}
[0-7]+/"," {yylval.str = strdup(yytext); BEGIN(BI); return OCTAL;}
{digits}+/"," {yylval.str = strdup(yytext); BEGIN(BI); return DECIMAL;}
<BI>"2" {BEGIN(0); return TWO;}
<BI>{space}* {}
<BI>"8" {BEGIN(0); return EIGHT;}
<BI>"10" {BEGIN(0); return TEN;}
<BI>"," {return COMMA;}
<BI>. {yyerror("Syntax Error");}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return EQUAL;}
">" {return GREATER;}
"<" {return LESSER;}
">=" {return GREATER_EQUAL;}
"<=" {return LESSER_EQUAL;}
"<>" {return NOT_EQUAL;}
";" {return SC;}
"," {return COMMA;}
"(" {return OB;}
")" {return CB;}
":=" {return ASSIGNMENT;}
"\+=" {return PLUS_ASSIGN;}
"-=" {return MINUS_ASSIGN;}
"\*=" {return MUL_ASSIGN;}
"\/=" {return DIV_ASSIGN;}
"%=" {return MOD_ASSIGN;}
{oct_inv_const} {yyerror("Syntax Error");}
{bin_inv_const} {yyerror("Syntax Error");}
{invalid_const} {yyerror("Syntax Error");}
print{space}*\( {return PRINT;}
[\"] {BEGIN(STRINGS); return QUOTES;}
<STRINGS>"@" {return AT;}
<STRINGS>[\"] {BEGIN(0); return QUOTES;}
<STRINGS>. {yylval.str = strdup(yytext); return STRING_LETTER;}
scan{space}*\( {BEGIN(SCANS1);return SCAN;}
<SCANS1>[\"] {BEGIN(SCANS);return QUOTES;}
<SCANS1>{space}* {}
<SCANS1>. {yyerror("Syntax Error");}
<SCANS>"@" {return AT;}
<SCANS>"," {yylval.str = strdup(yytext);return COMMA;}
<SCANS>[\"] {BEGIN(0); return QUOTES;}
<SCANS>{space} {}
<SCANS>. {return STRING_LETTER;}
"//"(.)*\n {}
"/*" {BEGIN(COMMENT); m_comment++; yymore();}
<COMMENT>"/*" {m_comment++; yymore();}
<COMMENT>. {yymore();}
<COMMENT>\n {yymore();}
<COMMENT>"*/" {m_comment--; if(m_comment==0) BEGIN(0); else yymore();}
"begin"{space}*"VarDecl"{space}*":" {BEGIN(VAR_1); return BEGIN_VARDECL;}
<VAR_1>"end"{space}*"VarDecl" {BEGIN(0); return END_VARDECL;}
<VAR_1>"//"(.)*\n {}
<VAR_1>"/*" {BEGIN(VAR_COMMENT); m_comment++; yymore();}
<VAR_COMMENT>"/*" {m_comment++; yymore();}
<VAR_COMMENT>. {yymore();}
<VAR_COMMENT>\n {yymore();}
<VAR_COMMENT>"*/" {m_comment--; if(m_comment==0) {BEGIN(VAR_1);} else {yymore();} }
<VAR_1>";" {return SC;}
<VAR_1>"," {return COMMA;}
<VAR_1>"(" {return OB;}
<VAR_1>")" {return CB;}
<VAR_1>{space}*{identifier}\[{digits}*\]{space}* { yylval.str = strdup(yytext); return ARY;}
<VAR_1>{identifier}/"," { yylval.str = strdup(yytext); return ID;}
<VAR_1>{inv_identifier}/"," {yyerror("Syntax Error");}
<VAR_1>"int" {return INT;}
<VAR_1>"char" {return CHAR;}
<VAR_1>'\\n' {yylval.str= strdup(yytext); return CHARACTER;}
<VAR_1>'\\t' {yylval.str= strdup(yytext); return CHARACTER;}
<VAR_1>{space}|\n {}
<VAR_1>'.' {yylval.str= strdup(yytext); return CHARACTER;}
<VAR_1>EOF {return EOF;}
<VAR_1>. {yyerror("Syntax Error");}
{keywords} {yyerror("Syntax Error");}
{keywords}\[{digits}+\]{space}* {yyerror("Syntax Error");}
{identifier} {yylval.str = strdup(yytext); return ID;}
{identifier}\[{digits}+\]{space}* {yylval.str = strdup(yytext); return ID;}
{inv_identifier} {yyerror("Syntax Error");}
'\\n' {yylval.str= strdup(yytext); return CHARACTER;}
'\\t' {yylval.str= strdup(yytext); return CHARACTER;}
'.' { yylval.str= strdup(yytext); return CHARACTER;}
{space}|\n {}
EOF {return EOF;}
. {printf("UNMATCHED Character\n");yyerror("Syntax Error");}
%%

int yywrap(void){
    return 1;
}

