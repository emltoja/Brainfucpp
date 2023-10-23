/**********************************************
*   PROJECT: Brainfuck compiler written in C++
*   AUTHOR:  Emil Olszewski
*   DATE:    22.10.2023
***********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cassert>
#include <map>

// Capital ASSERT for better visibility
#define ASSERT assert


// Compiler struct
struct BFCompiler {
    char               memory[30000] = {0};
    char               currentChar = 0;
    int                memoryPointer = 0;
    std::string        fileContents;
    int                contentPointer = -1;
    std::map<int, int> leftToRight;            // K - left bracket pos, V - right bracket pos
    std::map<int, int> rightToLeft;            // K - right bracket pos, V - left bracket
};


// Load source file to compiler buffer
int loadFileContents(BFCompiler* compiler, std::string path) {

    std::ifstream file(path);
    std::string   line;

    if (!file.is_open()) {
        std::cerr << "Failed to open the file at " << path;
        return 1;
    }

    while (std::getline(file, line)) {
        compiler->fileContents += line + '\n';
    }

    return 0;
}

// Advance to the next character in the buffer and read it
char advance(BFCompiler* compiler) {
    compiler->contentPointer++;
    compiler->currentChar = compiler->fileContents[compiler->contentPointer];
    return compiler->currentChar;
}


// Perform lexycal analysis on loop brackets structure
void loopLexing(BFCompiler* compiler) {

    std::stack<int> leftBrackets;

    for (int i = 0; i < compiler->fileContents.length(); ++i) {
        char current = compiler->fileContents[i];
        if (current == '[') {
            leftBrackets.push(i);
        } else if (current == ']') {
            assert(!leftBrackets.empty());
            compiler->leftToRight[leftBrackets.top()] = i;
            compiler->rightToLeft[i] = leftBrackets.top();
            leftBrackets.pop();
        } else {
            continue;
        }
    }
}


char performAction(BFCompiler* compiler) {

    std::size_t closedLoopPos;

    switch (compiler->currentChar)
    {
        case '>': // > - Increment pointer
            ++compiler->memoryPointer;
            break;
        case '<': // < - Decrement pointer
            --compiler->memoryPointer;
            break;
        case '+': // + - Increment at current position
            ++compiler->memory[compiler->memoryPointer];
            break;
        case '-': // - - Decrement at current position
            --compiler->memory[compiler->memoryPointer];
            break;
        case '.': // . - Display at current position
            std::putchar(compiler->memory[compiler->memoryPointer]);
            break;    
        case ',': // , - Get char and put at current position
            compiler->memory[compiler->memoryPointer] = std::getchar();
            break;
        case '[': // [ - Goto next ']' if at current position is 0
            if (!compiler->memory[compiler->memoryPointer]) {
                compiler->contentPointer = compiler->leftToRight[compiler->contentPointer];
            }
            break;
        case ']': // ] - Go back to the last '['
            compiler->contentPointer = compiler->rightToLeft[compiler->contentPointer] - 1;
            break;
        default:
            break;
    }

    return advance(compiler);
}

void run(BFCompiler* compiler, std::string path) {

    loadFileContents(compiler, path);
    loopLexing(compiler);

    advance(compiler);
    while (compiler->contentPointer != compiler->fileContents.length()) {
        performAction(compiler);
    }

}


// Entry point
int main(int argc, char** argv) {

    if (argc == 1) {
        std::cerr << "Provide path to the source file";
        return 1;
    }
    BFCompiler cmp;

    run(&cmp, argv[1]);
    // run(&cmp, argv[1]);

    return 0;
}