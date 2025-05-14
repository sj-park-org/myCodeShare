#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define SPACING 30

int compare(const struct item first, const struct item second) {
    return strcmp(first.character, second.character);
}
void print_item(struct item item) {
    printf("%s (%s)\n", item.character, item.name);
}
void print2DUtil(struct node* root, int space) {
    space += SPACING;

    if (root == NULL) {
        for (int i = SPACING; i < space; i++)
            printf(" ");
        //space는 재귀함수가 호출될때마다 커지고, 재귀함수에서 탈출하면
        //원래대로 돌아온다.
        printf("NULL");
        return;
        //NULL을 찾을 경우 재귀함수를 종료하는 return
    }
    print2DUtil(root->right, space);
    printf("\n");
    for (int i = SPACING; i<space; i++)
        printf(" ");
    print_item(root->item);
    print2DUtil(root->left, space);

}

void print_node(struct node* root, int level) {
    if (root == NULL)
        return;

    printf("%s (%s) -> ", root->item.character, root->item.name);

    if (root->left == NULL)
        printf("NULL, ");
    else
        printf("%s (%s), ", root->left->item.character, root->left->item.name);
    if (root->right == NULL)
        printf("NULL");
    else
        printf("%s (%s), ", root->right->item.character, root->right->item.name);
    printf("\n");
    print_node(root->left, level +1);
    print_node(root->right, level +1);

}


