//
// Created by spros on 25. 2. 11.
//
#include <stdio.h>
#include <stdbool.h>

#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#define TSIZE 45

struct movie {
    char title[TSIZE];
    float rating;
};
struct node {
    struct movie item;//노드 하나에 movie 아이템 하나
    struct node* next;
};
struct list {
    struct node* head;
    int size;
};


#endif //SIMPLELIST_H

void InitializeList(struct list* plist);
bool AddItem(struct movie item, struct list* plist);
unsigned int PrintAllItems(const struct list* plist, void (*print_an_item_func)(struct movie item));

bool FindItemByIndex(const struct list* plist, const int index, struct movie** item);
bool AddItem(struct movie item, struct list* plist);
