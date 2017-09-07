#include "Interpreter.h"
#include <assert.h>

Interpreter::Interpreter()
	: m_stackSize(0)
{
}

void Interpreter::run(int code[], int size)
{
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
