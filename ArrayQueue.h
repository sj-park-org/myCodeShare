#pragma once

#include <stdbool.h>

#define TSIZE 45
#define MAXSIZE 4

struct element {
    char name[TSIZE];
};

struct queue {
    int front;
    int rear;
    int n_items;
    struct element items[MAXSIZE];
};

void InitializeQueue(struct queue* p_que);
bool QueueIsFull(const struct queue* p_que);
bool EnQueue(struct element item, struct queue* p_que);
bool QueueIsEmpty(const struct queue* p_que);
bool DeQueue(struct element* p_item, struct queue* p_que);
