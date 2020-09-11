cmake_minimum_required(VERSION 3.17)
project(CPPBrainfuck)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPPBrainfuck main.cpp scanner.h scanner.cpp parser.cpp parser.h vm.cpp vm.h ast.cpp ast.h printer.h printer.cpp optimize.cpp optimize.h counter.cpp counter.h)