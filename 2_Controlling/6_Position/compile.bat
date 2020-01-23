i686-w64-mingw32-g++ -O3 -shared -static -std=c++17 -Wall -Wextra ai.cpp -o ai.dll & REM 2> errors.txt
strip --strip-unneeded ai.dll
pause
