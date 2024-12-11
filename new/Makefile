all: compile link

compile:
	g++ -c ./main.cpp ./game.cpp ./windowHandler.cpp ./enemy.cpp

link:
	g++ ./main.o ./game.o ./windowHandler.o ./enemy.o -o tower-defense.exe -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm *.o tower-defense.exe