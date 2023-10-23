# Makefile
CFLAGS= -Wall -Wextra

main:
	@echo "Compiling..."
	g++ .\src\brainfuck.cpp ${CFLAGS} -o .\target\brainfuck.exe