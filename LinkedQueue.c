#include "LinkedQueue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void CopyToNode(struct element item, struct node* p_node) {
    p_node->item = item;
}

static void CopyToItem(struct node* p_node, struct element* p_item) {
    *p_item = p_node->item;
}

void InitializeQueue(struct queue* p_queue) {
    p_queue->front = NULL;
    p_queue->rear = NULL;
    p_queue->n_items = 0;
}

bool QueueIsFull(const struct queue* p_queue) {
    return p_queue->n_items == MAXITEMS;
}

bool QueueIsEmpty(const struct queue* p_queue) {
    return p_queue->n_items == 0;
}
int QueueItemCount(const struct queue* p_queue) {
    return p_queue->n_items;
}

bool EnQueue(struct element item, struct queue* p_queue) {
    if (QueueIsFull(p_queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return false;
    }
    struct node* p_newNode;
    p_newNode = (struct node*)malloc(sizeof(struct node));
    if (p_newNode == NULL) {
        printf("Malloc() failed.\n");
        return false;
    }
    CopyToNode(item, p_newNode);
    p_newNode->next = NULL;

    if (QueueIsEmpty(p_queue))
        p_queue->front = p_newNode;
    else
        p_queue->rear->next = p_newNode;
    p_queue->rear = p_newNode;
    p_queue->n_items++;
    return true;
}

bool DeQueue(struct element* p_item, struct queue* p_queue) {
    if (QueueIsEmpty(p_queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return false;
    }
    struct node* p_node;
    CopyToItem(p_queue->front, p_item);
    p_node = p_queue->front;
    p_queue->front = p_queue->front->next;
    free(p_node);
    if (p_queue->n_items==0)
        p_queue->rear = NULL;

    return true;

}

void EmptyTheQueue(struct queue* p_queue) {
    struct element temp;
    while (!QueueIsEmpty(p_queue))
        DeQueue(&temp, p_queue);
}

void TraverseQueue(struct queue* p_queue, void (*func)(struct element item)) {
    struct node* temp = p_queue->front;
    while (temp != NULL) {
        (*func)(temp->item);
        temp = temp->next;
    }
}