all: compile link

compile:
	g++ -c window.cpp

link:
	g++ window.o -o sfml-app.exe -lsfml-graphics -lsfml-window -lsfml-system

clear:
	rm *.o sfml-app.exe