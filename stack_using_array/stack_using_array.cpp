#include"stack.h"
#include<iostream>
using namespace std;

int main()
{
	stack s;
	if (!s.is_full())
		s.push(2);
	if (!s.is_full())
		s.push(3);
	while (!s.is_empty())
		cout << s.pop();
    return 0;
}

