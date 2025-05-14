%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int m_comment=0;
int inp=0;
char **ary;
int ary_size=20;
int ary_count=0;
int ag;

void check(const char *str);
%}

%x COMMENT
%x VAR_1
%x VAR_2
%x VAR_COMMENT
%x SCANF
%x ARGCNT
%x EWWOW
%x PRINTF
%x PFCNT
%x EWW

lowercase [a-z]
digits [0-9]
separator [_;,:{}()]
space [ ]
arithmetic [+\-*/%]
relational =|>|<|(>=)|(<=)|(<>)
assignment (:=)|(\+=)|(-=)|(\*=)|(\/=)|(%=)
type (int)|(char)
keywords (int)|(char)|(if)|(else)|(while)|(for)|(main)|(begin)|(end)|(print)|(scan)|(VarDecl)|(program)|(inc)|(dec)
identifier {lowercase}({lowercase}|{digits})*[_]?({lowercase}|{digits})*
inv_identifier ({lowercase}|{digits}|_)*
dec_const \({space}*{digits}*{space}*,{space}*10{space}*\)
oct_const \({space}*[0-7]*{space}*,{space}*8{space}*\)
bin_const \({space}*[01]*{space}*,{space}*2{space}*\)
oct_inv_const \({space}*{digits}*{space}*,{space}*8{space}*\)
bin_inv_const \({space}*{digits}*{space}*,{space}*2{space}*\)


