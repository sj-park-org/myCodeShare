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

}