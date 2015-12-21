# tiny_compiler - a tiny compiler for c (it's not ISO-C or GNU C, it's decreased some complex grammer stuff)
# See LICENSE file for copyright and license details.

SRC = lexical_parser.c symbol_table.c test_code.c
OBJ = ${SRC:.c=.o}

all: options tiny_compiler testing_code

options:
	@echo tiny_compiler build options

tiny_compiler:
	@echo CC -o $@
	@${CC} -o $@ ${SRC}

clean:
	@echo cleaning
	@rm -rf tiny_compiler
	@cd testing_code; make clean; cd -

dist: clean
	@echo creating dist tarball

install: all
	@echo do nothing

uninstall:
	@echo do nothing

testing_code:
	@cd testing_code; make; cd ../

.PHONY: all options clean dist install uninstall testing_code
