#ifndef QUEUE_H_
#define QUEUE_H_

class queue {
protected:
	int a[5],front,rear;
public:
	queue();
	void enqueue(int);
	int dequeue();
	void display();
	bool is_full();
	bool is_empty();
	virtual ~queue();
};

#endif /* QUEUE_H_ */
