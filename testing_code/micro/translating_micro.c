
void check_id(string s)
{
	if (!lookup(s)) {
		enter(s);
		generate("Declare", s, "Integer", "");
	}
}

char *get_temp(void)
{
	/* max temporary allocated so far */
	static int max_temp = 0;
	static char tempname[MAXIDLEN];

	max_temp++;
	sprintf(tempname, "Temp&%d", max_temp);
	check_id(tempname);
	return tempname;
}

void start(void)
{
	/* Semantic initializations, none needed. */
}

void finish(void)
{
	/* Generate code to finish program */
	generate("Halt", "", "", "");
}

void assign(expr_rec target, expr_rec source)
{
	/* Generate code for assignment */
	generate("Store", extract(source), target.name, "");
}

op_rec process_op(void)
{
	/* Produce operator descriptor */
	op_rec o;
	if (current_token == PLUSOP) {
		o.operator = PLUS;
	} else {
		o.operator = MINUS;
	}
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2)
{
	expr_rec e_rec;
	/* An expr_rec with temp variant set. */
	e_rec.kind = TEMPEXPR;
	
	/*
	 * Generate code for infix operation.
	 * Get result temp and set up semantic record
	 * for result.
	 */
	strcpy(erec.name, get_temp());
	generate(extract(op), extract(e1), extract(e2), erec.name);

	return erec;
}


void read_id(expr_rec in_var)
{
	/* generate code for read */
	generate("Read", in_var.name, "Integer", "");
}

expr_rec process_id(void)
{
	expr_rec t;

	/*
	 * Declare ID and build a Corresponding semantic record
	 */
	check_id(token_buffer);
	t.kind = IDEXPR;
	strcpy(t.name, token_buffer);

	return t;
}

expr_rec process_literal(void)
{
	expr_rec t;
	
	/*
	 * Convert literal to a numeric repressentation
	 * and build semantic record.
	 */
	t.kind = LITERALEXPR;
	(void) sscanf(token_buffer, "%d", &t.val);

	return t;
}

void write_expr(expr_rec out_expr)
{
	generate("Write", extract(out_expr), "Integer", "");
}

void expression(expr_rec *result)
{
	expr_rec left_operand, right_operand;
	op_rec op;

	primary(&left_operand);
	while (next_token() == PLUSOP || next_token() == MINUSOP) {
		add_op(&op);
		primary(&right_operand);
		left_operand = gen_infix(left_operand, op, right_operand);
	}
	*result = left_operand;
}