%%
{dec_const} {printf("%-25s\tINTEGER CONSTANT\n", yytext);}
{oct_const} {printf("%-25s\tINTEGER CONSTANT\n", yytext);}
{bin_const} {printf("%-25s\tINTEGER CONSTANT\n", yytext);}
{oct_inv_const} {printf("%-25s\tERROR: INVALID INTEGER CONSTANT\n", yytext);}
{bin_inv_const} {printf("%-25s\tERROR: INVALID INTEGER CONSTANT\n", yytext);}
{arithmetic} {printf("%-25s\tARITHMETIC OPERATOR\n", yytext);}
{relational} {printf("%-25s\tRELATIONAL OPERATOR\n", yytext);}
{assignment} {printf("%-25s\tASSIGNMENT OPERATOR\n", yytext);}
{separator} {printf("%-25s\tSEPARATOR\n", yytext);}
({space}*[\"][^\"]*[\"]{space}*) {printf("%-25s\tSTRING\n", yytext);}
\({space}*{keywords}\[{digits}*\]{space}*,{space}*int{space}*\) {printf("%-25s\tERROR: INVALID INTEGER ARRAY\n", yytext);}
\({space}*{keywords}\[{digits}*\]{space}*,{space}*char{space}*\) {printf("%-25s\tERROR: INVALID CHAR ARRAY\n", yytext);}
\({space}*{identifier}\[{digits}*\]{space}*,{space}*int{space}*\) {printf("%-25s\tINTEGER ARRAY\n", yytext);}
\({space}*{identifier}\[{digits}*\]{space}*,{space}*char{space}*\) {printf("%-25s\tCHAR ARRAY\n", yytext);}
scan\( {printf("%s",yytext); BEGIN(SCANF);}
<SCANF>{space}*[\"][^(\"|\n)]*[\"]{space}* {yymore(); char l[100]; strncpy(l,yytext,yyleng); l[yyleng]='\0'; ag=0; int st = 0;
for(int i=0; l[i]!='\0'; i++)
{
	if(l[i]==' ' || l[i]=='"') {continue;}
	else if(st==0)
	{
	if(l[i]=='@') {ag++; st=1;}
	else {st=0; break;}
	}
	else if(st==1)
	{
	if(l[i]==',') {st=0;}
	else {st=0; break;}
	}
}
if(st==1) BEGIN(ARGCNT);
else if(st==0) {BEGIN(EWWOW);}
}
<SCANF>. {yymore(); BEGIN(EWWOW);}
<ARGCNT>,{space}*{identifier}{space}* {yymore(); ag--;}
<ARGCNT>\){space}*;{space}* {if(ag==0){printf("%-25s\tVALID INPUT STATEMENT\n", yytext); BEGIN(0);} else {yymore(); BEGIN(EWWOW);}}
<ARGCNT>. {yymore(); BEGIN(EWWOW);}
<EWWOW>\n {yyless(yyleng-1); printf("%-25s\tERROR: INVALID INPUT STATEMENT\n", yytext); BEGIN(0);}
<EWWOW>. {yymore();}
print\( {yymore(); BEGIN(PRINTF);}
<PRINTF>{space}*[\"][^(\"||\n)]*[\"]{space}* {yymore(); char l[100]; strncpy(l,yytext,yyleng); l[yyleng]='\0'; ag=0;
for(int i=0; l[i]!='\0'; i++)
{
	if(l[i]=='@')
		ag++;
}
BEGIN(PFCNT);
}
<PRINTF>. {yymore();BEGIN(EWW);}
<PFCNT>,{space}*{identifier}{space}* {yymore(); ag--;}
<PFCNT>,{space}*({dec_const}|{oct_const}|{bin_const}){space}* {yymore(); ag--;}
<PFCNT>\){space}*;{space}* {if(ag==0) {printf("%-25s\tVALID OUTPUT STATEMENT\n", yytext); BEGIN(0);} else {yymore(); BEGIN(EWW);}}
<PFCNT>. {yymore(); BEGIN(EWW);}
<EWW>\n {yyless(yyleng-1); printf("%-25s\tERROR: INVALID OUTPUT STATEMENT\n", yytext); BEGIN(0);}
<EWW>. {yymore();}
"//"(.)*\n {yyless(yyleng-1); printf("%-25s\tSINGLE-LINE COMMENT\n", yytext);}
"/*" {BEGIN(COMMENT); m_comment++; yymore();}
<COMMENT>"/*" {m_comment++; yymore();}
<COMMENT>. {yymore();}
<COMMENT>\n {yymore();}
<COMMENT>"*/" {m_comment--; if(m_comment==0) {BEGIN(0); {printf("%-25s\tMULTI-LINE COMMENT\n", yytext);}} else {yymore();} }
"VarDecl" {printf("%-25s\tKEYWORD\n", yytext); BEGIN(VAR_1);}
<VAR_1>"end"/{space}*"VarDecl" {printf("%-25s\tKEYWORD\n", yytext); BEGIN(VAR_2);}
<VAR_1>"//"(.)*\n {yyless(yyleng-1); printf("%-25s\tSINGLE-LINE COMMENT\n", yytext);}
<VAR_1>"/*" {BEGIN(VAR_COMMENT); m_comment++; yymore();}
<VAR_COMMENT>"/*" {m_comment++; yymore();}
<VAR_COMMENT>. {yymore();}
<VAR_COMMENT>\n {yymore();}
<VAR_COMMENT>"*/" {m_comment--; if(m_comment==0) {BEGIN(VAR_1); {printf("%-25s\tMULTI-LINE COMMENT\n", yytext);}} else {yymore();} }
<VAR_1>{arithmetic} {printf("%-25s\tARITHMETIC OPERATOR\n", yytext);}
<VAR_1>{relational} {printf("%-25s\tRELATIONAL OPERATOR\n", yytext);}
<VAR_1>{assignment} {printf("%-25s\tASSIGNMENT OPERATOR\n", yytext);}
<VAR_1>{separator} {printf("%-25s\tSEPARATOR\n", yytext);}
<VAR_1>{identifier}/"," {check(yytext);}
<VAR_1>{inv_identifier}/"," {printf("%-25s\tERROR: INVALID IDENTIFIER\n", yytext);}
<VAR_1>{type} {printf("%-25s\tKEYWORD\n", yytext);}
<VAR_1>'\\n' {printf("%-25s\tNEWLINE CHARACTER\n", yytext);}
<VAR_1>'\\t' {printf("%-25s\tTAB CHARACTER\n", yytext);}
<VAR_1>{space}|\n {}
<VAR_1>. {printf("%-25s\tCHARACTER\n", yytext);}
<VAR_2>"VarDecl" {printf("%-25s\tKEYWORD\n", yytext); BEGIN(0);}
<VAR_2>{space}|\n {}
{keywords} {printf("%-25s\tKEYWORD\n", yytext);}
{identifier} {printf("%-25s\tIDENTIFIER\n", yytext);}
{inv_identifier} {printf("%-25s\tERROR: INVALID IDENTIFIER\n", yytext);}
'\\n' {printf("%-25s\tNEWLINE CHARACTER\n", yytext);}
'\\t' {printf("%-25s\tTAB CHARACTER\n", yytext);}
'.' {printf("%-25s\tCHARACTER\n", yytext);}
{space}|\n {}
EOF {return 0;}
%%

void check(const char *str){
    const char *keywords[]={"int", "char", "if", "else", "while", "for", "main", "begin", "end", "print", "scan", "program", "VarDecl", "inc", "dec", "then", "to", "do"};
    int num=sizeof(keywords)/sizeof(keywords[0]);

    for(int i=0; i<num; i++){
        if(strcmp(str, keywords[i])==0){
            printf("%-25s\tError: Keyword is used as an identifier\n",str);
            return;
        }
    }

    for(int i=0; i<ary_count; i++) {
        if(strcmp(ary[i], str)==0) {
            printf("%-25s\tError: identifier already declared\n",str);
            return;
        }
    }

    if(ary_count>=ary_size) {
        ary_size*=2;
        ary=(char **)realloc(ary, ary_size*sizeof(char *));
    }

    ary[ary_count]=(char *)malloc(strlen(str) + 1);
    strcpy(ary[ary_count], str);
    ary_count++;

    printf("%-25s\tIDENTIFIER\n", str);
}

int main(){
    ary=(char **)malloc(ary_size*sizeof(char *));
    printf("LEXEME                   \tTOKEN TYPE\n\n");

    yyin=fopen("input.txt", "r");
    yylex();

    for(int i=0; i<20; i++){
        free(ary[i]);
    }
    free(ary);

    return 0;
}