#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>
#define MAX_TOKEN_SIZE (100)
#define MAX_LINE_SIZE (1024)

#define ENUM_TOKEN_TYPE_NUM (11)
#define ENUM_SIGN_TOKEN_NUM (16)

extern FILE *source_file;
typedef enum {
	KEYWORD_TOKEN,
	SIGN_TOEKN,
	IDENTIFIER_TOKEN,
	NUMBER_TOKEN,
	STRING_TOKEN,
	REGEXPRESSION_TOKEN,
	SPACE_TOKEN,
	NEWLINE_TOKEN,
	COMMENT_TOKEN,
	END_OF_LINE_TOKEN,
	END_OF_FILE_TOKEN
} token_type;

typedef enum {
	PLUS = ENUM_TOKEN_TYPE_NUM,
	MINUS,
	TIMES,
	OVER,
	ASSIGN,
	LT,
	GT,
	LPAREN,
	RPAREN,
	LSHIFT,
	RSHIFT,
	SEMI,
	LTOREQ,
	GTOREQ,
	EQUAL,
	ERROR
} sign_token;

typedef enum {
	AUTO = ENUM_SIGN_TOKEN_NUM + ENUM_TOKEN_TYPE_NUM,
	BREAK,
	CASE,
	CHAR,
	CONST,
	CONTINUE,
	DEFAULT,
	DO,
	DOUBLE,
	ELSE,
	ENUM,
	EXTERN, 
	FLOAT, 
	FOR, 
	GOTO,
	IF,
	INT,
	LONG,
	REGISTER,
	RETURN,
	SHORT,
	SIGNED,
	SIZEOF,
	STATIC,
	STRUCT,
	SWITCH,
	TYPEDEF,
	UNION,
	UNSIGNED,
	VOID,
	VOLATILE,
	WHILE,
	NONE
} keyword_token;

struct _keyword {
	char *keyword_str;
	char keyword_value;
};

typedef enum {
	INITIAL_STATUS,
	INSTRING_STATUS,
	INSIGN_STATUS,
	INCOMMENT_STATUS,
	INNUM_INT_STATUS,
	INNUM_DOT_STATUS,
	INNUM_DEC_STATUS,
	INIDENTIFIER_STATUS,
	INREGEXP_STATUS,
	INFINISH_STATUS,
	INERROR_STATUS
}lexer_status;

typedef struct {
	token_type this_type;
	double value;
	char str[MAX_TOKEN_SIZE];
} token;

enum {
	FALSE,
	TRUE
};

#endif
