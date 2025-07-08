#!/bin/bash

echo "Running SmartStudent System..."

# Check if executable exists
if [ ! -f "./SmartStudent" ]; then
    echo "SmartStudent executable not found!"
    echo "Please build the project first using: ./build.sh"
    exit 1
fi

# Run the program
./SmartStudent
