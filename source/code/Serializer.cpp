#include "Serializer.h"
#include <fstream>

void Serializer::writeToFile(const char* filePath, std::vector<unsigned char> bytecode)
{
	// Insert size as first value
	unsigned char sizeData[4];
	int size = bytecode.size();
	memcpy(&sizeData[0], &size, sizeof(sizeData));
	bytecode.insert(bytecode.begin(), sizeData[3]);
	bytecode.insert(bytecode.begin(), sizeData[2]);
	bytecode.insert(bytecode.begin(), sizeData[1]);
	bytecode.insert(bytecode.begin(), sizeData[0]);

	// Write bytecode to file
	std::ofstream file;
	file.open(filePath, std::ios::out | std::ios::binary);
	file.write((char*)&bytecode[0], bytecode.size() * sizeof(char));
	file.close();
}

std::vector<unsigned char> Serializer::readFromFile(const char* filePath)
{
	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::binary);

	// Fetch size
	unsigned char sizeData[4];
	int size;
	file.read((char*)&sizeData[0], sizeof(sizeData));
	memcpy(&size, &sizeData[0], sizeof(int));

	// Read bytecode
	std::vector<unsigned char> bytecode(size);
	file.read((char*)&bytecode[0], size * sizeof(char));

	return bytecode;
}
