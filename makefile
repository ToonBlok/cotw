CPPFLAGS = -c -std=c++11
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES = main.o game.o map.o player.o tile.o texture_manager.o

cotw: $(OBJFILES)
	g++ $(OBJFILES) -o $@ $(SFMLFLAGS) $(UTFLAGS)

main.o: main.cpp 
	$(CC) $(CPPFLAGS) main.cpp 

game.o: game.cpp 
	$(CC) $(CPPFLAGS) game.cpp 

map.o: map.cpp 
	$(CC) $(CPPFLAGS) map.cpp 

player.o: player.cpp 
	$(CC) $(CPPFLAGS) player.cpp 

tile.o: tile.cpp 
	$(CC) $(CPPFLAGS) tile.cpp 

texture_manager.o: texture_manager.cpp 
	$(CC) $(CPPFLAGS) texture_manager.cpp 

clean:
	rm *.o cotw 
