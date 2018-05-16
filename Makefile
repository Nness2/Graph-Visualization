exec: affichage.o visu.o main.o
	g++ -o exec -std=c++14 visu.o affichage.o main.o `sdl-config --libs`

affichage.o: affichage.cpp
	g++ -o affichage.o -c affichage.cpp -std=c++14

visu.o: visu.cpp
	g++ -o visu.o -c visu.cpp -std=c++14

main.o: main.cpp 
	g++ -o main.o -c main.cpp -std=c++14


clean:
	rm *.o 
	
