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

void InsertByIndex(struct movie item, struct list* plist, int index);
void RemoveByIndex(struct list* plist, int index);

void ClearList(struct list* plist);

unsigned int CountItems(const struct list* plist);

unsigned int WriteAllItems(const struct list* plist, FILE* file, void (*write_an_item_func)(FILE* file, struct movie item));

bool Find(const struct list* plist, struct movie item_to_find, int* index, struct movie* item_found,
 bool (*compre_func)(struct movie a, struct movie b));