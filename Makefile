CC = g++
OBJS = Store.o

MB: main.cpp Store.o
	${CC} main.cpp ${OBJS} -o MB

Store.o: Store.cpp Store.h 
	${CC} -c Store.cpp 

run:
	./MB
clean:
	rm -f MB ${OBJS}