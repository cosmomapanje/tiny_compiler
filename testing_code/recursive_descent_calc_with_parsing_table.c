


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
 * 	nullable	FIRST		FOLLOW
 * S	no		( id num
 * E	no		( id num	) $
 * E'	yes		+ -		) $
 * T	no		( id num	) + - $
 * T'	yes		* /		) + - $
 * F	no		( id num	) * / + - $
 */

/*
 * predictive parsing table
 * 	+	-	*	/	id	num	(	)	$
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
static int result;

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

#if 1
void eat(char expected_char)
{
	if (expected_char == this_char) {
		this_char = getchar();
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
	printf("this char = %c\n", this_char);
	if ('(' == this_char) {
		eat('(');
		num = E();
		eat(')');
	}
	if (isdigit(this_char)) {
		ungetc(this_char, stdin);
		scanf("%d", &num);
		this_char = getchar();
	}
	printf("num = %d\n", num);
	return num;
}

int T_(int temp)
{
	int t = temp;
	while ('*' == this_char || '/' == this_char) {
		switch (this_char) {
		case '*':
			eat('*');
			t *= F();
			break;
		case '/':
			eat('/');
			t /= F();
			break;
		default:
			break;
		}
	}
	return t;
}

int T(void)
{
	int temp = 0;
	temp = F();
	temp = T_(temp);
	return temp;
}

int E_(int temp)
{
	int t = temp;
	while ('+' == this_char || '-' == this_char) {
		switch (this_char) {
		case '+':
			eat('+');
			t += T();
			break;
		case '-':
			eat('-');
			t -= T();
			break;
		default:
			break;
		}
	}
	return t;
}

int E(void)
{
	int temp = 0;
	temp = T();
	temp = E_(temp);
	return temp;
}

int S(void)
{
	return E();
}

int main()
{
	this_char = getchar();
	result = S();
	if ('\n' == this_char) {
	  printf("result = %d\n", result);
	}
	return 0;
}
