#include <iostream>
#include <cstdlib>
#include "Interpreter.hpp"

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "[Error] No input file provided !" << std::endl;
		std::cout << "[Info] Usage : ./EAH <my_program.bf>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string programPath = std::string(argv[1]);

	Interpreter interpreter;

	interpreter.LoadProgramFromFile(programPath);

	interpreter.Interpret();

	return EXIT_SUCCESS;
}