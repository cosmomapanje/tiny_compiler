#testing code for tiny compiler

all:
	@gcc recursive_descent_if.c -o recursive_descent_if
	@gcc recursive_descent_calc.c -o recursive_descent_calc
	@gcc recursive_descent_calc_with_parsing_table.c -o recursive_descent_calc_with_parsing_table
	@cd micro; make; cd ..
clean:
	@rm -rf recursive_descent_if recursive_descent_calc recursive_descent_calc_with_parsing_table
	@cd micro; make clean; cd ..
