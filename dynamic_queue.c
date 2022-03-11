/* Dynamic queue in C
 *
 *
 * */

#include "dynamic_queue.h"

typedef struct queue_data { // header of the queue
	queue_size_t capacity; // max items allocated CHANGE LATER
	queue_size_t high_ptr; 
	queue_size_t low_ptr;
	char buff[]; // use char to store bytes of an unknown type
} queue_data;


queue queueInit(type_size t_size)  /* returns type void* */ {
	queue_data* q_data = malloc(sizeof(queue_data) + INIT_SIZE * t_size);
	(char*)q_data->capacity = INIT_SIZE;
	q_data->high_ptr = 0;
	q_data->low_ptr = 0;
	return &q_data->buff;	// returns a void* to the buffer, queue is a ptr to the buffer
}


queue_data* queueGetData(queue q) {
	return &((queue_data*)q)[-1];
}


queue_size_t queueHighPtr(queue q) {
	return queueGetData(q)->high_ptr;
}


queue_size_t queueCapacity(queue q) {
	return queueGetData(q)->capacity;
}

queue_size_t queueSize(queue q) {
	return queueGetData(q)->high_ptr - queueGetData(q)->low_ptr;
}


queue_data* queueRealloc(queue_data* q_data, type_size t_size)
{
	queue_size_t new_capacity = (q_data->capacity == 0) ? 1 : q_data->capacity * 2;
	#ifdef DEBUG
	printf("Reallocated to size: %zu \n", new_capacity);
	#endif
	queue_data* new_q_data = (queue_data*)
		realloc(q_data, sizeof(queue_data) + new_capacity * t_size);
	assert(new_q_data != NULL);
	new_q_data->capacity = new_capacity;
	return new_q_data;
}


void queueFree(queue q) {
	free(queueGetData(q));
}


bool isEmpty(queue_data* q_data) {
	return q_data->high_ptr == 0;
}


bool isFull(queue_data* q_data) {
	return q_data->capacity - q_data->high_ptr == 0;
}


bool isUnbalanced(queue_data* q_data) {
	return q_data->low_ptr > (q_data->high_ptr) / 2;
}


void* _queue_add(queue* queue_addr, type_size t_size) {

	queue_data* q_data = queueGetData(*queue_addr);

	if (isUnbalanced(q_data)) {
		#ifdef DEBUG
		printf("Unbalanced \n");
		#endif
		memmove(&q_data->buff[0],
			&q_data->buff[(q_data->low_ptr) * t_size],
			((q_data->high_ptr) - (q_data->low_ptr)) * t_size); // move trailing elements

		q_data->high_ptr -= q_data->low_ptr;
		q_data->low_ptr = 0;
	}

	if (isFull(q_data))
	{
		q_data = queueRealloc(q_data, t_size);
		*queue_addr = q_data->buff;
	}
	return (void*)&q_data->buff[t_size * q_data->high_ptr++];
}


void* _queuePopReturn(queue q, type_size t_size) {
	queue_size_t index = (queueGetData(q)->high_ptr--) - 1;
	assert(index >= 0);
	return ((char*)q + t_size * index);
}


void* _queueDequeue(queue q, type_size t_size) {
	queue_size_t index = (queueGetData(q)->low_ptr++);
	assert(index >= 0 && index <= queueGetData(q)->high_ptr);
	assert(queueGetData(q)->low_ptr <= queueGetData(q)->high_ptr);

	return ((char*)q + t_size * index);
}


void* _queuePeek(queue q, type_size t_size) {
	queue_size_t index = (queueGetData(q)->low_ptr);
	assert(index >= 0 && index <= queueGetData(q)->high_ptr);
	return ((char*)q + t_size * index);
}



