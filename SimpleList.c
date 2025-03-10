#include "SimpleList.h"

#include <stdio.h>
#include <stdlib.h>

void InitializeList(struct list* plist) {
    plist->head = NULL;
}
static void CopyToNode(struct movie item, struct node* pnode) {
    pnode->item = item;
}
bool AddItem(struct movie item, struct list* plist) {
    struct node* new_node;
    struct node* search = plist->head;
    new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Malloc failed.\n");
        return false;
    }
    CopyToNode(item, new_node); //copy과정까지 new_node 생성과 합쳐서 하나로 만든나면?
    new_node->next = NULL;
    if (search == NULL)
        plist->head = new_node;
    else {
        while (search->next != NULL)
            search = search->next;
        search->next = new_node;
    }
    return true;
}
unsigned int PrintAllItems(const struct list* plist,
    void (*print_an_item_func)(struct movie item)) {
    struct node* pnode = plist->head;
    unsigned int count = 0;
    while (pnode != NULL) {
        printf("%d : ", count);
        (*print_an_item_func)(pnode->item);
        pnode = pnode->next;
        count++;
    }
    return count;
}
bool FindItemByIndex(const struct list* plist, const int index,
    struct movie** item) {

    struct node* pnode = plist->head;
    int count = 0;
    while (pnode != NULL) {
        if (count == index) break;
        pnode = pnode->next;
        count++;
    }
    if (pnode==NULL)
        return false;
    else {
        *item = &pnode->item;
        return true;
    }
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

struct node* FindNodeByIndex(const struct list* plist, const int index) {
    struct node* pnode = plist->head;
    int count = 0;
    while (pnode != NULL) {
        if (count == index) break;
        pnode = pnode->next;
        count++;
    }
    return pnode;
}
bool InsertItemFront(struct movie item, struct list* plist) {
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Malloc failed.\n");
        return false;
    }
    CopyToNode(item, new_node);
    struct node* temp = plist->head;
    plist->head = new_node;
    new_node->next = temp;
    return true;
}
void InsertByIndex(struct movie item, struct list* plist, int index) {
    struct node* prev = FindNodeByIndex(plist, index -1);
    if (prev==NULL)
        InsertItemFront(item, plist);
}

void ClearList(struct list* plist) {
    struct node* iterator = plist->head;
    struct node* temp = NULL;
    while (iterator != NULL) {
        temp = iterator->next;
        free(iterator);
        iterator = temp;
    }
    plist->head = NULL;
}
void RemoveFirstItem(struct list* plist) {
    struct node* temp = NULL;
    if (plist->head != NULL)
        temp = plist->head->next;
    free(plist->head);
    plist->head = temp;
}
void RemoveNextItem(struct node* prev) {
    struct node* temp = NULL;
    if (prev->next == NULL)
        temp = NULL;
    else
        temp = prev->next->next;
    free(prev->next);
    prev->next = temp;
}

void RemoveByIndex(struct list* plist, int index) {
    struct node* prev = FindNodeByIndex(plist, index -1);
    if (prev == NULL)
        RemoveFirstItem(plist);
    else
        RemoveNextItem(prev);
}
unsigned int WriteAllItems(const struct list* plist, FILE* file,
    void (*write_an_item_func)(FILE* file, struct movie item)) {
    struct node* pnode = plist->head;
    unsigned int count = 0;
    while (pnode != NULL) {
        (*write_an_item_func)(file, pnode->item);
        pnode = pnode->next;
        count++;
    }
    return count;
}













