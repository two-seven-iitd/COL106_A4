
# 🧮 Rational Expression Evaluator with Arbitrary Precision

This project is a C++ implementation of a **Rational Expression Evaluator** that parses and evaluates expressions involving **arbitrary-size rational numbers**. It includes a custom `UnlimitedInt` class for handling big integers, a `UnlimitedRational` class for rational arithmetic, an **Expression Tree** for structured evaluation, and a **Binary Search Tree (BST)**-based symbol table for variable storage.

---

## 📁 File Structure and Roles

```
.
├── entry.cpp                # Main driver to read, parse and pass expressions for evaluation
├── evaluator.cpp            # Builds and evaluates the expression tree
├── exprtreenode.cpp         # Defines the structure of the expression tree nodes
├── main.cpp                 # Test cases and execution logic for the evaluator
├── symtable.cpp             # Symbol table implemented using a Binary Search Tree (BST)
├── ulimitedint.cpp          # Class for arbitrary-precision integers
├── ulimitedrational.cpp     # Rational number class built using UnlimitedInt
├── run.sh                   # Script to compile, run, and clean the project
```

---

## 🔧 Components Used

### 🧠 Expression Tree
- Built using `ExprTreeNode`.
- Each node stores either an operator (`+`, `-`, `*`, `/`, `=`) or a rational number / variable.
- Recursively evaluated in `Evaluator`.

### 🧮 UnlimitedInt
- Handles **arbitrary-sized integers**.
- Internally stores digits as dynamic arrays or vectors.
- Supports all basic arithmetic and comparison operators.

### 🔢 UnlimitedRational
- Represents a rational number as a fraction: numerator / denominator (`UnlimitedInt`).
- Automatically simplifies the result.
- Supports arithmetic and comparison operators.

### 🌳 Symbol Table (BST)
- Implemented in `symtable.cpp` as a Binary Search Tree.
- Stores variables and their assigned rational values.
- Supports insertion, lookup, and update in logarithmic time.

---

## 🚀 How to Build and Run

You can build and run the project using either manual commands or the provided shell script.

### Option 1: Manual Commands

```bash
g++ -std=c++17 -o program entry.cpp evaluator.cpp exprtreenode.cpp main.cpp symtable.cpp ulimitedint.cpp ulimitedrational.cpp
./program
rm program
```

### Option 2: Using run.sh

```bash
chmod +x run.sh
./run.sh
```

---

## ✅ Expected Output

When you run `main.cpp`, you should see:

```
x = 8/1
y = 16/1
z = 6/1
a = 72/5
b = -21/1
c = 49/1
```

---

## 📄 Description of Each File

### `main.cpp`
- Contains hardcoded test expressions.
- Calls the evaluator for each input.
- Prints the result of expression evaluation.

### `entry.cpp`
- Acts as a bridge between input handling and evaluation.
- Parses expressions, initializes evaluator, and controls flow.

### `evaluator.cpp`
- Parses expressions into a tree (`ExprTreeNode`).
- Evaluates expression trees recursively.
- Handles variable assignment and retrieval via symbol table.

### `exprtreenode.cpp`
- Defines the `ExprTreeNode` class.
- Stores value, operator, left/right child.
- Used to construct the parse tree for each expression.

### `symtable.cpp`
- Implements the symbol table using a **Binary Search Tree**.
- Each node stores a variable name and its `UnlimitedRational` value.
- Allows quick lookup, insertion, and modification.

### `ulimitedint.cpp`
- Defines the `UnlimitedInt` class for big integer arithmetic.
- Internally manages digits to avoid overflow.
- Supports addition, subtraction, multiplication, division, comparisons.

### `ulimitedrational.cpp`
- Implements the `UnlimitedRational` class.
- Each rational is stored as numerator and denominator (`UnlimitedInt`).
- Handles rational simplification using GCD.

### `run.sh`
- A helper script to:
  - Compile all files
  - Run the executable
  - Remove it after execution

---

## 💡 Key Features

- 📐 **Expression Tree Parsing** for accurate evaluation  
- 🧮 **Big Integer and Rational Arithmetic** (custom-built, no third-party libraries)  
- 🧾 **Symbol Table via Binary Search Tree** for storing/retrieving variables  
- 🧹 **Automatic Simplification** of rational expressions  
- ⚙️ **C++17 Standard**, cross-platform compilation  

---

## 📌 Requirements

- C++17 compatible compiler (e.g., `g++ 9+`)  
- Linux or compatible terminal (tested on Ubuntu)  
- Basic understanding of expression parsing and rational arithmetic  

---

## 🔬 Possible Extensions

- Support for parentheses and operator precedence  
- Floating-point mode for approximate calculations  
- Saving expressions and outputs to file  
- GUI or command-line calculator front-end  

---

## 👨‍💻 Author

**Ankit Kumar (2023AM10185)**  
Project for **COL106: Data Structures & Algorithms 23'Odd Sem Assignment**, IIT Delhi
