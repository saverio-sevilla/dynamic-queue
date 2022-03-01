#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>


#define INIT_SIZE 16

typedef void* queue;
typedef size_t queue_size_t;	  // stores the number of elements
typedef unsigned char type_size; // stores the number of bytes for a type


#define DEBUG

#define queue_add_asg(q_addr, type)                                         \
	((type*)_queue_add((queue*)q_addr, sizeof(type)))

#define enqueue(q_addr, type, value)                                      \
	(*queue_add_asg(q_addr, type) = value)

#define popStack(q, type)                              \
	*(type*)_queuePopReturn(q, sizeof(type))

#define dequeue(q, type)                              \
	*(type*)_queueDequeue(q, sizeof(type))

#define back(q, type)                              \
	*(type*)_queuePeek(q, sizeof(type))

queue queueInit(type_size t_size);
void queueFree(queue q);
queue_size_t queueNItems(queue q);
queue_size_t queueCapacity(queue q);
void* _queuePeek(queue q, type_size t_size);
void* _queuePopReturn(queue q, type_size t_size);
void* _queueDequeue(queue q, type_size t_size);
void* _queue_add(queue* queue_addr, type_size t_size);

#endif
