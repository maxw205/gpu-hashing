#!/bin/bash

# Build the C++ program
make

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the program
    ./build/main
else
    echo "Compilation failed. Program cannot be run."
fi
