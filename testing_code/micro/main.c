#include <stdio.h>
#include <ctype.h>
#include "all.h"

token scanner(void)
{
	int in_char, c;

	while ((in_char = getchar()) != EOF) {
		if (isspace(in_char)) {
			continue;
		} else if (isalpha(in_char)) {
	        	/* 
			 * ID ::= LETTER | ID LETTER
			 *               | ID DIGIT
			 *		   | ID UNDERSCORE
			 */
			for (c = getchar(); isalnum(c) || c == '_'; c = getchar())
				;
			ungetc(c, stdin);
			return ID;
		} else if (isdigit(in_char)) {
			/* 
			 * INTLITERAL ::= DIGIT |
			 *                INTLITERAL DIGIT
			 */
			while (isdigit((c = getchar())))
				;
			ungetc(c, stdin);
			return INTLITERAL;
		} else if (in_char == '(') {
			return LPAREN;
		} else if (in_char == ')') {
			return RPAREN;
		} else if (in_char == ';') {
			return SEMICOLON;
		} else if (in_char == ',') {
			return COMMA;
		} else if (in_char == '+') {
			return PLUSOP;
		} else if (in_char == ':') {
			/* looking for ":=" */
			c = getchar ();
			if (c == '=') {
				return ASSIGNOP;
			} else {
				ungetc(c, stdin);
				lexical_error(in_char);
			}
		} else if (in_char == '-') {
		  	/* looking for "--", comment start */
			c = getchar ();
			if (c == '-') {
				while ((in_char = getchar()) != '\n');
			} else {
				ungetc(c, stdin);
				return MINUSOP;
			}
		} else {
			lexical_error(in_char);
		}
	}
}

int main(int argc, char **argv)
{
	return 0;
}
