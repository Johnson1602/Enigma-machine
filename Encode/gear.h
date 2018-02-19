//
// Created by 徐伟毅 on 2017/3/10.
//

#ifndef THREEPIGS_GEAR_H
#define THREEPIGS_GEAR_H

#include <iostream>
using namespace std;

class Gear;

class Node {
private:
    int leftElement;
    int rightElement;
    Node *link;
    friend class Gear;
};

class Gear {
public:
    Gear() { first = NULL; }                //构造函数
    ~Gear();                                //析构函数
    void initGear(int data[2][26]);
    bool Find(int in, int &x) const;        //查找每个轮子左列与输入下标相同的元素的值
    int Search(int x) const;                //查找每个轮子右列与输入元素值相同的元素的下标
    bool move();                            //每加密一个字母，旋转一下轮子

private:
    Node *first;
};

Gear::~Gear() {
    Node *p;
    first = new Node;           //Important!!!
    while (first) {
        p = first->link;
        delete first;
        first = p;
    }
}

void Gear::initGear(int data[2][26]) {
    Node *p = first, *q;
    for (int i = 0; i < 26; ++i) {
        q = new Node;
        q->leftElement = data[0][i];
        q->rightElement = data[1][i];
        if (i == 0) {
            first = q;
            p = q;
        } else if (i == 25) {
            p->link = q;
            p = q;
            q->link = first;
        } else {
            p->link = q;
            p = q;
        }
    }
}

bool Gear::Find(int in, int &x) const {
    Node *p = first;
    for (int i = 0; i < in; ++i) {
        p = p->link;
    }
    x = p->leftElement;
    return true;
}

int Gear::Search(int x) const {
    Node *p = first;
    int i;
    for (i = 0; p && p->rightElement != x; ++i) {    //从第一个元素开始查找，一直到 p 指向 NULL 或 p 指向的节点的 element 值与 x 相等
        p = p->link;
    }
    if (p) {        //若 p 不指向 NULL，return 当前下标
        return i;
    }
    return -1;
}

bool Gear::move() {
    Node *p = first;
    for (int i = 0; i <25; ++i) {       // first 指向最后一个节点，将链表最后一个元素置为第一个元素
        p = p->link;
    }
    first = p;
    return true;
}

int fgear[2][26] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26},{8, 18, 26, 17, 20, 22, 10, 3, 13, 11, 4, 23, 5, 24, 9, 12, 25, 16, 19, 6, 15, 21, 2, 7, 1, 14}};
int mgear[2][26] = {{26, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25},{20, 1, 6, 4, 15, 3, 14, 12, 23, 5, 16, 2, 22, 19, 11, 18, 25, 24, 13, 7, 10, 8, 21, 9, 26, 17}};
int sgear[2][26] = {{24, 25, 26, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},{21, 3, 15, 1, 19, 10, 14, 26, 20, 8, 16, 7, 22, 4, 11, 5, 17, 9, 12, 23, 18, 2, 25, 6, 24, 13}};

Gear gFast, gMiddle, gSlow;

#endif //THREEPIGS_GEAR_H
