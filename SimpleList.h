#pragma once

#include <stdbool.h>
#include <stdio.h>

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
bool AddItem(struct movie item, struct list* plist);
unsigned int PrintAllItems(const struct list* plist, void (*print_an_item_func)(struct movie item));

bool FindItemByIndex(const struct list* plist, const int index, struct movie** item);
unsigned int CountItems(const struct list* plist);

void InsertByIndex(struct movie item, struct list* plist, int index);
void ClearList(struct list* plist);

void RemoveByIndex(struct list* plist, int index);
unsigned int WriteAllItems(const struct list* plist, FILE* file,
    void (*write_an_item_func)(FILE* file, struct movie item));

