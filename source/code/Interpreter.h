#pragma once

class Interpreter
{
public:
	Interpreter();
	void run(char code[], int size);
private:
	// Stack
	static const int MAX_STACK_SIZE = 512;
	int m_stack[MAX_STACK_SIZE];
	int m_stackSize;
	void push(int value);
	int pop();
};