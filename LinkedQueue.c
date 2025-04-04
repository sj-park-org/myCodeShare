//
// Created by spros on 25. 4. 1.
//

#include "LinkedQueue2.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void CopyToNode(struct element item, struct node* p_node){
    p_node->item = item;
} // 매개변수 아이템을 노드의 아이템에 복사

static void CopyToItem(struct node* p_node, struct element* p_item) {
    *p_item = p_node->item;
} // 노드의 아이템을 매개변수 아이템에 복사

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
    return p_queue->n_items; //매번 카운트를 하면 포인터를 따라가면서 성능 감소가 발생. 단순히 숫자를 저장
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
    CopyToNode(item, p_newNode); //뉴노드에 아이템을 복사
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
    CopyToItem(p_queue->front, p_item); //노드의 아이템을 *p_item에 복사
    p_node = p_queue->front;
    p_queue->front = p_queue->front->next;
    free(p_node);
    p_queue->n_items--;
    if (p_queue->n_items == 0)
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