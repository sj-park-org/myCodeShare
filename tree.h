#pragma once

#include <stdbool.h>

#define TMAX 20

struct item{
    char character[TMAX];
    char name[TMAX];
};

#define MAXITEMS 20

struct node {
    struct item item;
    struct node* left;
    struct node* right;
};

struct tree {
    struct node* root;
    int size; //아이템의 숫자
};

void InitializeTree(struct tree* p_tree, int(comp_func)
    (const struct item item1, const struct item item2));
bool TreeIsEmpty(const struct tree* p_tree);
bool TreeIsFull(const struct tree* p_tree);
int TreeItemCount(const struct tree* p_tree);
bool AddItem(const struct item* p_item, const struct tree* p_tree);
bool InTree(const struct item* p_item, const struct tree* p_tree);
bool DeleteItem(const struct item* p_item, struct tree* p_tree);
void Traverse(const struct tree* p_tree, void (*pfun)(struct item item));
void DeleteAll(struct tree* p_tree);
struct item* TreeSearch(struct tree* tree, const struct item key);

