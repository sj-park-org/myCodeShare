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
        for (int i = SPACING; i< space; i++)
            printf(" ");
        printf("NULL");
        return;
    }

    print2DUtil(root->right, space);
    printf("\n");
    for (int i = SPACING; i< space;i++)
        printf(" ");
    print_item(root->item);
    print2DUtil(root->left, space);
}

void print_node(struct node* root, int level) {
    if (root==NULL)
        return;

    printf("%s (%s) -> ", root->item.character, root->item.name);

    if (root->left == NULL)
        printf("NULL, ");
    else
        printf("%s (%s), ", root->left->item.character, root->left->item.name);
    if(root->right ==NULL)
        printf("NULL");
    else
        printf("%s (%s)", root->right->item.character, root->right->item.name);

    printf("\n");
    print_node(root->left, level+1);
    print_node(root->right, level+1);
}
void print_tree(struct tree* p_tree) {
    printf("\n--------------------\n");
    Traverse(p_tree, print_item);
    printf("\n--------------------\n");
    print2DUtil(p_tree->root, 0);
    printf("\n--------------------\n");
    print_node(p_tree->root, 0);
}

int main(void)
{
    struct item items[] = {
        {"Iron Man", "Tony Stark"},
        {"Thor","Thor Odinson"},
        {"Ant-Man", "Hank Pym"},
        {"Wasp", "Janet van Dyne"},
        {"Hulk", "Bruce Banner"},
        {"Captain America", "Steve Rogers"},
        {"Scarlet Witch", "Wanda Maximoff"},
        {"Black Widow", "Natasha Romanoff"},
        {"Dr. Strange", "Stephen Strange"},
        {"Daredevil","Matthew Murdock"},
        {"Punisher", "Frank Castle"},
        {"Batman", "Bruce Wayne"}
    };
    int n = sizeof(items) / sizeof(items[0]);

    struct tree tree;
    InitializeTree(&tree, &compare);

    for (int i = 0; i < n; ++i)
        AddItem(&items[i], &tree);
    AddItem(&items[2], &tree);
    print_tree(&tree);

    struct item key = {"Punisher", ""};
    struct item* result = TreeSearch(&tree, key);
    if (result == NULL)
        printf("\nSearch failed.\n");
    else
        printf("\n%s is the %s\n", result->name, result->character);
    {
        struct item key = {"Iron Man", ""};
        DeleteItem(&key, &tree);
        print_tree(&tree);
    }



    return 0;
}

