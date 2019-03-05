#include <iostream>
#include "rbtree.h"

RBtree joinRBtrees2to1(RBtree tree1, RBtree tree2){
    node * t1_s = tree1.root;
    node * t2_s = tree2.root;
    node * max = t1_s;
    
    while(max->right != NULL)
        max = max->right;
    
    int val = max->key;

    tree1.del(val);
    
    while(black_height(t1_s) > black_height(t2_s)){
        t1_s = t1_s->right;
    }

    node * p = t1_s->parent;

    node * pp = new node;

    pp->key = val;
    pp->parent = p;
    pp->color = 'r';
    pp->left = t1_s;
    pp->right = t2_s;

    p->right = pp;
    t1_s->parent = pp;
    t2_s->parent = pp;

    RBtree tree3(tree1.root);
    return tree3;
}

RBtree joinRBtrees1to2(RBtree tree1, RBtree tree2){
    node * t1_s = tree1.root;
    node * t2_s = tree2.root;
    node * min = t2_s;
    
    while(min->left != NULL)
        min = min->left;
    
    int val = min->key;

    tree2.del(val);
    
    while(black_height(t1_s) < black_height(t2_s)){
        t2_s = t2_s->left;
    }

    node * p = t2_s->parent;
    node * pp = new node;

    pp->key = val;
    pp->parent = p;
    pp->color = 'r';
    pp->left = t1_s;
    pp->right = t2_s;

    p->left = pp;
    t1_s->parent = pp;
    t2_s->parent = pp;

    RBtree tree3(tree2.root);
    return tree3;
}

// All elements of tree1 is smaller than all elements of tree2
RBtree join_t1st2(RBtree tree1, RBtree tree2){
    node * t1_s = tree1.root;
    node * t2_s = tree2.root;
    if(black_height(t1_s) > black_height(t2_s))
        return joinRBtrees2to1(tree1, tree2);
    else
        return joinRBtrees1to2(tree1, tree2);
}

RBtree join(RBtree tree1, RBtree tree2){
    if(tree1.min() >= tree2.max())
        return join_t1st2(tree2, tree1);
    else if(tree2.min() >= tree1.max())  
        return join_t1st2(tree1, tree2);
    
    RBtree tree3;
    cout << "Condition does not satisfy" << endl;
    return tree3;
}