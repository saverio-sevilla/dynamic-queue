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
``'
peek(q, type)
```
