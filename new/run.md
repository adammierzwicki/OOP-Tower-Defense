# Compile
`g++ -c .\main.cpp .\game.cpp .\windowHandler.cpp .\enemy.cpp -I"B:\Politechnika\SFML project\SFML-2.6.2\include"`

# Link
`g++ .\main.o .\game.o .\windowHandler.o .\enemy.o -o tower-defense.exe -L"B:\Politechnika\SFML project\SFML-2.6.2\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main`
