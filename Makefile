frac:	main.o Pieza.cpp
	g++ -std=c++11 main.o Pieza.cpp -lncurses
main.o:	main.cpp
	g++ -c main.cpp
