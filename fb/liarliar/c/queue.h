#ifndef QUEUE_H_
#define QUEUE_H_

#include "item.h"

#define QUEUESIZE 10000

typedef struct {
	int /*item_type*/ q[QUEUESIZE+1];	/* body of queue */
	int first;                      	/* position of first element */
	int last;                       	/* position of last element */
	int count;                      	/* number of queue elements */
} queue;

void init_queue(queue *q);
void enqueue(queue *q, item_type x);
item_type dequeue(queue *q);
item_type headq(queue *q);
int empty_queue(queue *q);

#endif
