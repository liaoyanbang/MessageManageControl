#ifndef _MSG_QUEUE_H
#define _MSG_QUEUE_H
#include <stdbool.h>

typedef struct {
    int event_id;
    int parameter_1;
    int parameter_2;
} message_t;

typedef struct {
    message_t *messages;
    int front;
    int rear;
    unsigned int size;
    unsigned int max_size;
} msg_queue_t;

msg_queue_t* createQueue(unsigned int size);
void freeQueue(msg_queue_t* queue);
unsigned int enqueue(msg_queue_t *queue, message_t *message);
message_t* dequeue(msg_queue_t *queue);

#endif
