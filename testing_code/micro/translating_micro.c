void check_id(string s)
{
	if (!lookup(s)) {
		enter(s);
		generate("Declare", s, "Integer", "");
	}
}
