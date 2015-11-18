#include <stdio.h>
#include "global.h"
static char *one_line;
static int one_line_pos;
static char token_buf[MAX_TOKEN_SIZE + 1];

__attribute__(alway_inline) char isseparator(const char byte)
{
	return ('\t' == byte) ||
		(' ' == byte) ||
		('\n' == byte) ? 
		(char) 1 : (char) 0;
}

static unsigned char get_next_char()
{
	/* get one char from instring */
}
static void unget_next_char()
{
	/* put back one char to instring */
}

token_type get_token(token *token)
{
	token_type current_token_t;
	lexer_status status = INITIAL_STATUS;
	char cc;
	char only_one_char_sign = TRUE;
	char skip = FALSE;
	unsigned char token_len = 0;

	while (status != INFINISH_STATUS) {
		cc = get_next_char();
		switch (status) {
		case INITIAL_STATUS:
			if ('"' == cc) {
				status = INSTRING_STATUS;
			} else if (isdigit(cc)) {
				status = INNUM_INT_STATUS;
			} else if (isalpha(cc) || ('_' == cc)) {
				status = INIDENTIFIER_STATUS;
			} else if ('`' == cc) {
				status = INREGEXP_STATUS;
			} else if ('#' == cc) {
				status = INCOMMENT_STATUS;
			} else if (isseparator(cc)) {
				skip = TRUE;
			} else {
				status = INFINISH_STATUS;
				switch (cc) {
				case '+':
					current_token_t = PLUS;
					break;
				case '-': current_token_t = MINUS;
					break;
				case '*':
					current_token_t = TIMES;
					break;
				case '/':
					current_token_t = OVER;
					break;
				case '=':
					current_token_t = ASSIGN;
					status = INSIGN_STATUS;
					break;
				case '<':
					current_token_t = LT;
					status = INSIGN_STATUS;
					break;
				case '>':
					current_token_t = GT;
					status = INSIGN_STATUS;
					break;
				case '(':
					current_token_t = LPAREN;
					break;
				case ')':
					current_token_t = RPAREN;
					break;
				case ';':
					current_token_t = SEMI;
					break;
				default:
					current_token_t = ERROR;
					break;
				}
			}
			break;
		case INSTRING_STATUS:
			break;
		case INSIGN_STATUS:
			if (current_token_t == LT) {
				if ('<' == cc) {
					current_token_t = LSHIFT;
				} else if ('=' == cc) {
					current_token_t = LTOREQ;
				} else {
				}
			} else if (current_token_t == GT) {
				if ('>' == cc) {
					current_token_t = RSHIFT;
				} else if ('=' == cc) {
					current_token_t = RTOREQ;
				} else {
				}
			} else if (current_token_t == ASSIGN) {
				if ('=' == cc) {
					current_token_t = EQUAL;
				} else {
				}
			} else {
				/* no way to get here */
			}
			status = INFINISH_STATUS;
			break;
		case INCOMMENT_STATUS:
			skip = TRUE;
			if ('\n' == cc) {
				status = INITIAL_STATUS;
			} else if (EOF == cc) {
				status == INFINISH_STATUS;
				current_token_t = ENDFILE;
			} else {
				status = INCOMMENT_STATUS;
			}
			break;
		case INNUM_INT_STATUS:
			if (isdigit(cc)) {
				status = INNUM_INT_STATUS;
			} else if ('.' == cc) {
				status = INNUM_DOT_STATUS;
			} else {
				status = INERROR_STATUS;
			}
			break;
		case INNUM_DOT_STATUS:
			if (isdigit(cc)) {
			} else {
			}
			break;
		case INNUM_DEC_STATUS:
			if (!isdigit(cc)) {
				status = INFINISH_STATUS;
			}
			break;
		case INIDENTIFIER_STATUS:
			if ((!isdigit(cc)) || (!isalpha(cc)) || ('_' == cc)) {
				status = INFINISH_STATUS;
			}
			break;
		case INREGEXP_STATUS:
			if ('`' == cc) {
				status = INFINISH_STATUS;
			}
			break;
		case INFINISH_STATUS:
			break;
		case INERROR_STATUS:
			/* point to where is wrong */
			exit(-1);
		default:
			break;
		}


		if (INFINISH_STATUS == status) {
			/* Do some saving token work */	
			token_buf[token_len] = '\0';
		}
	}
}

int main(int argc, char **argv)
{

}
