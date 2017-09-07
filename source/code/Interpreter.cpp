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
			unsigned char data[4];
			data[0] = code[++i];
			data[1] = code[++i];
			data[2] = code[++i];
			data[3] = code[++i];
			int value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
			push(value);
			break;
		}
		case Inst::FLOAT:
		{
			break;
		}
		case Inst::NEGATIVE:
		{
			int value = pop();
			push(-value);
			break;
		}
		case Inst::ADD:
		{
			int a = pop();
			int b = pop();
			push(a + b);
			break;
		}
		case Inst::SUBTRACT:
		{
			int a = pop();
			int b = pop();
			push(b - a);
			break;
		}
		case Inst::MULTIPLY:
		{
			int a = pop();
			int b = pop();
			push(a * b);
			break;
		}
		case Inst::DIVIDE:
		{
			int a = pop();
			int b = pop();
			push(a / b);
			break;
		}
		case Inst::PRINT:
		{
			int value = pop();
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
