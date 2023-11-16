.ONESHELL:

dump:
	clang main.c -o main.s -s
	objdump main.s --disassemble > main.dump

debug:
	clang main.c -o main -g
	