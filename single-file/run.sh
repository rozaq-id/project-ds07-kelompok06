#!/bin/bash

echo "Running Single-File SmartStudent System..."

# Check if executable exists
if [ ! -f "./SmartStudent-SingleFile" ]; then
    echo "SmartStudent-SingleFile executable not found!"
    echo "Please build the project first using: ./build.sh"
    exit 1
fi

# Run the program
./SmartStudent-SingleFile
