/*
 * S -> E $
 *
 * E -> T E'
 *
 * E'-> + T E'
 * E'-> - T E'
 * E'->
 *
 * T -> F T'
 *
 * T'-> * F T'
 * T'-> / F T'
 * T'->
 *
 * F -> id
 * F -> num
 * F -> (E)
 *
 */

/*
 * predictive parsing table
 * 	+	*	id	(	)	$
 * S	
 * E
 * E'
 * T
 * T'
 * F
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_CODE 0
#define ERROR_CODE1 1
#define ERROR_CODE2 2
#define ERROR_CODE3 3

#define IS_ASCII_NUM(x) ({typeof(x) (__x) = (x);	\
		(((__x) >= 0x30) && ((__x) <= 0x39)) ? 1 : 0;})

static char input[256];
static char *saveptr = input;
static char this_char;

void in_error(int flag)
{
	printf("error[%d]!\n", flag);
	exit(-1);
}

void getToken(void)
{
	memset(input, '\0', 256);
	fgets(input, 256, stdin);
	saveptr = input;
}

#if 0
void eat(enum token t)
{
	if (tok == t) {
		getToken();
	} else {
		in_error(ERROR_CODE2);
	}
}

void L(void)
{
}

#endif

int F(void)
{
	/*
	 * F -> id
	 * F -> num
	 * F -> (E)
	 */
	int num = 0;
	int temp = 0;
	if ('(' == this_char) {
		eat('(');
		temp = E();
		eat(')');
	}
	if (isdigit(this_char)) {
		ungetc(this_char, stdin);
		scanf("%d", &num);
		this_char = getchar();
	}
	return num;
}

int T_(void)
{
	switch (this_char) {
	case '*':
		F();
		T_();
		break;
	case '/':
		F();
		T_();
		break;
	default:
		break;
	}
}

void T(void)
{
	F();
	T_();
}

int E_(void)
{
	switch (this_char) {
	case '+':
		T();
		E_();
		break;
	case '-':
		T();
		E_();
		break;
	default:
		break;
	}
}

void E(void)
{
	T();
	E_();
}

void S(void)
{
	E();
}

int main()
{
	//getToken();
	while (1) {
		//S();

	}
	return 0;
}
