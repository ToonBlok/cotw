CPPFLAGS = -c -std=c++11 -Wall -pedantic
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES = Main.o Game.o Map.o Player.o Tile.o TextureManager.o Item.o MainMenu.o Button.o Console.o MainMenuState.h

cotw: $(OBJFILES)
	g++ $(OBJFILES) -o $@ $(SFMLFLAGS) $(UTFLAGS)

Main.o: Main.cpp 
	$(CC) $(CPPFLAGS) Main.cpp 

Game.o: Game.cpp 
	$(CC) $(CPPFLAGS) Game.cpp 

Map.o: Map.cpp 
	$(CC) $(CPPFLAGS) Map.cpp 

Player.o: Player.cpp 
	$(CC) $(CPPFLAGS) Player.cpp 

Tile.o: Tile.cpp 
	$(CC) $(CPPFLAGS) Tile.cpp 

TextureManager.o: TextureManager.cpp 
	$(CC) $(CPPFLAGS) TextureManager.cpp 

Item.o: items/Item.cpp 
	$(CC) $(CPPFLAGS) items/Item.cpp 

Console.o: screens/Console.cpp
	$(CC) $(CPPFLAGS) screens/Console.cpp

MainMenu.o: screens/MainMenu.cpp
	$(CC) $(CPPFLAGS) screens/MainMenu.cpp

Button.o: screens/Button.cpp
	$(CC) $(CPPFLAGS) screens/Button.cpp

MainMenuState.o: MainMenuState.cpp
	$(CC) $(CPPFLAGS) MainMenuState.cpp


clean:
	rm *.o cotw 
