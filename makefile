.ONESHELL:

dump:
	clang ./examples/example1.c -o example1.s -s
	objdump example1.s --disassemble > example1.dump

example1:
	clang ./examples/example1.c -o example1 -g
	
example2:
	clang ./examples/example2.c -o example2 -g

clean:
	rm -f example1.s example1.dump example1 example2