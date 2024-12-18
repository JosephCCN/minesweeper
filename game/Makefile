flags = -std=c++11
objects = kernel.o player.o game.o

all: $(objects)
	g++ $(objects) $(flags) -o run
kernel.o: kernel.cpp
	g++ $(flags) -c kernel.cpp
player.o: player.cpp player.h
	g++ $(flags) -c player.cpp
game.o: game.cpp game.h
	g++ $(flags) -c game.cpp
clean:
	rm run $(objects)