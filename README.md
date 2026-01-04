# Lexical Analyzer (C++)

## Overview

This project implements a simple lexical analyzer written in C++ using regular expressions. The analyzer reads an input source file (`program.txt`) and identifies basic lexical elements, including identifiers, keywords, numbers, strings, operators, separators, constants, whitespace, and lexical errors.

The project is designed for academic purposes, particularly for introductory compiler or programming languages courses.

## Features

* Identification and counting of lexical tokens:

  * Identifiers
  * Keywords
  * Numbers
  * String literals
  * Arithmetic operators
  * Logical operators
  * Separators
  * Constants
  * Whitespace
* Removal of comments before analysis
* Detection of unrecognized or invalid input segments (lexical errors)
* Platform-independent file handling suitable for GitHub repositories

## Input File

The analyzer processes a text file named `program.txt` that contains sample source code. The file path can be:

* Provided by the user at runtime, or
* Passed as a command-line argument, or
* Placed in the same directory as the executable (relative path)

This design avoids hard-coded absolute paths and ensures portability across systems.

## Compilation and Execution

Compile the program using a C++ compiler such as `g++`:

```
g++ lexer.cpp -o lexer
```

Run the program:

```
./lexer
```

Or specify a custom input file path:

```
./lexer path/to/program.txt
```

## Output

The program prints a summary of token counts and reports any detected lexical errors to the standard output.

## Notes

This project focuses on lexical analysis only and does not perform syntax or semantic analysis.

## Author

Aylin Dourandish
