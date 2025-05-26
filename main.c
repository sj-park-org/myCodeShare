#include "BinaryTreeArray.h"


void preorder(Node root) {
    if (isTreeEmpty(root))
        return;
    printf("%c ", getCurData(root));
    preorder(getLeftChild(root));
    preorder(getRightChild(root));
}
void inorder(Node root) {
    if (isTreeEmpty(root))
        return;
    inorder(getLeftChild(root));
    printf("%c ", getCurData(root));
    inorder(getRightChild(root));
}
void postorder(Node root) {
    if (isTreeEmpty(root))
        return;
    postorder(getLeftChild(root));
    postorder(getRightChild(root));
    printf("%c ", getCurData(root));

}

void main() {
    Node _a = makeRoot('A');
    Node _b = makeLeftChild(_a, 'B');
    Node _c = makeRightChild(_a, 'C');
    Node _d = makeLeftChild(_b, 'D');
    Node _e = makeRightChild(_b, 'E');
    Node _f = makeLeftChild(_c, 'F');
    Node _g = makeRightChild(_c, 'G');

    postorder(_a); printf("\n");


}