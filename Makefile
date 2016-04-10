CC=g++
CXX_FLAGS=-std=c++0x

t5: pgm.o t5.cpp
	$(CC) $(CXX_FLAGS) pgm.o t5.cpp -o t5

pgm.o: pgm.h pgm.cpp
	$(CC) $(CXX_FLAGS) -c pgm.cpp
