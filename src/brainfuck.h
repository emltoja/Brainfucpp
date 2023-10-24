/**************************************************
*   PROJECT: Brainfuck interpreter written in C++
*   FILE:    Brainfuck interpreter header file
*   AUTHOR:  Emil Olszewski
*   DATE:    22.10.2023
***************************************************/


#pragma once

#ifndef BF_INTERPRETER
#define BF_INTERPRETER


#include <string>
#include <cassert>
#include <map>


#ifndef ASSERT
//* Capital assert for better visibility
#define ASSERT(expr) assert(expr)
#endif //ASSERT

#ifndef MEM_SIZE
//* Brainfuck tape size
#define MEM_SIZE 30000
#endif //MEM_SIZE

//* Interpreter struct
struct BFInterpreter {
    char               memory[MEM_SIZE] = {0};
    char               currentChar = 0;
    int                memoryPointer = 0;
    std::string        inputBuffer;
    int                contentPointer = -1;
    std::map<int, int> bracketPairs;            // K - l/r bracket position 
};                                              // V - r/l corresponding bracker position


//* BF tokens enum

#define  LT            '>'   // ">" - Increment pointer 
#define  GT            '<'   // "<" - Decrement pointer 
#define  PLUS          '+'   // "+" - Increment value 
#define  MINUS         '-'   // "-" - Decrement value 
#define  DOT           '.'   // "." - Display value  
#define  COMA          ','   // "," - Write value  
#define  LEFT_BRACKET  '['   // "[" - Go to next ']' if value == 0
#define  RIGHT_BRACKET ']'   // "]" - Go back to the last '['


//* Load string to interpreter buffer
void loadInput(BFInterpreter* interpreter, std::string input);

//* Load source file to interpreter buffer
int loadFileContent(BFInterpreter* interpreter, std::string path);

//* Advance to the next character in the buffer and read it
char advance(BFInterpreter* interpreter);

//* Perform lexical analysis on loop brackets structure
void loopLexing(BFInterpreter* interpreter);

//* Parse current token and interpret it
char performAction(BFInterpreter* interpreter);

//* Run the interpretation of given input
void runFile(BFInterpreter* interpreter, std::string path);

//* Run the terminal input
void runTermInput(BFInterpreter* interpreter, std::string input);

//* Run the interpreter post setup
void run(BFInterpreter* interpreter);


#endif //BF_INTERPRETER