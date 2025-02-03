/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_SRC_PARSER_H_INCLUDED
# define YY_YY_BUILD_SRC_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID_TK = 258,                   /* ID_TK  */
    NUM_TK = 259,                  /* NUM_TK  */
    PLUS_TK = 260,                 /* PLUS_TK  */
    MINUS_TK = 261,                /* MINUS_TK  */
    TIMES_TK = 262,                /* TIMES_TK  */
    DIV_TK = 263,                  /* DIV_TK  */
    LT_TK = 264,                   /* LT_TK  */
    LT_EQ_TK = 265,                /* LT_EQ_TK  */
    GT_TK = 266,                   /* GT_TK  */
    GT_EQ_TK = 267,                /* GT_EQ_TK  */
    EQ_TK = 268,                   /* EQ_TK  */
    NEQ_TK = 269,                  /* NEQ_TK  */
    ASSIGN_TK = 270,               /* ASSIGN_TK  */
    SEMICOLON_TK = 271,            /* SEMICOLON_TK  */
    COMMA_TK = 272,                /* COMMA_TK  */
    LPAR_TK = 273,                 /* LPAR_TK  */
    RPAR_TK = 274,                 /* RPAR_TK  */
    LBRACKET_TK = 275,             /* LBRACKET_TK  */
    RBRACKET_TK = 276,             /* RBRACKET_TK  */
    LBRACE_TK = 277,               /* LBRACE_TK  */
    RBRACE_TK = 278,               /* RBRACE_TK  */
    ELSE_TK = 279,                 /* ELSE_TK  */
    IF_TK = 280,                   /* IF_TK  */
    INT_TK = 281,                  /* INT_TK  */
    RETURN_TK = 282,               /* RETURN_TK  */
    VOID_TK = 283,                 /* VOID_TK  */
    WHILE_TK = 284                 /* WHILE_TK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_SRC_PARSER_H_INCLUDED  */
