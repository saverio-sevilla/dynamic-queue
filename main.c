#include "dynamic_queue.h"
#define TYPE float
int main() {

	queue q = queueInit(sizeof(TYPE));
	printf("Size of queue: %zu\n", queueNItems(q));
	printf("Capacity of queue: %zu \n", queueCapacity(q));

	for (int i = 0; i < 1000; i++) {
		enqueue(&q, TYPE, (TYPE)i );
	}

	printf("Size of queue: %zu\n", queueNItems(q));
	printf("Capacity of queue: %zu \n", queueCapacity(q));

	TYPE result;

	
	for (int i = 1; i < 20; i++) {
		result = dequeue(q, TYPE);
		printf("result: %f \n", result);
		printf("Number of items: %zu\n", queueNItems(q));
	}

	queueFree(q);
	return 0;
}