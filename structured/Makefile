all: compile link

compile:
	cd /game/out -Wall
	g++ -c /game/src/*.cpp

link:
	g++ game/out/*.o -o ../../tower-defense.exe -Wall -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm game/out/*.o tower-defense.exe
