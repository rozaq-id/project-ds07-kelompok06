#!/bin/bash

echo "Building Single-File SmartStudent System for Linux..."

# Check if g++ is installed
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ is not installed!"
    echo "Please install g++ using your package manager:"
    echo "Ubuntu/Debian: sudo apt-get install g++"
    echo "CentOS/RHEL: sudo yum install gcc-c++"
    echo "Fedora: sudo dnf install gcc-c++"
    exit 1
fi

echo
echo "Compiling with g++..."
g++ -std=c++11 -Wall -Wextra -o SmartStudent-SingleFile main.cpp

if [ $? -ne 0 ]; then
    echo "Error compiling with g++!"
    exit 1
fi

echo
echo "Build successful!"
echo "SmartStudent-SingleFile is ready to run."
echo
echo "To run the program, use: ./SmartStudent-SingleFile"
echo

# Make the executable file executable
chmod +x SmartStudent-SingleFile
