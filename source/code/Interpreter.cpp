#include "Interpreter.h"
#include <assert.h>
#include "Types.h"

Interpreter::Interpreter()
	: m_stackSize(0)
{
}

void Interpreter::run(char code[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int instruction = code[i];

		// TODO: Finish this shit
		switch (instruction)
		{
		case Inst::INTEGER:
		{
			break;
		}
		case Inst::NEGATIVE:
		{
			break;
		}
		case Inst::ADD:
		{
			break;
		}
		case Inst::SUBTRACT:
		{
			break;
		}
		case Inst::MULTIPLY:
		{
			break;
		}
		case Inst::PRINT:
		{
			break;
		}
		}
	}
}

void Interpreter::push(int value)
{
	assert(m_stackSize <= MAX_STACK_SIZE);
	m_stack[m_stackSize++] = value;
}

int Interpreter::pop()
{
	assert(m_stackSize >= 0);
	return m_stack[--m_stackSize];
}
