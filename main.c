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
Node* deleteBST(Node *root, char x) {
    Node* p = root;
    Node* parent = NULL;
    while ((p != NULL) && (p->key != x)) { //x와 일치하는 p값 찾기
        parent = p;
        if (p->key < x)
            p=p->right;
        else
            p=p->left;
    }
    if (p==NULL) {
        printf("찾는 노드가 없습니다.\n");
        return root;
    }
    if (p->left == NULL && p->right == NULL) {
        if (parent != NULL) {//부모가 NULL이 아닐 경우
            if (parent->left == p)
                parent->left = NULL; // 부모와 p의 연결해제
            else
                parent->right = NULL; // 부모와 p의 연결해제
        }
    }
    else if (p->left == NULL || p->right == NULL) {
        Node* child = (p->left != NULL) ? p->left : p->right; //1차수 조건 노드의 자식 찾기.
        if (parent != NULL) {
            if (parent->left == p)
                parent->left = child;
            else
                parent->right = child;
        }
    }
    else {
        Node* succ_parent = p;
        Node* succ = p->right;
        while (succ->left != NULL) {
            succ_parent = succ;
            succ = succ->left;
        }
        p->key = succ->key;
        if (succ_parent->left == succ)
            succ_parent->left = succ->right;
        else
            succ_parent->right = succ->right;
        p=succ;
    }
    free(p);
    return root;
}

void Inorder(Node* root) {
    if (root == NULL)
        return;
    Inorder(root->left);
    printf("%c ", root->key);
    Inorder(root->right);
}

int main(void)
{
    Node *root = insertBST(NULL, 'D');
    insertBST(root, 'I');
    insertBST(root, 'F');
    insertBST(root, 'A');
    insertBST(root, 'G');
    insertBST(root, 'C');
    Inorder(root); printf("\n");

    root = deleteBST(root, 'C');
    Inorder(root); printf("\n");
    return 0;
}
