.ONESHELL:

dump:
	clang example.c -o example.s -s
	objdump example.s --disassemble > example.dump

debug:
	clang main.c -o main -g
	
example:
	clang example.c -o example -g

clean:

	rm example main 