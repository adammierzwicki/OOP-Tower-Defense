all: compile link

compile:
	cd ./game/obj && g++ -c ./../src/*.cpp -Wall

link:
	g++ ./game/obj/*.o -o tower_defense.exe -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm game/out/*.o tower-defense.exe
