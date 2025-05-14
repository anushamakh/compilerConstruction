/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING_LETTER = 259,
     BINARY = 260,
     OCTAL = 261,
     DECIMAL = 262,
     ARY = 263,
     COMMA = 264,
     CHARACTER = 265,
     INT = 266,
     BEGIN_VARDECL = 267,
     END_VARDECL = 268,
     CHAR = 269,
     SC = 270,
     BGN = 271,
     END = 272,
     OB = 273,
     CB = 274,
     AT = 275,
     IF = 276,
     ASSIGNMENT = 277,
     ELSE = 278,
     PLUS = 279,
     MINUS = 280,
     MUL = 281,
     DIV = 282,
     MOD = 283,
     EQUAL = 284,
     GREATER = 285,
     LESSER = 286,
     GREATER_EQUAL = 287,
     LESSER_EQUAL = 288,
     NOT_EQUAL = 289,
     FOR = 290,
     DO = 291,
     TO = 292,
     INC = 293,
     DEC = 294,
     WHILE = 295,
     BEGIN_PROGRAM = 296,
     END_PROGRAM = 297,
     PRINT = 298,
     TEN = 299,
     EIGHT = 300,
     TWO = 301,
     QUOTES = 302,
     PLUS_ASSIGN = 303,
     MINUS_ASSIGN = 304,
     MUL_ASSIGN = 305,
     DIV_ASSIGN = 306,
     MOD_ASSIGN = 307,
     SCAN = 308,
     IFX = 309
   };
#endif
/* Tokens.  */
#define ID 258
#define STRING_LETTER 259
#define BINARY 260
#define OCTAL 261
#define DECIMAL 262
#define ARY 263
#define COMMA 264
#define CHARACTER 265
#define INT 266
#define BEGIN_VARDECL 267
#define END_VARDECL 268
#define CHAR 269
#define SC 270
#define BGN 271
#define END 272
#define OB 273
#define CB 274
#define AT 275
#define IF 276
#define ASSIGNMENT 277
#define ELSE 278
#define PLUS 279
#define MINUS 280
#define MUL 281
#define DIV 282
#define MOD 283
#define EQUAL 284
#define GREATER 285
#define LESSER 286
#define GREATER_EQUAL 287
#define LESSER_EQUAL 288
#define NOT_EQUAL 289
#define FOR 290
#define DO 291
#define TO 292
#define INC 293
#define DEC 294
#define WHILE 295
#define BEGIN_PROGRAM 296
#define END_PROGRAM 297
#define PRINT 298
#define TEN 299
#define EIGHT 300
#define TWO 301
#define QUOTES 302
#define PLUS_ASSIGN 303
#define MINUS_ASSIGN 304
#define MUL_ASSIGN 305
#define DIV_ASSIGN 306
#define MOD_ASSIGN 307
#define SCAN 308
#define IFX 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "ast.y"
{
    int ival;
    char* str;
    ASTNode* ast;
}
/* Line 1529 of yacc.c.  */
#line 163 "ast.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

