#include <stdio.h>
#include <stdlib.h>

typedef char data;
typedef struct Node {
    char key;
    struct Node* left;
    struct Node* right;
}Node;

Node* searchBST(Node *root, char x) {
    Node *p = root;
    while (p != NULL) {
        if (p->key == x)
            return p;
        else if (p->key < x)
            p=p->right;
        else
            p=p->left;
    }
    return NULL;
}
Node* insertBST(Node *root, char x) {
    Node *p = root;
    Node *parent = NULL; //루트가 빈 경우

    while (p != NULL) {
        parent = p;
        if (p->key == x) {
            printf("같은 키가 있습니다.\n");
            return p;
        }
        else if (p->key < x)
            p=p->right;
        else
            p=p->left;
    }
    //새 노드 할당
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = x;
    newNode->left = newNode->right = NULL;
    //parent의 자식으로 새 노드 붙이기
    if (parent != NULL) {
        if (parent->key < newNode->key)
            parent->right = newNode;
    }
    return NULL;//새 노드 삽입 작업만 완료하면 되므로 반환값이 필요 없음.
}
Node* deleteBST(Node *root, char x) {
    Node *p = root;
    Node *parent = NULL; //루트가 빈 경우
    while ((p != NULL) && (p->key !=x)){
        parent = p;
        if (p->key == x) {
            printf("같은 키가 있습니다.\n");
            return p;
        }
        else if (p->key < x)
            p=p->right;
        else
            p=p->left;
    }
    if (p == NULL) {
        printf("찾는 노드가 없습니다.\n");
        return root;
    }
    if (p->left == NULL && p->right == NULL) { //차수가 0
        if (parent == NULL)
            root = NULL;
        else {
            if (parent->left == p)
                parent->left == NULL;
            else
                parent->right==NULL;
        }
    }

    free(p);
}


int main(void)
{



    return 0;
}

