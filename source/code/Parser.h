#pragma once

#include <vector>
#include <map>
#include <string>

class Parser
{
public:
	Parser();
	std::vector<int> readAndParse(const char* filePath);
private:
	std::map<std::string, int> m_syntaxChart;
};