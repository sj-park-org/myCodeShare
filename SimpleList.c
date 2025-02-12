//
// Created by spros on 25. 2. 11.
//

#include "SimpleList2.h"

#include <stdio.h>
#include <stdlib.h>

static void CopyToNode(struct movie item, struct node* pnode) {
    pnode->item = item;
}
void InitializeList(struct list* plist) {
    plist->head = NULL;
}
bool IsEmpty(const struct list* plist) {
    if (plist->head == NULL)
        return true;
    else
        return false;
}
bool IsFull(const struct list* plist) {
    struct node* pt;
    bool full;
    pt = (struct node*)malloc(sizeof(struct node));
    if (pt == NULL)
        full = true;
    else
        full = false;
    free(pt);
    return full;
}
unsigned int CountItems(const struct list* plist) {
    unsigned int count = 0;
    struct node* pnode = plist->head;
    while (pnode != NULL) {
        ++count;
        pnode = pnode->next;
    }
    return count;
}
bool InsertItemFront(struct movie item, struct node* prev) {
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Malloc failed.\n");
        return false;
    }
    CopyToNode(item, new_node);
    struct node* temp = prev->next;
    prev->next = new_node;
    new_node->next = temp;
    return true;
}
bool AddItem(struct movie item, struct list* plist) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* search = plist->head;
    if (new_node == NULL) {
        printf("Malloc failed.\n");
        return false;
    }
    CopyToNode(item, new_node);
    new_node->next = NULL;

    if (search == NULL) {
        plist->head = new_node;
    }else {
        while (search->next != NULL)
            search = search->next;
        search->next = new_node;
    }
    return true;
}

unsigned int WriteAllItems(const struct list* )










