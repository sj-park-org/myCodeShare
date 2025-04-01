//
// Created by spros on 25. 3. 29.
//

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include <stdbool.h>

#define TSIZE 45
#define MAXSIZE 4

//구조체인 이유는 추후에 여러 아이템을 추가할 수 있음.
struct element{ //struct Item
  char name[TSIZE];
};

struct queue{
  int front;
  int rear;
  int n_items;
  struct element items[MAXSIZE];
};

void InitializeQueue(struct queue* p_que);
bool QueueIsFull(const struct queue* p_que);
bool QueueIsEmpty(const struct queue* p_que);
int QueueItemCount(const struct queue* p_que);
bool EnQueue(struct element item, struct queue* p_que);
bool DeQueue(struct element* p_item, struct queue* p_que);
void EmptyTheQueue(struct queue* p_que);
void TraverseQueue(struct queue* p_que,
    void (*func)(struct element item));





#endif //ARRAYQUEUE_H
