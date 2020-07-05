#ifndef STACK_H_
#define STACK_H_

#define MAX 10

class stack
{
	int a[MAX];
	int top;
public:
	stack();
	void push(int);
	int pop();
	int peep();
	bool is_full();
	bool is_empty();
	~stack();
};

#endif

