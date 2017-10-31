CC = g++
OBJS = Store.o Operation.o

MB: main.cpp ${OBJS}
	${CC} main.cpp ${OBJS} -o MB

Store.o: Store.cpp Store.h 
	${CC} -c Store.cpp 

Operation.o: Operation.cpp Operation.h
	${CC} -c Operation.cpp

run:
	./MB
clean:
	rm -f MB ${OBJS}