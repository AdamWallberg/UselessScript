#include "Parser.h"
#include "Interpreter.h"
#include <iostream>

int main()
{
	Parser parser;
	std::vector<unsigned char> code = parser.readAndParse("test_script.uls");

	Interpreter interpreter;
	interpreter.run((char*)&code[0], code.size());

	std::cin.get();
	return 0;
}