#pragma once

#include <stdbool.h>

#define TSIZE 45
#define MAXITEMS 3

struct element {
    char name[TSIZE];
};

struct node {
    struct element item;
    struct node* next;
};

struct queue {
    struct node* front;
    struct node* rear;
    int n_items;
};

void InitializeQueue(struct queue* p_queue);
bool QueueIsFull(const struct queue* p_queue);
bool QueueIsEmpty(const struct queue* p_queue);
int QueueItemCount(const struct queue* p_queue);
bool EnQueue(struct element item, struct queue* p_queue);
bool DeQueue(struct element* p_item, struct queue* p_queue);
void EmptyTheQueue(struct queue* p_queue);
void TraverseQueue(struct queue* p_queue, void (*func)(struct element item));
