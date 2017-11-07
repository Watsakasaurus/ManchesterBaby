CC = g++
OBJS = Store.o Operation.o

ManchesterBaby: main.cpp ${OBJS}
	${CC} main.cpp ${OBJS} -o ManchesterBaby

Store.o: Store.cpp Store.h 
	${CC} -c Store.cpp 

Operation.o: Operation.cpp Operation.h
	${CC} -c Operation.cpp

run:
	./ManchesterBaby
clean:
	rm -f ManchesterBaby ${OBJS}