//
// Created by spros on 25. 2. 11.
//


#include <stdio.h>
#include "SimpleList.h"

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
    CopyToNode(item, new_node);
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
    void(*print_an_item_func)(struct movie item)) {
    struct node* pnode = plist->head;
    unsigned int count = 0;
    while (pnode !=NULL) {
        printf("%d : ", count);
        (*print_an_item_func)(pnode->item);
        pnode =pnode->next;
        count++;
    }
    return count;
}
bool FindItemByIndex(const struct list* plist, const int index, struct movie** item) {
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
        //item은 node에 있는 struct movie 구조체의 오브젝트임
        //그 오브젝트의 주소를 대입하려고 하는 것.
        // 만약 오브젝트를 수정하려고 했다면 오브젝트의 주소가 아니라 오브젝트의 내용만 변경해도 됨.
        // item->title = pnode->item->title;
        //struct movie** item은 복사가 두번 발생.
        //1. 함수의 매개변수로 전달 2. pnode->item의 복사(원본전달을 위해 &pnode->item을 사용)
        return true;
    }
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
bool AppendItem(struct movie item, struct node* prev) {
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

void InsertByIndex(struct movie item, struct list* plist, int index) {
    struct node* prev = FindNodeByIndex(plist, index -1);
    if (prev==NULL)
        InsertItemFront(item, plist);
    else
        AppendItem(item, prev);
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
        temp == NULL;
    else
        temp = prev->next->next;
    free(prev->next);
    prev->next = temp;
}

void RemoveByIndex(struct list* plist, int index) {
    struct node* prev = FindNodeByIndex(plist, index - 1);
    if (prev == NULL)
        RemoveFirstItem(plist);
    else
        RemoveNextItem(prev);
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
unsigned int CountItems(const struct list* plist) {
    unsigned int count = 0;
    struct node* pnode = plist->head;
    while (pnode != NULL) {
        ++count;
        pnode = pnode->next;
    }
    return count;
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
bool Find(const struct list* plist, struct movie item_to_find, int* index,
    struct movie* item_found,
    bool (*compare_func)(struct movie a, struct movie b)) {

}