# Makefile
CFLAGS= -Wall -Wextra

main:
	@echo "Compiling..."
	g++ .\src\brainfuck.cpp .\src\cli.cpp ${CFLAGS} -o .\target\brainfuck.exe