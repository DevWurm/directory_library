ifeq	($(OS),Windows_NT)
all:
	mkdir Binary
	g++ .\Source\classes.cpp -std=c++11 -c -o .\Binary\directory_windows.o
	mkdir lib
	copy .\Headers\classes.h .\lib\libdirectory.h
	copy .\Headers\liberror.h .\lib\liberror.h
	ar rs .\lib\libdirectory_windows.a .\Binary\directory_windows.o .\error_lib\error.o
	ranlib  .\lib\libdirectory_windows.a
else	
all:	source
	cp ./liberror/liberror.h ./lib/
	cp ./Headers/classes.h ./lib/
	mv ./lib/classes.h ./lib/libdirectory.h
	ar rs ./lib/libdirectory.a ./Binary/directory.o ./liberror/error.o

source:	
	./prepare_directory.sh
	g++ ./Source/classes.cpp -std=c++11 -c -o ./Binary/directory.o
endif

