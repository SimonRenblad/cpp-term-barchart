# cpp-term-barchart
Single-header library for adding barcharts in your ncurses terminal application. Uses C++11 and compiled latest on MacOS. Requires unicode support. 

## Example 
![](/example1.png)

## Get Started

To use, you must:

1. Copy the header file to your directory.
2. Include it at the top of your file, with an additional library:
```c++
#include "barchart.h"
#include <locale.h>
```
3. Before any call to ncurses, include the following line in your code:
```c++
setlocale(LC_ALL, "");
```

## Compile the example code

This repository contains an additional `example.cpp` and `Makefile` to make it easier to understand. 

Assuming you have `g++` installed, simply call:
```shell
make
```
in your local repo.
