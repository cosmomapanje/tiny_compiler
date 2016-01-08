#define MAXIDLEN 33

typedef char string[MAXIDLEN];

typedef struct operator {
	enum op {PLUS, MINUS} operator;
} op_rec;

/* expression types */
enum expr {INEXPR, LITERALEXPR, TEMPEXPR};

/* for <primary> and <expression> */
typedef struct expression {
	enum expr kind;
	union {
		string name; /* for IDEXPR, TEMPEXPR */
		int val; /*for LITERALEXPR */
	};
} expr_rec;
