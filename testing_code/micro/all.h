typedef enum token_types {
  BEGIN, ENG, READ, WRITE, ID, INTLITERAL, LPAREN, RPAREN, SEMICOLON,
  COMMA, ASSIGNOP, PLUSOP, MINUSOP, SCANEOF
} token;

extern token scanner(void);
