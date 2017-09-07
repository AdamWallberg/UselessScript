#include "Machine.h"
#include <assert.h>
#include "Types.h"
#include <stdio.h>
#include <cstring>

Machine::Machine()
	: m_stackSize(0)
{
}

void Machine::run(char code[], int size)
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
			int value;
			memcpy(&value, &data[0], sizeof(char) * 4);
			push(value);
			break;
		}
		case Inst::FLOAT:
		{
			unsigned char data[4];
			data[0] = code[++i];
			data[1] = code[++i];
			data[2] = code[++i];
			data[3] = code[++i];
			int value;
			memcpy(&value, &data[0], sizeof(char) * 4);
			push(value);
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
			float vf;
			memcpy(&vf, &value, sizeof(float));
			printf("%d\t%f\n", value, vf);
			break;
		}
		}
	}
}

void Machine::push(int value)
{
	assert(m_stackSize < MAX_STACK_SIZE);
	m_stack[m_stackSize++] = value;
}

int Machine::pop()
{
	assert(m_stackSize >= 0);
	return m_stack[--m_stackSize];
}
