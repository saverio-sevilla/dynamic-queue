#include "dynamic_queue.h"
#include <stdio.h>
#include <assert.h>

#define TYPE float
#undef DEBUG


typedef struct test_struct {
	int val1;
	float val2;
	char id;
} Test_struct;

void test1(void) {

	queue q = queueInit(sizeof(TYPE));

	assert(queueHighPtr(q) == 0); // Assert that the queue is empty after initialization
	assert(queueCapacity(q) == INIT_SIZE); // Assert that the initial capacity is INIT_SIZE
	printf("High ptr position in queue: %zu\n", queueHighPtr(q));
	printf("Capacity of queue: %zu \n", queueCapacity(q));

	for (int i = 0; i < 1000; i++) {
		enqueue(&q, TYPE, (TYPE)i);
	}

	assert(queueHighPtr(q) == 1000);
	assert(queueCapacity(q) >= queueHighPtr(q));

	printf("High ptr position in queue: %zu\n", queueHighPtr(q));
	printf("Capacity of queue: %zu \n", queueCapacity(q));

	TYPE result;

	for (int i = 0; i < 10; i++) {
		result = dequeue(q, TYPE);
		assert(result == (TYPE)i);
		#ifdef DEBUG
		printf("result: %f \n", result);
		printf("Number of items: %zu\n", queueNItems(q));
		#endif	
	}

	queueFree(q);
	return 0;
}

void test2(void) {
	Test_struct s1 = { 1, 3.14, 'c' };
	Test_struct s2 = { 5, 4.20, 'R' };
	Test_struct s3 = { -7, 5.5, 'e' };
	Test_struct s4 = { 3, 1.2, 'X' };
	Test_struct s5 = { 14, 6.8, 'b' };

	queue q2 = queueInit(sizeof(Test_struct));
	enqueue(&q2, Test_struct, s1);
	enqueue(&q2, Test_struct, s2);
	enqueue(&q2, Test_struct, s3);
	enqueue(&q2, Test_struct, s4);
	enqueue(&q2, Test_struct, s5);

	Test_struct result = dequeue(q2, Test_struct);
	#ifdef DEBUG
	printf("%d:%f:%c\n", result.val1, result.val2, result.id);
	#endif
	assert(result.val1 == 1 && result.id == 'c');
	result = dequeue(q2, Test_struct);
	#ifdef DEBUG
	printf("%d:%f:%c\n", result.val1, result.val2, result.id);
	#endif
	assert(result.val1 == 5 && result.id == 'R');

	queueFree(q2);

}


void test3(int iterations, int n_elements, int difference) {
	queue q = queueInit(sizeof(TYPE));

	if (difference > n_elements) {
		fprintf(stderr, "The difference in elements cannot be larger than the number of elements");
		exit(EXIT_FAILURE);
	}

	while (iterations) {

		for (int i = 0; i < n_elements; i++) {
			enqueue(&q, TYPE, (TYPE)i);
		}

		for (int i = 0; i < n_elements - difference; i++) {
			TYPE result = dequeue(q, TYPE);
		}

		iterations--;
	}

	printf("Size of queue: %zu\n", queueSize(q));
	printf("Capacity of queue: %zu \n", queueCapacity(q));
	queueFree(q);
}

void test4() {
	queue q = queueInit(sizeof(int));

	enqueue(&q, int, (int)42);
	enqueue(&q, int, (int)33);
	enqueue(&q, int, (int)16);
	enqueue(&q, int, (int)88);

	int val1 = peek(q, int);
	int val2 = dequeue(q, int);

	printf("val1: %d, val2: %d\n", val1, val2);
}

void example() {
	queue q = queueInit(sizeof(int));

	enqueue(&q, int, (int)42);
	enqueue(&q, int, (int)33);
	enqueue(&q, int, (int)16);
	enqueue(&q, int, (int)88);

	int val1 = peek(q, int);
	int val2 = dequeue(q, int);
	int val3 = dequeue(q, int);

	printf("%d, %d, %d, capacity: %zu, size: %zu\n", val1, val2, val3, queueCapacity(q), queueSize(q));

}

void main() {
	test1();
	test2();
	test3(900, 250, 0);
	test4();
	example();
}