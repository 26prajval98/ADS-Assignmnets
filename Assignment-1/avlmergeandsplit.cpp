#include <iostream>
#include <vector>
#include <fstream>
#include "avltree.h"

using namespace std;

AVLtree joinAVLtrees2to1(AVLtree tree1, AVLtree tree2, int val)
{
    node *t1_s = tree1.root->right;
    node *t1_s_parent = tree1.root;
    node *t2_s = tree2.root;

    while (findHeight(t1_s->right) > findHeight(t2_s))
    {
        t1_s_parent = t1_s_parent->right;
        t1_s = t1_s->right;
    }

    node *pp = t1_s;

    node *p = new node;

    p->data = val;
    p->left = t1_s->right;
    p->right = t2_s;

    pp->right = p;

    if (getBalance(t1_s_parent))
    {
        t1_s_parent = leftRotate(t1_s_parent);
    }

    AVLtree tree3(tree1.root);
    return tree3;
}

AVLtree joinAVLtrees1to2(AVLtree tree1, AVLtree tree2, int val)
{
    if (tree2.root == NULL)
    {
        AVLtree tree3(tree2.root);
        return tree3;
    }

    node *t1_s = tree1.root;
    node *t2_s = tree2.root->left;
    node *t2_s_parent = tree2.root;

    while (findHeight(t1_s) < findHeight(t2_s->left))
    {
        t2_s = t2_s->left;
        t2_s_parent = t2_s_parent->left;
    }

    node *pp = t2_s;

    node *p = new node;

    p->data = val;
    p->left = t1_s;
    p->right = t2_s->left;

    pp->left = p;

    tree1.disp(pp);
    cout << endl;

    if (getBalance(t2_s_parent) > 1)
    {
        rightRotate(t2_s_parent);
    }

    AVLtree tree3(tree2.root);
    return tree3;
}

// All elements of tree1 is smaller than all elements of tree2
AVLtree join_t1st2(AVLtree tree1, AVLtree tree2)
{
    node *t1_s = tree1.root;
    node *t2_s = tree2.root;
    int val = tree1.findMax();

    tree1.root = tree1.del(tree1.getRoot(), val);

    if (findHeight(t1_s) > findHeight(t2_s))
    {
        return joinAVLtrees2to1(tree1, tree2, val);
    }
    else
    {
        return joinAVLtrees1to2(tree1, tree2, val);
    }
}

AVLtree join(AVLtree tree1, AVLtree tree2)
{
    if (tree1.findMin() >= tree2.findMax())
        return join_t1st2(tree2, tree1);
    else if (tree2.findMin() >= tree1.findMax())
        return join_t1st2(tree1, tree2);

    AVLtree tree3;
    cout << "Condition does not satisfy" << endl;
    return tree3;
}

vector<int> read_input(string filename)
{
    ifstream file(filename.c_str());
    vector<int> A;
    int a;
    while (file >> a)
    {
        A.push_back(a);
    }

    return A;
}

int main()
{
    int ch, y = 0;
    vector<int> itr;
    AVLtree tree1;
    string file1 = "tree1.txt", file2 = "tree2.txt";
    itr = read_input(file1);
    for (int i = 0; i < itr.size(); i++)
    {
        tree1.root = tree1.insert(tree1.getRoot(), itr[i]);
    }
    // tree1.insert(7);
    // tree1.insert(3);
    // tree1.insert(18);
    // tree1.insert(10);
    // tree1.insert(22);
    // tree1.insert(8);
    // tree1.insert(11);
    // tree1.insert(26);
    tree1.disp(tree1.getRoot());

    cout << endl;

    AVLtree tree2;
    itr = read_input(file2);
    for (int i = 0; i < itr.size(); i++)
    {
        tree2.root = tree2.insert(tree2.getRoot(), itr[i]);
    }
    // // tree2.insert(100);
    // // tree2.insert(90);
    // // tree2.insert(120);
    tree2.disp(tree2.getRoot());
    cout << endl;

    AVLtree tree3 = join(tree1, tree2);
    cout << "Done" << endl;

    tree3.disp(tree3.getRoot());

    return 0;
}