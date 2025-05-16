//
// Created by spros on 25-05-16 (금).
//

#ifndef ADT_H
#define ADT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef char DATA;

typedef int Node;


Node makeRoot(DATA data);
Node makeLeftChild(Node cur, DATA data);
Node makeRightChild(Node cur, DATA data);

DATA getCurData(Node cur);
Node getLeftChild(Node cur);
DATA getLeftChildData(Node cur);
Node getRightChild(Node cur);
DATA getRightChildData(Node cur);
int isTreeEmpty(Node root);





#endif //ADT_H
