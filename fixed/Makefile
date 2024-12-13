all: compile link

compile:
	g++ -c *.cpp

link:
	g++ *.o -o tower-defense.exe -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm *.o tower-defense.exe