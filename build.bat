@echo off
echo Building SmartStudent System...

REM Compile with g++
echo.
echo Compiling with g++...
g++ -std=c++11 -Wall -Wextra -o SmartStudent.exe main.cpp StudentList.cpp ServiceQueue.cpp TransactionStack.cpp StudentHashTable.cpp BST.cpp ProdiGraph.cpp StudentSorter.cpp

if %errorlevel% neq 0 (
    echo Error compiling with g++!
    echo Make sure you have g++ installed and in your PATH
    pause
    exit /b 1
)

echo.
echo Build successful!
echo SmartStudent.exe is ready to run.
echo.
echo To run the program, use: SmartStudent.exe
echo Or use: run.bat
echo.
pause
