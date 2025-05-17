.PHONY: install clean

program: brainfuck.o
	gcc -o brainfuck brainfuck.o

brainfuck.o: brainfuck.c output.h parser.h
	gcc -c brainfuck.c

install: brainfuck
	cp brainfuck /usr/local/bin/
	chmod +x /usr/local/bin/brainfuck

clean: 
	rm -f brainfuck.o brainfuck