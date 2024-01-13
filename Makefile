# Makefile
CFLAGS= -Wall -Wextra
BUILDTARGET= ./target/



main:
	@echo "Compiling..."
	@test -d $(BUILDTARGET) || mkdir $(BUILDTARGET)
	g++ ./src/brainfuck.cpp ./src/cli.cpp ${CFLAGS} -o ./target/brainfuck.exe