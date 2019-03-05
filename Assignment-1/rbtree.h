#ifndef RB_TREE
#define RB_TREE

#include<iostream>

using namespace std;

struct node
{
    int key;
    node *parent;
    char color;
    node *left;
    node *right;
};

class RBtree
{
    node *root;
    node *q;

  public:
    RBtree()
    {
        root = NULL;
    }
    void insert(int);
    void insertfix(node *);
    void leftrotate(node *);
    void rightrotate(node *);
    void del(int);
    node *successor(node *);
    void delfix(node *);
    void disp();
    void display(node *);
    void search(int);
    int black_height(node *);
};

#endif