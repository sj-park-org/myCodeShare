#pragma once

#include <stdbool.h>

#define TSIZE 45
#define MAXITEMS 3  //옵션

struct element{ //데이터
  char name[TSIZE];
};

struct node { //연결
    struct element item;
    struct node* next;
};

struct queue { //전체 연결, 데이터
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
