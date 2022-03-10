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

int test1(void) {

	queue q = queueInit(sizeof(TYPE));

	assert(queueNItems(q) == 0); // Assert that the queue is empty after initialization
	assert(queueCapacity(q) == INIT_SIZE); // Assert that the initial capacity is INIT_SIZE
	printf("Size of queue: %zu\n", queueNItems(q));
	printf("Capacity of queue: %zu \n", queueCapacity(q));

	for (int i = 0; i < 1000; i++) {
		enqueue(&q, TYPE, (TYPE)i);
	}

	assert(queueNItems(q) == 1000);
	assert(queueCapacity(q) >= queueNItems(q));

	printf("Size of queue: %zu\n", queueNItems(q));
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

int test2(void) {
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

}

int main() {
	int t1 = test1();
	int t2 = test2();
}