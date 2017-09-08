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
	int ifDepth = 0;
	int posDepth = 0;

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
		case Inst::PRINT_I:
		{
			int value = pop();
			float vf;
			memcpy(&vf, &value, sizeof(float));
			printf("%d\n", value);
			break;
		}
		case Inst::PRINT_S:
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
		case Inst::IF:
		{
			int value = pop();

			ifDepth++;
			if (value == 0)
			{
				int numEncounters = 0;
				while (true)
				{
					unsigned char value = code[++i];

					if (value == Inst::IF)
						numEncounters++;

					if (value == Inst::ELSE || value == Inst::END)
					{
						if (numEncounters > 0)
						{
							if(value == Inst::END)
								numEncounters--;
						}
						else
						{
							i--;
							break;
						}
					}
				}
			}
			else
			{
				posDepth++;
			}
			break;
		}
		case Inst::ELSE:
		{
			if (ifDepth == posDepth)
			{
				while (true)
				{
					unsigned char value = code[++i];
					if (value == Inst::END)
					{
						i--;
						break;
					}
				}
			}
			else
			{
				posDepth++;
			}
			break;
		}
		case Inst::END:
		{
			ifDepth--;
			if (ifDepth < 0)
				ifDepth = 0;
			posDepth--;
			if (posDepth < 0)
				posDepth = 0;
			break;
		}
		case Inst::CMP:
		{
			int a = pop();
			int b = pop();
			push(a == b);
			break;
		}
		case Inst::GT:
		{
			int a = pop();
			int b = pop();
			push(a > b);
			break;
		}
		case Inst::LT:
		{
			int a = pop();
			int b = pop();
			push(a < b);
			break;
		}
		case Inst::GTE:
		{
			int a = pop();
			int b = pop();
			push(a >= b);
			break;
		}
		case Inst::LTE:
		{
			int a = pop();
			int b = pop();
			push(a <= b);
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
