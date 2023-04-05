
tic: main.o tic.o
	g++ main.o tic.o -o tic

main.o: main.cpp
	g++ -c main.cpp

tic.o: tic.cpp tic.hpp
	g++ -c tic.cpp

clean:
	del *.o tic