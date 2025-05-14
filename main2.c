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
        else
            parent->left = newNode;
    }
    return newNode;
}
Node* deleteBST(Node *root, char x) {
    Node *p = root;
    Node *parent = NULL; //루트가 빈 경우
    while ((p != NULL) && (p->key !=x)){
        parent = p;
        if (p->key < x)
            p=p->right;
        else
            p=p->left;
    }
    if (p == NULL) {
        printf("찾는 노드가 없습니다.\n");
        return root;
    }
    if (p->left == NULL && p->right == NULL) { //차수가 0
        if (parent == NULL){
            if (parent->left == p)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    }
    else if (p->left == NULL || p->right == NULL) {
        Node* child = (p->left != NULL) ? p->left : p->right;
        if (parent != NULL){
            if (parent->left == p)
                parent->left = child;
            else
                parent->right = child;
        }
    }
    else {
        Node *succ_parent = p; //p 삭제할 값.(정확히는 값을 대체)
        //succ_parent succ의 부모 값. - 나중에 succ의 NULL 처리를 위한
        //값을 대체하므로 부모 노드 ,자식 노드 연결을 수정할 필요 없음.
        Node *succ = p->right; // p->right, 우측 서브트리의 시작 값.
        // succ 우측서브트리에서 가장 작은 값
        while (succ->left != NULL) { //가장 작은 값 찾기.
            succ_parent = succ; // succ p(삭제할 값) 하위 노드의 가장 작은 값.
            succ = succ->left; // succ_parent, 가장 작은 값의 부모 값.
        }
        p->key = succ->key; //연결관계는 두고 값만 변경
        if (succ_parent->left == succ)
            succ_parent->left = succ->right; //부모노드의 연결방향에 찾은 노드의 자식을 재결합
        else
            succ_parent->left = succ->right;//부모노드의 연결방향에 찾은 노드의 자식을 재결합
        p = succ;
    }

    free(p);
    return root;
}


void Inorder(Node* root) {
    if (root == NULL)
        return;
    Inorder(root->left);
    printf("%c ", root->key);
    Inorder(root ->right);
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

