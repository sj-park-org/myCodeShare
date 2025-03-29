//
// Created by spros on 25. 3. 29.
//

#include "ArrayQueue.h"
#include <assert.h>
#include <stdio.h>

void TraverseQueue(struct queue* p_queue, void (*func)(struct element item)) {
    for (int i = p_queue->front; i != p_queue->rear; i = (i+1) % MAXSIZE)
        (*func)(p_queue->items[(i + 1) % MAXSIZE]);

}

void InitializeQueue(struct queue* p_queue) {
    p_queue->front = 0;
    p_queue->rear = 0;
    p_queue->n_items = 0;
}

bool QueueIsFull(const struct queue* p_queue) {
    return (p_queue->rear+1) %MAXSIZE == p_queue->front;
}

bool QueueIsEmpty(const struct queue* p_queue) {
    return p_queue->front == p_queue->rear;
}

int QueueItemCount(const struct queue* p_queue) {
    return p_queue->n_items;
}

bool EnQueue(struct element item, struct queue* p_queue) {
    if (QueueIsFull(p_queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return false;
    }
    p_queue->rear = (p_queue->rear + 1) % MAXSIZE;
    p_queue->items[p_queue->rear] = item;
    p_queue->n_items++;

    return true;
}
bool DeQueue(struct element* p_item, struct queue* p_queue) {
    if (QueueIsEmpty(p_queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return false;
    }

    p_queue->front = (p_queue->front +1) % MAXSIZE;
    *p_item = p_queue->items[p_queue->front];
    p_queue->n_items--;

    return true;
}

void EmptyTheQueue(struct queue* p_queue) {
    InitializeQueue(p_queue);
}