#!/bin/bash

# Compile all source files into an executable named 'program'
g++ -std=c++17 -o program entry.cpp evaluator.cpp exprtreenode.cpp main.cpp symtable.cpp ulimitedint.cpp ulimitedrational.cpp

# Run the compiled program
./program

# Remove the executable after running
rm program
