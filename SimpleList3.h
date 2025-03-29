#pragma once

#include <stdbool.h>
#include <stdio.h>

#define TSIZE 45

struct item {
    char name[TSIZE];
    int year;
};
struct node {
    struct item item;
    struct node* next;
};
struct list {
    struct node* head;
    int size;
};

unsigned int ReadFromFile(struct list* plist, const char* filename,
    bool (*read_an_item_func)(FILE* file,struct item* item));
unsigned int PrintAllItems(const struct list* plist, void (*print_an_item_func)(struct item item));

unsigned int FindAndRun(const struct list* plist, struct item item_to_find,
    bool (*compare_func)(struct item a, struct item b),
    void (*func_run)(struct item item));

bool AddItem(struct item item, struct list* plist);
void InitializeList(struct list* plist);


