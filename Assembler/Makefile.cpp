CC = g++
CFLAGS = -Wall -pedantic -Wextra

compile: Assembler.cpp
	${CC} -o Assembler ${CFLAGS} Assembler.cpp

run:
	./Assembler

clean:
	rm -f Assembler
