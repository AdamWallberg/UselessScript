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
		EXPRESSION
	};

	ArgType checkArgumentType(std::string arg);

	std::map<std::string, unsigned char> m_syntaxChart;
};