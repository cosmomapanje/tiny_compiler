#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "symbol_table.h"

static char *one_line;
static int one_line_pos;
static int one_line_have;
static char token_buf[MAX_TOKEN_SIZE + 1];
static char line_buf[MAX_LINE_SIZE + 1];

__attribute__((alway_inline)) char isseparator(const char byte);

char isseparator(const char byte)
{
	return ('\t' == byte) ||
		(' ' == byte) ||
		('\n' == byte) ? 
		(char) 1 : (char) 0;
}

static unsigned char get_next_char()
{
	/* get one char from instring */
	if (!(one_line_pos < one_line_have)) {
		if (NULL != fgets(line_buf, MAX_LINE_SIZE, source_file)) {
			one_line_have = strlen(line_buf);
			one_line_pos = 0;
			printf("len = %d = %s\n",one_line_have,  line_buf);
		} else {
			if (0 != feof(source_file)) {
				return EOF;
			} else {
				/* some errors happened, need to check */
			}
		}
	}
	return line_buf[one_line_pos++];
}
static void unget_next_char()
{
	/* move index back one char in line buf */
	if (0 == feof(source_file)) {
		one_line_pos--;
	}
}

token_type get_token(token *token)
{
	token_type current_token_t;
	lexer_status status = INITIAL_STATUS;
	char cc;
	char only_one_char_sign = TRUE;
	char skip = FALSE;
	unsigned char token_pos = 0;

	while (status != INFINISH_STATUS) {
		skip = FALSE;
		cc = get_next_char();
		switch (status) {
		case INITIAL_STATUS:
			if ('"' == cc) {
				status = INSTRING_STATUS;
			} else if (isdigit((int)cc)) {
				status = INNUM_INT_STATUS;
			} else if (isalpha((int)cc) || ('_' == cc)) {
				status = INIDENTIFIER_STATUS;
			} else if ('`' == cc) {
				status = INREGEXP_STATUS;
			} else if ('#' == cc) {
				skip = TRUE;
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
				case EOF:
					current_token_t = END_OF_FILE_TOKEN;
					break;
				default:
					current_token_t = ERROR;
					break;
				}
			}
			break;
		case INSTRING_STATUS:
			if ('"' == cc) {
				status = INFINISH_STATUS;
			}
			break;
		case INSIGN_STATUS:
			if (current_token_t == LT) {
				if ('<' == cc) {
					current_token_t = LSHIFT;
				} else if ('=' == cc) {
					current_token_t = LTOREQ;
				} else {
					skip = TRUE;
					unget_next_char();
				}
			} else if (current_token_t == GT) {
				if ('>' == cc) {
					current_token_t = RSHIFT;
				} else if ('=' == cc) {
					current_token_t = GTOREQ;
				} else {
					skip = TRUE;
					unget_next_char();
				}
			} else if (current_token_t == ASSIGN) {
				if ('=' == cc) {
					current_token_t = EQUAL;
				} else {
					skip = TRUE;
					unget_next_char();
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
				current_token_t = END_OF_FILE_TOKEN;
			} else {
				status = INCOMMENT_STATUS;
			}
			break;
		case INNUM_INT_STATUS:
			if ('.' == cc) {
				status = INNUM_DOT_STATUS;
			} else if (!isdigit(cc)) {
				status = INFINISH_STATUS;
				skip = TRUE;
				unget_next_char();
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
			if (isdigit((int)cc) || isalpha((int)cc) || ('_' == cc)) {
				current_token_t = IDENTIFIER_TOKEN;
			} else {
				skip = TRUE;
				status = INFINISH_STATUS;
				unget_next_char();
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

		if (!skip && (token_pos <= MAX_TOKEN_SIZE)) {
			token_buf[token_pos++] = cc;
		} else {
			/* skip or token length is too long*/
		}

		if (INFINISH_STATUS == status) {
			/* Do some saving token work */	
			token_buf[token_pos] = '\0';
			if (IDENTIFIER_TOKEN == current_token_t) {
				if (NONE != is_key_word(token_buf, token_pos)) {
					current_token_t = KEYWORD_TOKEN;
				}
			}
			printf("token = %d = %s\n", token_pos, token_buf);
		}
	}
	return current_token_t;
}

