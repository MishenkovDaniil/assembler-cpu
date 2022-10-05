CC = g++
FLAGS = -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual

all:
	g++ asm.cpp op_code.cpp ..\..\standart_functions\io\io.cpp
	a.exe ..\calc.txt ..\out.txt MZ 1.0
