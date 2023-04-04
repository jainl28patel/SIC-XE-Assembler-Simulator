CFLAGS += -w
assembler: assembler.o
	g++ -std=c++11 -w -o assembler assembler.cpp
	./assembler