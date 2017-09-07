#include "Machine.h"
#include <assert.h>
#include "Types.h"
#include <stdio.h>
#include <cstring>
#include <string>

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
		case Inst::STRING:
		{
			int length = code[++i];
			for (int j = 0; j < length; j++)
			{
				push(code[++i]);
			}
			push(length);
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
		case Inst::PRINTS:
		{
			std::string value;
			unsigned char size = pop();

			for (int j = 0; j < size; j++)
			{
				value.insert(value.begin(), pop());
			}

			printf("%s\n", value.c_str());
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
