#include "Parser.h"
#include "Machine.h"
#include "Serializer.h"
#include <iostream>

int main()
{
	Serializer serializer;

	{
		Parser parser;
		std::vector<unsigned char> code = parser.readAndParse("test_script.uls");

		serializer.writeToFile("binary_test.ulb", code);
	}
	
	{
		std::vector<unsigned char> code = serializer.readFromFile("binary_test.ulb");

		Machine interpreter;
		interpreter.run((char*)&code[0], code.size());
	}
	

	std::cin.get();
	return 0;
}