//
// Created by spros on 25. 2. 11.
//

#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <stdio.h>
#include <stdbool.h>

#define TSIZE 45

struct movie {
    char title[TSIZE];
    float rating;
};
struct node {
    struct movie item;
    struct node* next;
};
struct list {
    struct node* head;
    int size;
};

void InitializeList(struct list* plist);
bool IsEmpty(const struct list* plist);
bool IsFull(const struct list* plist);
bool AddItem(struct movie item, struct list* plist);
void InsertByIndex(struct movie item, struct list* plist, int index);
void RemoveByIndex(struct list* plist, int index);
bool InsertItemFront(struct movie item, struct list* plist);
bool Find(const struct list* plist, struct movie item_to_find, int* index, struct movie* item_found);
bool (*compare_func)(struct movie a, struct movie b);

unsigned int CountItems(const struct list* plist);
unsigned int PrintAllItems(const struct list* plist, void (*print_an_item_func)(struct movie item));
unsigned int WriteAllItems(const struct list* plist, FILE* file, void (*write_an_item_func)(FILE* file, struct movie item));

void Traverse(const struct list* plist, void (*pfun)(struct movie item));
void CLearList(struct list* plist);

bool FindItemByIndex(const struct list* plist, const int index, struct movie** item);
void RemoveFisrtItem(struct list* plist);




#endif //SIMPLELIST_H
