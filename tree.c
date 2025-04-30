

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct pair {
    struct node* parent;
    struct node* child;
};

static struct node* MakeNode(const struct item* p_item);
static void AddNode(struct node* new_node, struct node* root);
static void InOrder(const struct node* root, void (*p_func)(struct item item));
static struct pair SeekItem(const struct item* p_item, const struct tree* p_tree);
static void DeleteNode(struct node** ptr);
static void DeleteAllNodes(struct node* ptr);
static struct item* Search(struct node* root, const struct item to_search);

static int(*compare_func)(const struct item item1, const struct item item2) = NULL;

void InitializeTree(struct tree* p_tree, int(comp_func)(const struct item item1, const struct item item2)) {
    p_tree->root = NULL;
    p_tree->size = 0;
    compare_func = comp_func;
}

static void AddNode(struct node* new_node, struct node* root) {
    int comp = compare_func(new_node->item, root->item);

    if (comp ==0) {
        printf("Cannot add a duplicated item.\n"); // 루트 노드와 새 노드가 같다.
        free(new_node);
        return;
    }
    else if (comp < 0 ) { //루트가 더 큼.
        if (root->left == NULL) //비어있으면 추가
            root->left = new_node;
        else //비어있지 않으면 재귀 함수(매개변수(새 노드, 루트->레프트)) 호출을 사용.
            AddNode(new_node, root->left);
    }
    else { // 새 노드가 더 큼
        if (root->right == NULL)// 비어있으면 추가
            root->right = new_node;
        else
            //비어있지 않으면 재귀함수를 사용.
            //addnode함수의 2번째 매개변수(struct node* root)에 root->right를 전달.
            AddNode(new_node, root->right);
    }
}

bool AddItem(const struct item* p_item, struct tree* p_tree) {
    if (TreeIsFull(p_tree)) {
        printf("Cannot add more items.\n");
        return false;
    }

    //아이템으로 새로운 노드1를 만듦
    struct node* new_node = MakeNode(p_item);

    p_tree->size++; // 트리의 숫자 카운트 증가

    if (p_tree->root == NULL) //루트가 비어있으면 루트에 새로운 노드1를 추가
        p_tree->root = new_node;
    else
        AddNode(new_node, p_tree->root);//루트가 있으면 루트 밑에 새 노드1를 추가.

    return true;
}

bool TreeIsEmpty(const struct tree* p_tree) {
    if (p_tree->root == NULL)
        return true;
    else
        return false;
}
bool TreeIsFull(const struct tree* p_tree) {
    if (p_tree->size == MAXITEMS)
        return true;
    else
        return false;
}
int TreeItemCount(const struct tree* p_tree) {
    return p_tree->size;
}
bool InTree(const struct item* p_item, const struct tree* p_tree) {
    return (SeekItem(p_item, p_tree).child == NULL) ? false : true;
}

bool DeleteItem(const struct item* p_item, struct tree* p_tree) {
    struct pair look;
    look = SeekItem(p_item, p_tree);
    if (look.child == NULL) // 차일드가 없다면 노드를 못찾은 것.
        return false;
    if (look.parent == NULL)//부모가 없다는건, 루트 노드라는 것임.
        DeleteNode(&p_tree->root);
    else if(look.parent->left == look.child) // 차일드가 레프트일 경우.
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right); //차일드가 라이트일 경우
    p_tree->size--;
    return true;
}
static void InOrder(const struct node* root, void (*p_func)(struct item item)) {
    if (root ==NULL)
        return;
    InOrder(root->left, p_func);
    (*p_func)(root->item);
    InOrder(root->right, p_func);
}
void Traverse(const struct tree* p_tree, void (*p_func)(struct item item)) {
    if (p_tree != NULL)
        InOrder(p_tree->root, p_func);
}
void DeleteAll(struct tree* p_tree) {
    if (p_tree == NULL)
        return;

    DeleteAllNodes(p_tree->root);
    p_tree->root = NULL;
    p_tree->size = 0;
}
static void DeleteAllNodes(struct node* root) {
    if (root == NULL)
        return;
    struct node* p_right = root->right;
    DeleteAllNodes(root->left);
    free(root);
    DeleteAllNodes(p_right);
}
static struct node* MakeNode(const struct item* p_item) {
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));

    //노드 구조체에는 item, left, right가 있다.
    if (new_node != NULL) {
        new_node->item = *p_item;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    else {
        printf("Malloc() failed.\n");
        exit(1);
    }
    return new_node;
}
static struct item* Search(struct node* root, const struct item key) {
    if (root == NULL)
        return NULL;
    int comp = compare_func(key, root->item);

    if (comp ==0)
        return &root->item;
    else if (comp <0)
        return Search(root->left, key);
    else
        return Search(root->right, key);
}
struct item* TreeSearch(struct tree* tree, const struct item key) {
    return Search(tree->root, key);
}






static struct pair SeekItem(const struct item* p_item, const struct tree* p_tree) {
    struct pair look;
    look.parent = NULL;
    look.child = p_tree->root;

    if (look.child == NULL)
        return look;
    while (look.child != NULL) {
        int comp = compare_func(*p_item, look.child->item);
        if (comp < 0) {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (comp > 0) {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
            break;
    }
}

static void DeleteNode(struct node** ptr) {
    struct node* temp;

    if((*ptr)->left == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ((*ptr)->right == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
            continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }

}