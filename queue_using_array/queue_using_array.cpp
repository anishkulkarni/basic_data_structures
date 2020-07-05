#include <iostream>
#include"queue.h"
using namespace std;

int main()
{
	queue q;
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	q.enqueue(1);
	cout<<q.dequeue();
	cout<<endl<<q.dequeue();
	cout<<endl<<q.is_full();
}
