#include <stdio.h>
#include <stdlib.h>

typedef char data;
typedef struct Node {
    char key;
    struct Node* left;
    struct Node* right;
} Node;

Node* searchBST(Node* root, char x ) {
    Node *p = root;
    while (p != NULL) {
        if (p->key == x)
            return p;
        else if (p->key <x)
            p=p->right;
        else
            p=p->left;
    }
    return NULL;
}
Node* insertBST(Node *root, char x) {
    Node *p = root;
    Node *parent = NULL;
    while (p!= NULL) {
        parent = p;
        if (p->key == x) {
            printf("같은 키가 있습니다.\n");
            return p;
        }
        else if (p->key < x)
            p= p->right;
        else
            p= p->left;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = x;
    newNode->left = newNode->right = NULL;
    if (parent != NULL) {
        if (parent->key < newNode->key)
            parent->right = newNode;
        else
            parent->left = newNode;
    }
    return newNode;
}

