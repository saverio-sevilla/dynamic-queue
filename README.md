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
