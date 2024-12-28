all: compile link

compile:
	cd game/out && g++ -c ../src/*.cpp -Wall

link:
	g++ game/out/*.o -o tower-defense.exe -Wall -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm game/out/*.o tower-defense.exe
