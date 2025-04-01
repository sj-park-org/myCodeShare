#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedQueue2.h"

struct element get_item(const char * name) {
    struct element new_item;
    strcpy(new_item.name, name);
    return new_item;
}

void print_item(struct element item) {
    printf("%s ", item.name);
}

void print_queue(struct queue* p_queue) {
    printf("Front: %s at %p, Rear: %s at %p, Size %d\n",
        p_queue->front == NULL ? "NULL" : p_queue->front->item.name, p_queue->front,
        p_queue->rear == NULL ? "NULL" : p_queue->rear->item.name, p_queue->rear, p_queue->n_items);

    printf("Queue: \n");
    if (QueueIsEmpty(p_queue))
        printf("Empty");
    else
        TraverseQueue(p_queue, &print_item);
    printf("\n\n");
}

int main(void)
{
    struct queue queue;
    struct element temp;

    InitializeQueue(&queue);

    EnQueue(get_item("Jack"), &queue);
    print_queue(&queue);

    EnQueue(get_item("Henry"), &queue);
    print_queue(&queue);

    EnQueue(get_item("Stan"), &queue);
    print_queue(&queue);

    EnQueue(get_item("Butters"), &queue);
    print_queue(&queue);

    if (DeQueue(&temp, &queue))
        printf("Item from queue: %s\n", temp.name);
    print_queue(&queue);

    if (DeQueue(&temp, &queue))
        printf("Item from queue: %s\n", temp.name);
    print_queue(&queue);

    if (DeQueue(&temp, &queue))
        printf("Item from queue: %s\n", temp.name);
    print_queue(&queue);

    if (DeQueue(&temp, &queue))
        printf("Item from queue: %s\n", temp.name);
    print_queue(&queue);

    printf("------ Circulation Test ------\n");

    InitializeQueue(&queue);

    for (int i = 0; i < 10; ++i) {
        EnQueue(get_item("Hello"), &queue);
        print_queue(&queue);

        if (DeQueue(&temp, &queue))
            printf("Item from queue: %s\n", temp.name);
        print_queue(&queue);
    }



    return 0;
}

