#!/bin/bash

# Build script for Linux with proper C++ standard
g++ -std=c++14 -Wall -Wextra -O2 -o main main.cpp

if [ $? -eq 0 ]; then
    echo "Build successful! Executable: main"
else
    echo "Build failed!"
    exit 1
fi
