#include "queue.h"
#include<iostream>
using namespace std;

queue::queue()
{
	front=rear=-1;
}

void queue::enqueue(int data)
{
	a[++rear]=data;
	if(front==-1)
		front++;
}

int queue::dequeue()
{
	return a[front++];
}

void queue::display()
{
	for(int i=front;i<=rear;i++)
		cout<<"\t"<<a[i];
}

bool queue::is_empty()
{
	if(rear==-1)
		return true;
	else
		return false;
}

bool queue::is_full()
{
	if(rear==4)
	{
		if(front==-1)
			return true;
		else
		{
			cout<<endl<<"Underflow";
			return true;
		}
	}
	else
		return false;
}

queue::~queue()
{
}

