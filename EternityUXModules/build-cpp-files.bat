@echo off
color 4
echo Building %1...
windres Assets\resource.rc -o resource.o
g++ -I../include %i -o %.exe
color 3
echo Hit "Enter" to try testing the build!
pause >nul 2>&1
%1.exe --test
color
del resource.o >nul 2>&1
del 0 >nul 2>&1