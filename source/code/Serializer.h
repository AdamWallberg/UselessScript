#pragma once
#include <vector>

class Serializer
{
public:
	void writeToFile(const char* filePath, std::vector<unsigned char> bytecode);
	std::vector<unsigned char> readFromFile(const char* filePath);
};

