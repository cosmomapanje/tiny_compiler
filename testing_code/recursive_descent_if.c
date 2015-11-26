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

enum token {
	IF,
	THEN,
	ELSE,
	BEGIN,
	END,
	PRINT,
	SEMI,
	EQ,
	NUM
};

#pragma pack(4)

static struct token_symbols {
	char *name;
	int token_value;
}tokens[] = {{"if", IF}, {"then", THEN}, {"else", ELSE}, {"begin", BEGIN}, {"end", END}, {"print", PRINT}, {";", SEMI}, {"=", EQ}, {"", NUM}};

#pragma pack(8)

enum token tok;
void token_id(char *token_p)
{
	int i = 0;
	for (; i < (sizeof(tokens)/sizeof(tokens[0])); i++) {
		if (0 == strcmp(tokens[i].name, token_p))
			tok = tokens[i].token_value;
	}
}

void getToken(void)
{
	char *token_p;

	if (!strlen(saveptr)) {
		memset(input, '\0', 256);
		fgets(input, 256, stdin);
		saveptr = input;
	}
	token_p = strtok_r(NULL, " \n", &saveptr); 
	if (token_p == NULL) {
		getToken();
	} else {
		token_id(token_p);
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

int main()
{
	return 0;
}
