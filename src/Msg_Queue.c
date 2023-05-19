#include "Msg_Queue.h"
#include "Mmc_Error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

msg_queue_t* createQueue(unsigned int size) 
{
    msg_queue_t *queue = (msg_queue_t*) malloc(sizeof(msg_queue_t));
    queue->messages = (message_t*) malloc(sizeof(message_t) * size);
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->max_size = size;
    return queue;
}
void freeQueue(msg_queue_t* queue)
{
    if(queue->messages != NULL)
        free(queue->messages);
    queue->messages = NULL;
    
    if(queue != NULL)
        free(queue);
    queue = NULL;
}

unsigned int enqueue(msg_queue_t *queue, message_t *message) {
    if (queue->size == queue->max_size) 
    {
        printf("Queue is full but push\n");
        queue->rear = (queue->rear + 1) % queue->max_size;
        queue->messages[queue->rear] = *message;
        return OK;
    }
    queue->rear = (queue->rear + 1) % queue->max_size;
    queue->messages[queue->rear] = *message;
    queue->size++;
    return OK;
}

message_t* dequeue(msg_queue_t *queue)
{
    if (queue->size == 0) 
    {
        return NULL;
    }

    message_t* message = (message_t*)malloc(sizeof(message_t));
    if(message == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    *message = queue->messages[queue->front];
    queue->front = (queue->front + 1) % queue->max_size;
    queue->size--;
    return message;
}
