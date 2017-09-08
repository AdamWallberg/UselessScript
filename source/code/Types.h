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
	PRINT_I, // print integer
	PRINT_S, // print string
	IF,
	ELSE,
	END,
	CMP, // compare
	GT, // greater than
	LT, // lesser than
	GTE, // greater than or equals
	LTE, // less than or equals
};