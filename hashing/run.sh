#!/bin/bash

# Build the C++ program
make

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Loop through numbers 0 to 9 and pass each as a filename to the program
    for i in {0..6}; do
        echo "Running program for file random_text$i.txt"
        ./build/main "random_text$i.txt"
    done
else
    echo "Compilation failed. Program cannot be run."
fi
