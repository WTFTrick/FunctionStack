all:
	gcc stack.c -o stack

preprocessor:
	gcc -E stack.c > preprocessor.log
