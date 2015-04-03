all: source
	mkdir lib
	cp ./Headers/classes.h ./lib/
	mv ./lib/classes.h ./lib/libdirectory.h
	ar rs ./lib/libdirectory.a ./Binary/directory.o

source:
	mkdir Binary
	g++ ./Source/classes.cpp -std=c++11 -c -o ./Binary/directory.o
