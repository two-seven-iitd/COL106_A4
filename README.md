# Rational Expression Evaluator

This project implements a rational expression evaluator in C++ that supports operations on unlimited-sized rational numbers using custom data types. It reads expressions, builds expression trees, and evaluates them accurately using arbitrary-precision arithmetic.

## 🔧 Build & Run

Use the following commands to compile and run the program:

```bash
g++ -std=c++17 -o program entry.cpp evaluator.cpp exprtreenode.cpp main.cpp symtable.cpp ulimitedint.cpp ulimitedrational.cpp
./program
rm program
```

Alternatively, you can use the provided `run.sh` script:

```bash
chmod +x run.sh
./run.sh
```

## ✅ Expected Output

When `main.cpp` is executed, the output should be:

```
x = 8/1
y = 16/1
z = 6/1
a = 72/5
b = -21/1
c = 49/1
```

## 📁 File Overview

- `ulimitedint.cpp` / `ulimitedint.h` — Arbitrary-length integer support
- `ulimitedrational.cpp` / `ulimitedrational.h` — Rational number class built using `UnlimitedInt`
- `exprtreenode.cpp` — Expression tree node structure
- `evaluator.cpp` — Expression tree parser and evaluator
- `symtable.cpp` — Symbol table for variable storage
- `main.cpp` — Driver code to test the evaluator
- `entry.cpp` — Input/output or parsing entry logic
- `run.sh` — Script to compile, run, and clean the program

## 📌 Notes

- Requires a C++17-compatible compiler
- Tested on Linux (g++ 11+)
