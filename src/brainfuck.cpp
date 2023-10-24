/**************************************************
*   PROJECT: Brainfuck interpreter written in C++
*   FILE:    Interpreter cpp file
*   AUTHOR:  Emil Olszewski
*   DATE:    22.10.2023
***************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cassert>
#include <map>
#include "brainfuck.h"
                                      // V - r/l corresponding bracker position


//* Load string to interpreter buffer
void loadInput(BFInterpreter* interpreter, std::string input) {
    interpreter->inputBuffer = input;
}


//* Load source file to interpreter buffer
int loadFileContent(BFInterpreter* interpreter, std::string path) {

    std::ifstream file(path);
    std::string   line;

    if (!file.is_open()) {
        std::cerr << "Failed to open the file at " << path;
        return 1;
    }

    while (std::getline(file, line)) {
        interpreter->inputBuffer += line + '\n';
    }

    return 0;
}

//* Advance to the next character in the buffer and read it
char advance(BFInterpreter* interpreter) {
    interpreter->currentChar = interpreter->inputBuffer[++interpreter->contentPointer];
    return interpreter->currentChar;
}


//* Perform lexycal analysis on loop brackets structure
void loopLexing(BFInterpreter* interpreter) {

    std::stack<int> leftBrackets;

    for (int i = 0; i < (int)interpreter->inputBuffer.length(); ++i) {
        char current = interpreter->inputBuffer[i];
        if (current == '[') {
            leftBrackets.push(i);
        } else if (current == ']') {
            ASSERT(!leftBrackets.empty());
            interpreter->bracketPairs[leftBrackets.top()] = i;
            interpreter->bracketPairs[i] = leftBrackets.top();
            leftBrackets.pop();
        } else {
            continue;
        }
    }
}

//* Parse current token and interpret it.
char performAction(BFInterpreter* interpreter) {


    switch (interpreter->currentChar)
    {
        case GT: // '>' - Increment pointer
            ASSERT(interpreter->memoryPointer < MEM_SIZE - 1);
            ++interpreter->memoryPointer;
            break;
        case LT: // '<' - Decrement pointer
            ASSERT(interpreter->memoryPointer > 0);
            --interpreter->memoryPointer;
            break;
        case PLUS: // '+' - Increment at current position
            ++interpreter->memory[interpreter->memoryPointer];
            break;
        case MINUS: // '-' - Decrement at current position
            --interpreter->memory[interpreter->memoryPointer];
            break;
        case DOT: // '.' - Display at current position
            std::putchar(interpreter->memory[interpreter->memoryPointer]);
            break;    
        case COMA: // ',' - Get char and put at current position
            interpreter->memory[interpreter->memoryPointer] = std::getchar();
            break;
        case LEFT_BRACKET: // '[' - Goto next ']' if at current position is 0
            if (!interpreter->memory[interpreter->memoryPointer]) {
                interpreter->contentPointer = interpreter->bracketPairs[interpreter->contentPointer];
            }
            break;
        case RIGHT_BRACKET: // ']' - Go back to the last '['
            interpreter->contentPointer = interpreter->bracketPairs[interpreter->contentPointer] - 1;
            break;
        default:
            break;
    }

    return advance(interpreter);
}

//* Run the interpreter post setup
void run(BFInterpreter* interpreter) {
    
    loopLexing(interpreter);

    advance(interpreter);
    while(interpreter->memoryPointer != (int)interpreter->inputBuffer.length()) {
        performAction(interpreter);
    }
}

//* Run the terminal input
void runTermInput(BFInterpreter* interpreter, std::string input) {

    loadInput(interpreter, input);
    run(interpreter);
}


//* Run the interpretation of the given file
//TODO: Implement REPL mode
void runFile(BFInterpreter* interpreter, std::string path) {

    loadFileContent(interpreter, path);
    run(interpreter);
    
}
