# Description
Basic tower defense style game made using SFML library.

### Warning
$\textsf{\color{red}Code is not working with SFML 3.0.0!}$ \
For best experience use SFML 2.6.2 (native version) but in general versions 2.5.X / 2.6.X should also work fine.

## Running code
### Linux
1. Install `libsfml-dev`.
2. Configure CMake build:
   ```
   cmake -B build
   ```
3. Build code:
   ```
   cmake --build build
   ```
4. Run `./build/game/tower_defense`
   
### Linux (without CMake)
1. Install `libsfml-dev`.
2. Run `make` command.
3. Run `./tower_defense`

### Linux (using terminal)
1. Install `libsfml-dev`.
2. Compile and link code:
   ```
   cd ./game/obj
   g++ -c ./../src/*.cpp -Wall
   cd ./../..
   g++ ./game/obj/*.o -o tower_defense.exe -lsfml-graphics -lsfml-window -lsfml-system
   ```
3. Run `./tower_defense.exe`

### Windows
<span style="color:red">`to be added`</span>

### Windows (without CMake)
1. Install SFML in `external/` folder.
2. Copy all `.dll` files from `external/PATH_TO_SFML/bin` into working directory.
3. Compile and link code: 
   ```
   cd .\game\obj
   g++ -c .\..\src\*.cpp -I .\..\..\external\PATH_TO_SFML\include -Wall
   cd .\..\..
   g++ .\game\obj\*.o -o tower-defense.exe  -L .\external\PATH_TO_SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
   ```
4. Run `.\tower_defense.exe`.

## Running unit test
To run unit tests use following command:
```
ctest --test-dir build/ut --output-on-failure
```

## Debugging
To truly check for all warnings during compilation append these flags: \
```
-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror
```