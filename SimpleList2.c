//
// Created by spros on 25. 2. 6.
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
    //운영체제에서 malloc을 해주지 않았을때.
    if (pt == NULL)
        full= true;
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
//새로운 노드를 만들고 item과 next를 설정. prev와 이어주고, 새로운 노드와 prev->next를 이음
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
bool AddItem(struct movie item, struct list* plist) {
    struct node* new_node;
    struct node* search = plist->head;

    new_node = (struct node*)malloc(sizeof(struct node));

    if (new_node ==NULL) {
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
unsigned int WriteAllItems(const struct list* plist, FILE* file, void (*write_an_item_func)(FILE* file, struct movie item)) {
    struct node* pnode = plist->head;
    unsigned int count = 0;
    while (pnode != NULL) {
        (*write_an_item_func)(file, pnode->item);
        pnode = pnode->next;
        count++;
    }
    return count;
}
unsigned int PrintAllItems(const struct list* plist, void (*print_an_item_func)(struct movie item)) {
    struct node* pnode = plist->head;
    unsigned int count = 0;
    while (pnode != NULL) {
        printf("%d : ", count);
        (*print_an_item_func)(pnode->item);
        //void (*print_an_item_func)(struct movie item)의 item과는 다름
        pnode = pnode->next;
        count++;
    }
    return count;
}
void Traverse(const struct list* plist, void (*pfun)(struct movie item)) {
    struct node* pnode = plist->head;
     while (pnode != NULL) {
         (*pfun)(pnode->item);//어떤 함수가 오든 한차례식 반복.
         pnode = pnode->next;
     }
}
bool Find(const struct list* plist, struct movie item_to_find, int* index, struct movie* item_found,
    bool (*compare_func)(struct movie a, struct movie b)) {
    struct node* pnode = plist->head;
    *index =0;
    while (pnode != NULL) {
        if ((*compare_func)(pnode->item, item_to_find) == true) {
            *item_found = pnode->item;
            return true;
        }
        pnode = pnode->next;
        *index += 1;
    }
    return false;
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
void InsertByIndex(struct movie item, struct list* plist, int index) {
    struct node* prev = FindNodeByIndex(plist, index - 1);
    if (prev == NULL)
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
        temp = NULL;
    else
        temp = prev->next->next;
    free(prev->next);
    prev->next = temp;
} // prev->next를 지우는게 목적
// prev->next->next를 temp에 보관
//prev->next 삭제후 prev->next에 temp(prev->next->next)를 대입

void RemoveByIndex(struct list* plist, int index) {
    struct node* prev = FindNodeByIndex(plist, index - 1);
    if (prev == NULL)
        RemoveFirstItem(plist);
    else
        RemoveNextItem(prev);
}
