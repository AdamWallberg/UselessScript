#include "Parser.h"
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <vector>
#include "Types.h"
#include <cmath>

Parser::Parser()
{
	// TODO: Setup syntax chart
#define ADD_EXPRESSION(NAME, CODE) m_syntaxChart[NAME] = Inst::CODE

	ADD_EXPRESSION("ADD", ADD);
	ADD_EXPRESSION("SUB", SUBTRACT);
	ADD_EXPRESSION("MUL", MULTIPLY);
	ADD_EXPRESSION("DIV", DIVIDE);
	ADD_EXPRESSION("PRINT", PRINT);
}

std::vector<unsigned char> Parser::readAndParse(const char* filePath)
{
	std::vector<unsigned char> code;

	// Read file
	std::ifstream file(filePath);
	std::string line;

	while (std::getline(file, line)) // Iterate lines
	{
		// Ignore empty lines
		if (line.size() == 0)
			continue;

		// Remove whitespace
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

		while (true) // Iterate parentheses
		{
			// Find last set of parentheses
			size_t parenthesisStart = line.find_last_of('(');
			if (parenthesisStart == std::string::npos)
				break;
			size_t parenthesisEnd = line.find(')', parenthesisStart) + 1;
			if (parenthesisEnd == std::string::npos)
			{
				printf("Missing ')'");
				assert(false);
			}

			// Extract arguments from parentheses, and remove from line
			// TODO: Define how many arguments each instruction takes, and do safe check.
			size_t argumentsLength = parenthesisEnd - parenthesisStart;
			std::string arguments = line.substr(parenthesisStart + 1, argumentsLength - 2);
			line.erase(parenthesisStart, argumentsLength);
			if (arguments.size() == 0)
				continue;

			bool cont = true;
			while (cont) // Iterate arguments
			{
				size_t lastArgPos = arguments.find_last_of(',');
				if (lastArgPos == std::string::npos)
				{
					cont = false;
					lastArgPos = 0;
				}

				std::string arg = arguments.substr(cont ? lastArgPos + 1 : lastArgPos, arguments.length());
				// Remove argument from argument list
				arguments.erase(lastArgPos, arguments.length());

				// Check if there's a negative operator
				bool negative = false;
				if (arg[0] == '-')
				{
					arg.erase(0, 1);
					negative = true;
				}

				ArgType argType = checkArgumentType(arg);

				if (argType == EXPRESSION)
				{
					unsigned char inst = m_syntaxChart[arg];
					// TODO: Check for error
					code.push_back(inst);
				}
				else if (argType == BYTE)
				{
					char value = std::stoi(arg);
					unsigned char inst = Inst::BYTE;
					code.push_back(inst);
					code.push_back(value);
				}
				else if (argType == INTEGER)
				{
					int value = std::stoi(arg);
					unsigned char inst = Inst::INTEGER;
					code.push_back(inst);

					unsigned char data[4];
					memcpy(&data[0], &value, sizeof(char) * 4);
					code.push_back(data[0]);
					code.push_back(data[1]);
					code.push_back(data[2]);
					code.push_back(data[3]);
				}
				else if (argType == FLOAT)
				{
					float value = std::stof(arg);
					unsigned char inst = Inst::FLOAT;
					code.push_back(inst);

					unsigned char data[4];
					memcpy(&data[0], &value, sizeof(char) * 4);
					code.push_back(data[0]);
					code.push_back(data[1]);
					code.push_back(data[2]);
					code.push_back(data[3]);
				}

				// Do this last
				if (negative)
				{
					code.push_back(Inst::NEGATIVE);
				}
			}
		}

		// Check base expression
		unsigned char inst = m_syntaxChart[line];
		code.push_back(inst);
	}

	return code;
}

Parser::ArgType Parser::checkArgumentType(std::string arg)
{
	if (arg[0] >= '0' && arg[0] <= '9')
	{
		size_t dotPos = arg.find('.');
		if (dotPos != std::string::npos)
			return ArgType::FLOAT;
		else
		{
			int value = std::stoi(arg);
			if (value < 256)
				return ArgType::BYTE;
			else
				return ArgType::INTEGER;
		}
	}

	return ArgType::EXPRESSION;
}
