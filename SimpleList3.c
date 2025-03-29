
#include "SimpleList3.h"

#include <stdlib.h>


static void CopyToNode(struct item item, struct node* pnode) {
    pnode->item = item;
}

bool AddItem(struct item item, struct list* plist) {
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
unsigned int ReadFromFile(struct list* plist, const char* filename,
    bool (*read_an_item_func)(FILE* file,struct item* item)) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }
    int num;
    if (fscanf(file, "%d%*c", &num) !=1) {
        printf("ERROR: Wrong file format.\n");
        exit(1);
    }
    for (int n = 0; n < num; ++n) {
        struct item new_item;

        const bool flag = read_an_item_func(file, &new_item);
        if (flag == false) {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        else
            AddItem(new_item, plist);
    }
    fclose(file);

    return num;
}
unsigned int FindAndRun(const struct list* plist, struct item item_to_find,
    bool (*compare_func)(struct item a, struct item b),
    void (*func_run)(struct item item)) {

    struct node* pnode = plist->head;

    int count = 0;
    while (pnode != NULL) {
        if ((*compare_func)(pnode->item, item_to_find) == true)
            (*func_run)(pnode->item);
        pnode = pnode->next;
        count += 1;
    }
    return count;
}
unsigned int PrintAllItems(const struct list* plist,
            void (*print_an_item_func)(struct item item)) {

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

void InitializeList(struct list* plist) {
    plist->head = NULL;
}