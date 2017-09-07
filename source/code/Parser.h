#pragma once

#include <vector>
#include <map>
#include <string>

class Parser
{
public:
	Parser();
	std::vector<unsigned char> readAndParse(const char* filePath);
private:
	enum ArgType
	{
		BYTE,
		INTEGER,
		FLOAT,
		EXPRESSION,
		STRING,
	};

	unsigned char getExpressionCode(std::string expr);
	ArgType checkArgumentType(std::string arg);

	std::map<std::string, unsigned char> m_syntaxChart;
};