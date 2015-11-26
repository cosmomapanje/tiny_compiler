/*
 * S -> if E then S else S
 * S -> begin S L
 * S -> print E
 *
 * L -> end
 * L -> ; S L
 *
 * E -> num = num
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[] = "if E then S else S";
FILE *source;

static char input[256];
static char *saveptr = input;
static char *token_symbol[] = {"if","then","else","begin","end","print",";","="}; /* no num */
enum token {
	IF,
	THEN,
	ELSE,
	BEGIN,
	END,
	PRINT,
	SEMI,
	NUM,
	EQ
};

enum token tok;

void getToken(void)
{
	char *token;

	if (!strlen(saveptr)) {
		memset(input, '\0', 256);
		fgets(input, 256, stdin);
		saveptr = input;
	}
	token = strtok_r(NULL, " \n", &saveptr); 
	if (token == NULL) {
		getToken();
	}
}

void eat(enum token t)
{
	if (tok == t) {
		tok = getToken();
	} else {
		error();
	}
}

void S(void)
{
	switch (tok) {
	case IF:
		eat(IF);
		E();
		eat(THEN);
		S();
		eat(ELSE);
		S();
		break;
	case BEGIN:
		eat(BEGIN);
		S();
		L();
		break;
	case PRINT:
		eat(PRINT);
		E();
		break;
	default:
		error();
		break;
	}
}

void L(void)
{
	switch (tok) {
	case END:
		eat(END);
		break;
	case SEMI:
		eat(SEMI);
		S();
		L();
		break;
	default:
		error();
		break;
	}
}

void E(void)
{
	eat(NUM);
	eat(EQ);
	eat(NUM);
}
