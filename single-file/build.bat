@echo off
echo Building Single-File SmartStudent System...

echo.
echo Compiling with g++...
g++ -std=c++11 -Wall -Wextra -o SmartStudent-SingleFile.exe main.cpp

if %errorlevel% neq 0 (
    echo Error compiling with g++!
    echo Make sure you have g++ installed and in your PATH
    pause
    exit /b 1
)

echo.
echo Build successful!
echo SmartStudent-SingleFile.exe is ready to run.
echo.
echo To run the program, use: SmartStudent-SingleFile.exe
echo.
pause
