# Description
Basic tower defense style game made using SFML library.

## Running code
1. Clone repository
   ```
   git clone https://github.com/adammierzwicki/OOP-Tower-Defense.git
   ```
2. Enter the directory and switch to branch extra
   ```
   cd OOP-Tower-Defense
   git checkout extra
   ```
3. (Linux only) Install required libraries
   ```
   sudo apt-get install cmake build-essential libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libgl1-mesa-dev libudev-dev libfreetype-dev libopenal-dev libvorbis-dev libflac-dev
   ```
4. Configure CMake:\
   On Linux
   ```
   cmake -B build
   ```
   On Windows
   ```
   cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -B build
   ```
5. Build project
   ```
   cmake --build build
   ```
6. Run `./build/bin/tower-defense`

## Running unit test
Unit tests are not currently supported on Windows!

To run unit tests use following command:
```
ctest --test-dir build/ut --output-on-failure
```

## Debugging
To truly check for all warnings during compilation append these flags:
```
-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror
```