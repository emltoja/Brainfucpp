/**************************************************
*   PROJECT: Brainfuck interpreter written in C++
*   FILE:    CLI application header file
*   AUTHOR:  Emil Olszewski
*   DATE:    24.10.2023
***************************************************/

#ifndef CLI
#define CLI

#include <iostream>
#include <string>
#include <vector>
#include "brainfuck.h"

#define HELP_LONG_OPTION "--help"
#define TERM_INPUT_OPTION "-m"
#define HELP_SHORT_OPTION "-h"
#define VERSION_SHORT_OPTION "-v"
#define VERSION_LONG_OPTION "--version"


struct CLIApplication {
    
    BFInterpreter interpreter;
    std::vector<std::string> options;
    std::string input;
    const std::string version = "0.0.1";

};

void printHelp(CLIApplication* app);

void runApplication(CLIApplication* app, int argc, char** argv);


#endif //CLI
