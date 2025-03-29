//
// Created by spros on 25. 3. 29.
//

#include "stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void Initialize(struct stack* stack){
    stack->top = -1;
}

bool IsFull(const struct stack* stack){
    if (stack->top >= MAX_STACK_SIZE -1)
      return true;
    else
      return false;
}

bool IsEmpty(const struct stack* stack){
    if (stack->top == -1)
      return true;
    else
      return false;
}

void Push(struct stack* stack, struct element item)
    {
    if (IsFull(stack) == true)
        printf("Stack is full. Cannot add.\n");
    else{
        stack->items[++stack->top] = item;
    }
}
struct element Pop(struct stack* stack){
     if (IsEmpty(stack) == true)
       {
         printf("Stack is empty. Cannot remove.\n");
         struct element temp = { -1 };
         return temp;
       }
       return stack->items[stack->top--]
}
