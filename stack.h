//
// Created by spros on 25. 3. 29.
//

#ifndef STACK_H
#define STACK_H

#include "element.h"
#include <stdbool.h>

#define MAX_STACK_SIZE 5

struct stack
{
    struct element items[MAX_STACK_SIZE];
    int top;
};

void Initialize(struct stack* stack);
bool IsFull(const struct stack* stack);
bool IsEmpty(const struct stack* stack);
void Push(struct stack* stack, struct element item);
struct element Pop(struct stack* stack);


#endif //STACK_H
