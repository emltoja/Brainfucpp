/**************************************************
*   PROJECT: Brainfuck interpreter written in C++
*   FILE:    CLI application cpp file
*   AUTHOR:  Emil Olszewski
*   DATE:    24.10.2023
***************************************************/

#include "cli.h"
#include "brainfuck.h"
#include <string>


void printHelp(CLIApplication* app) {
    std::cout << "Brainfuck interpreter version " << app->version << '\n';
}

void runApplication(CLIApplication* app, int argc, char** argv) {

    std::string s;
    switch(argc) {

        case 1:
            printHelp(app);
            break;

        case 2:
            s = argv[1];
            runFile(&(app->interpreter), s);
            break;

        case 3:
            s= argv[2];
            runTermInput(&(app->interpreter), s);
            break;

        default:
            break;
    }
}

//* Entry Point
int main(int argc, char** argv) {

    CLIApplication app;
    runApplication(&app, argc, argv);
    
}