#pragma once

#include <stdbool.h>

#define TSIZE 45
#define MAXITEMS 10

struct cust {
    long arrival_time;
    int processtime;
};

struct node {
    struct cust item;
    struct node* next;
};

struct queue {
    struct node* front;
    struct node* rear;
};


void InitializeQueue(struct queue* p_queue);
bool QueueIsFull(const struct queue* p_queue);
bool QueueIsEmpty(const struct queue* p_queue);
int QueueItemCount(const struct queue* p_queue);
bool EnQueue(struct cust item, struct queue* p_queue);
bool DeQueue(struct cust* p_item, struct queue* p_queue);
void EmptyTheQueue(struct queue* p_queue);
void TraverseQueue(struct queue* p_queue, void (*func)(struct cust item));
