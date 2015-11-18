
#define TOTAL_KEYWORDS 32
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 8
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 42 

#ifndef HASH_FUNC
#define HASH_FUNC hash_ckeyword

static const char * const wordlist[MAX_HASH_VALUE] =
{
	"",
	"return",
	"struct",
	"if",
	"int",
	"unsigned",
	"switch",
	"short",
	"union",
	"static",
	"continue",
	"const",
	"auto",
	"extern",
	"else",
	"char",
	"for",
	"case",
	"signed",
	"register",
	"do",
	"volatile",
	"goto",
	"void",
	"break",
	"sizeof",
	"while",
	"float",
	"typedef",
	"enum",
	"",
	"long",
	"double",
	"", "", "", "", "", "", "", "", "",
	"default"
};

static const unsigned char alphabet_value_for_ckeyword[] =
{
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43,  6, 12,  9,
	20,  6, 16, 16, 43,  3, 43, 43, 15, 23,
	0,  5, 21, 43,  0,  2,  1,  0,  0,  8,
	43, 43, 17, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
	43, 43, 43, 43, 43, 43
};

static unsigned int hash_ckeyword(const char *str, unsigned int len)
{
	register int hval = 0;
	switch (len) {
	default:
		hval += alphabet_value_for_ckeyword[(unsigned char)str[3]];
		/*FALLTHROUGH*/
	case 3:
		hval += alphabet_value_for_ckeyword[(unsigned char)str[2]];
		/*FALLTHROUGH*/
	case 2:
	case 1:
		hval += alphabet_value_for_ckeyword[(unsigned char)str[0]];
		break;
	}
	return hval;
}

const char * is_key_word(const char *str, unsigned int len)
{ 
	if(len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH) {
		register int key = HASH_FUNC(str, len);

		if (key <= MAX_HASH_VALUE && key >= 0) {
			register const char *s = wordlist[key];
			if (*str == *s && !strcmp (str + 1, s + 1)) {
				return s;
			}
		}
	}
	return 0;
}

#ifdef DEBUG_HASH
int main(int argc, char **argv)
{
	int i = 0;
	for (;i < MAX_HASH_VALUE; i++) {
		printf("%s == %d\n", wordlist[i], HASH_FUNC(wordlist[i], strlen(wordlist[i])));
	}
	return 0;
}
#endif
#endif
