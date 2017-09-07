#pragma once

enum Inst : unsigned char
{
	BYTE = 1,
	INTEGER,
	FLOAT,
	NEGATIVE,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	PRINT,
};