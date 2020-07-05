#include "stack.h"



stack::stack()
{
	top = -1;
}

void stack::push(int x)
{
	a[++top] = x;
}

int stack::pop()
{
	return a[top--];
}

int stack::peep()
{
	return a[top];
}

bool stack::is_empty()
{
	return (top == -1);
}

bool stack::is_full()
{
	return(top >= MAX-1);
}

stack::~stack()
{
}
