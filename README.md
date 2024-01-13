# Brainfuc++ - The C++ Brainfuck interpreter

## About Brainfuck 
[Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) is an esoteric programming language developed by Urban Muller. It's simple yet [Turing complete](https://en.wikipedia.org/wiki/Turing_completeness) which makes it perfect choice for writing simple interpreter. Brainfuck's syntax is a set of only few instructions i.e. `<>+-.,[]` while everything else is treated as a comment. The way it works is analogous to the [Turing machine](https://en.wikipedia.org/wiki/Turing_machine). 

## Build
Run `make` in your terminal. Make will build the project to `.\target\` directory. To alter this behaviour change `BUILDTARGET` in `Makefile`.

## Usage
To interpret brainfuck file run: 

`.\target\brainfuck.exe .\path\to\source\file`

You can also interpret input directly: 

`.\target\brainfuck.exe -term "brainfuckinput"`

## Dependencies 
- [GNU Make](https://www.gnu.org/software/make/)
- [gcc](https://www.gnu.org/software/gcc/)