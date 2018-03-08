myprogram: main.o game.o player.o tile.o texture_manager.o
	g++ main.o game.o player.o tile.o texture_manager.o -o game  -lsfml-graphics -lsfml-window -lsfml-system
	
main.o: main.cpp 
	g++ -c -std=c++11 main.cpp 

game.o: game.cpp 
	g++ -c -std=c++11 game.cpp 

player.o: player.cpp 
	g++ -c -std=c++11 player.cpp 

tile.o: tile.cpp 
	g++ -c -std=c++11 tile.cpp 

texture_manager.o: texture_manager.cpp 
	g++ -c -std=c++11 texture_manager.cpp 

clean:
	rm *.o game 
