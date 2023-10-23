/**************************************************
*   PROJECT: Brainfuck interpreter written in C++
*   AUTHOR:  Emil Olszewski
*   DATE:    22.10.2023
***************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cassert>
#include <map>

//* Capital assert for better visibility
#define ASSERT(expr) assert(expr)
//* Brainfuck tape size
#define MEM_SIZE 30000


//* interpreter struct
struct BFInterpreter {
    char               memory[MEM_SIZE] = {0};
    char               currentChar = 0;
    int                memoryPointer = 0;
    std::string        fileContents;
    int                contentPointer = -1;
    std::map<int, int> bracketPairs;            // K - l/r bracket position 
};                                              // V - r/l corresponding bracker position


//* Load source file to interpreter buffer
int loadFileContents(BFInterpreter* interpreter, std::string path) {

    std::ifstream file(path);
    std::string   line;

    if (!file.is_open()) {
        std::cerr << "Failed to open the file at " << path;
        return 1;
    }

    while (std::getline(file, line)) {
        interpreter->fileContents += line + '\n';
    }

    return 0;
}

//* Advance to the next character in the buffer and read it
char advance(BFInterpreter* interpreter) {
    interpreter->contentPointer++;
    interpreter->currentChar = interpreter->fileContents[interpreter->contentPointer];
    return interpreter->currentChar;
}


//* Perform lexycal analysis on loop brackets structure
void loopLexing(BFInterpreter* interpreter) {

    std::stack<int> leftBrackets;

    for (int i = 0; i < (int)interpreter->fileContents.length(); ++i) {
        char current = interpreter->fileContents[i];
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
        case '>': // > - Increment pointer
            ASSERT(interpreter->memoryPointer < MEM_SIZE - 1);
            ++interpreter->memoryPointer;
            break;
        case '<': // < - Decrement pointer
            ASSERT(interpreter->memoryPointer > 0);
            --interpreter->memoryPointer;
            break;
        case '+': // + - Increment at current position
            ++interpreter->memory[interpreter->memoryPointer];
            break;
        case '-': // - - Decrement at current position
            --interpreter->memory[interpreter->memoryPointer];
            break;
        case '.': // . - Display at current position
            std::putchar(interpreter->memory[interpreter->memoryPointer]);
            break;    
        case ',': // , - Get char and put at current position
            interpreter->memory[interpreter->memoryPointer] = std::getchar();
            break;
        case '[': // [ - Goto next ']' if at current position is 0
            if (!interpreter->memory[interpreter->memoryPointer]) {
                interpreter->contentPointer = interpreter->bracketPairs[interpreter->contentPointer];
            }
            break;
        case ']': // ] - Go back to the last '['
            interpreter->contentPointer = interpreter->bracketPairs[interpreter->contentPointer] - 1;
            break;
        default:
            break;
    }

    return advance(interpreter);
}


//* Run the interpretation of the given file
//TODO: Implement REPL mode
void run(BFInterpreter* interpreter, std::string path) {

    loadFileContents(interpreter, path);
    loopLexing(interpreter);

    advance(interpreter);
    while (interpreter->contentPointer != (int)interpreter->fileContents.length()) {
        performAction(interpreter);
    }

}


//*Entry point
int main(int argc, char** argv) {

    if (argc == 1) {
        std::cerr << "Provide path to the source file";
        return 1;
    }
    BFInterpreter intp;

    run(&intp, argv[1]);

    return 0;
}