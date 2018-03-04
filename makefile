myprogram: main.o game.o player.o tile.o
	g++ main.o game.o player.o tile.o -o game  -lsfml-graphics -lsfml-window -lsfml-system
	
main.o: main.cpp 
	g++ -c -std=c++11 main.cpp 

game.o: game.cpp 
	g++ -c -std=c++11 game.cpp 

player.o: player.cpp 
	g++ -c -std=c++11 player.cpp 

tile.o: tile.cpp 
	g++ -c -std=c++11 tile.cpp 

clean:
	rm *.o game 
