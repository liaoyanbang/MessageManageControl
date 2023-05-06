#ifndef _MOUDLE_LIST_H
#define _MOUDLE_LIST_H


typedef struct Node {
    int moudle;
    struct Node *next;
} Node_t;// 创建链表

Node_t* create_list(int data);
Node_t* insert_node(Node_t *head, int data);
Node_t* delete_node(Node_t *head, int data);
void print_list(Node_t *head);

#endif
