# dynamic-queue

A small implementation of queue in C, works with different types (even structs or struct pointers), will automatically resize itself
at runtime to accomodate any amount of elements. 

## Usage 

Initalize a queue containing elements of TYPE with 
```
queue q = queueInit(sizeof(TYPE))
```
Information about the capacity and size of the queue can be retrieved by calling
```
size_t queueCapacity(queue q);
size_t queueSize(queue q);
```
The main functions to dequeue and enqueue elements are
```
enqueue(queue* q, TYPE, value)
dequeue(q, type)
```
The user must remember that, to enqueue an element, the address of the queue is passed, while to dequeue, the queue itself is passed as parameter.
To peek on the first element at the front of the queue use the function 
```
peek(q, type)
```
Lastly to free the queue call the function
```
queueFree(queue q)
```

## Example

```
void example() {
	queue q = queueInit(sizeof(int));

	enqueue(&q, int, (int)42);
	enqueue(&q, int, (int)33);
	enqueue(&q, int, (int)16);
	enqueue(&q, int, (int)88);

	int val1 = peek(q, int);
	int val2 = dequeue(q, int);
	int val3 = dequeue(q, int);

	printf("peek: %d, first value: %d, second value: %d, capacity: %zu, size: %zu\n", val1, val2, val3, queueCapacity(q), queueSize(q));
}
```

Output: `peek: 42, first value: 42, second value: 33, capacity: 16, size: 2`
