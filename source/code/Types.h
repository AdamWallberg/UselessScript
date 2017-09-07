#pragma once

enum Inst : unsigned char
{
	BYTE = 1,
	INTEGER,
	FLOAT,
	STRING,
	NEGATIVE,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	PRINT,
	PRINTS,
};