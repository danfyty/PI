CC=g++
CXX_FLAGS=-std=c++0x
FLAGS=$(CXX_FLAGS) -O2

t5: pgm.o filters.o t5.cpp
	$(CC) $(FLAGS) pgm.o filters.o t5.cpp -o t5

pgm.o: pgm.h pgm.cpp
	$(CC) $(FLAGS) -c pgm.cpp

filters.o: filters.cpp filters.h pgm.o
	$(CC) $(FLAGS) -c filters.cpp

.PHONY: clean

clean:
	rm *.o t5
