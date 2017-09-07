#include "Interpreter.h"
#include <assert.h>
#include "Types.h"
#include <stdio.h>

Interpreter::Interpreter()
	: m_stackSize(0)
{
}

void Interpreter::run(char code[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int instruction = code[i];

		switch (instruction)
		{
		case Inst::BYTE:
		{
			char value = code[++i];
			push(value);
			break;
		}
		case Inst::INTEGER:
		{
			break;
		}
		case Inst::FLOAT:
		{
			break;
		}
		case Inst::NEGATIVE:
		{
			char value = pop();
			push(-value);
			break;
		}
		case Inst::ADD:
		{
			char a = pop();
			char b = pop();
			push(a + b);
			break;
		}
		case Inst::SUBTRACT:
		{
			char a = pop();
			char b = pop();
			push(a - b);
			break;
		}
		case Inst::MULTIPLY:
		{
			char a = pop();
			char b = pop();
			push(a * b);
			break;
		}
		case Inst::PRINT:
		{
			char value = pop();
			printf("%d\n", value);
			break;
		}
		}
	}
}

void Interpreter::push(int value)
{
	assert(m_stackSize < MAX_STACK_SIZE);
	m_stack[m_stackSize++] = value;
}

int Interpreter::pop()
{
	assert(m_stackSize >= 0);
	return m_stack[--m_stackSize];
}
