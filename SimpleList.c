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
        //struct movie** item은 복사가 두번 발생.
        //1. 함수의 매개변수로 전달 2. pnode->item의 복사(원본전달을 위해 &pnode->item을 사용)
        return true;
    }

}

