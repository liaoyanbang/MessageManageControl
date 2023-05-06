#include "Moudle_List.h"


#include <stdio.h>
#include <stdlib.h>


Node_t* create_list(int data) 
{
    Node_t *head = (Node_t*)malloc(sizeof(Node_t));  // 创建头节点
    head->moudle = data;
    head->next = NULL;
    return head;
}
// 插入元素
Node_t* insert_node(Node_t *head, int data) 
{
    Node_t *new_node = (Node_t*)malloc(sizeof(Node_t));
    new_node->moudle = data;
    new_node->next = head->next;
    head->next = new_node;
    return head;

}
// 删除元素
Node_t* delete_node(Node_t *head, int data) 
{
    Node_t *p = head->next;   // p指向第一个节点
    Node_t *q = head;         // q指向头节点
    while (p != NULL) {
        if (p->moudle == data) {
            q->next = p->next;
            free(p);
            break;
        }
        q = p;
        p = p->next;
    }
    return head;
}

// 打印链表
void print_list(Node_t* head) 
{
    Node_t* p = head->next;
    while (p != NULL) {
        printf("%d ", p->moudle);
        p = p->next;
    }
    printf("\n");
}