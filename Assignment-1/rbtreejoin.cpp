#include <iostream>
#include <vector>
#include <fstream>
#include "rbtree.h"

void random()
{
    int A[200];

    for (int i = 0; i < 200; i++)
    {
        A[i] = 0;
    }

    int val;

    ofstream file1("tree1.txt"), file2("tree2.txt");
    int r1 = rand() % 100 + 1, r2 = rand() % 100 + 1;

    for (int i = 0; i < r1; i++)
    {
        val = rand() % 100;
        if (!A[val - 1])
        {
            A[val - 1] = 1;
            file1 << val << endl;
        }
    }

    for (int i = 0; i < r2; i++)
    {
        val = 100 + rand() % 100;
        if (!A[val - 1])
        {
            A[val - 1] = 1;
            file2 << val << endl;
        }
    }

    file1.close();
    file2.close();
}

RBtree joinRBtrees2to1(RBtree tree1, RBtree tree2, int val)
{
    node *t1_s = tree1.root;
    node *t2_s = tree2.root;

    while (black_height(t1_s) > black_height(t2_s))
    {
        t1_s = t1_s->right;
        if (black_height(t1_s) == black_height(t2_s))
        {
            int is_black = 0;
            if (t1_s->color == 'b')
                is_black = 1;
            while (!is_black)
            {
                t1_s = t1_s->right;
                if (t1_s->color == 'b')
                    is_black = 1;
                break;
            }
        }
    }

    node *pp = t1_s->parent;

    node *p = new node;

    p->key = val;
    p->parent = pp;
    p->color = 'r';
    p->left = t1_s;
    p->right = t2_s;

    pp->right = p;
    t1_s->parent = p;
    t2_s->parent = p;

    if (p->color == 'r' && pp->color == 'r')
    {
        pp->color = 'b';
        tree1.leftrotate(pp->parent);
    }

    if (pp == NULL)
        p->color = 'b';

    RBtree tree3(tree1.root);
    return tree3;
}

RBtree joinRBtrees1to2(RBtree tree1, RBtree tree2, int val)
{
    node *t1_s = tree1.root;
    node *t2_s = tree2.root;

    while (black_height(t1_s) <= black_height(t2_s))
    {
        t2_s = t2_s->left;
        if (black_height(t1_s) == black_height(t2_s))
        {
            int is_black = 0;
            if (t2_s->color == 'b')
                is_black = 1;
            while (!is_black)
            {
                t2_s = t2_s->left;
                if (t2_s->color == 'b')
                    is_black = 1;
                break;
            }
        }
    }

    node *pp = t2_s->parent;

    node *p = new node;

    p->key = val;
    p->parent = pp;
    p->color = 'r';
    p->left = t1_s;
    p->right = t2_s;

    pp->left = p;
    t1_s->parent = p;
    t2_s->parent = p;

    if (p->color == 'r' && pp->color == 'r')
    {
        pp->color = 'b';
        tree1.rightrotate(pp->parent);
    }

    if (pp == NULL)
        p->color = 'b';

    RBtree tree3(tree2.root);
    return tree3;
}

// All elements of tree1 is smaller than all elements of tree2
RBtree join_t1st2(RBtree tree1, RBtree tree2)
{
    node *t1_s = tree1.root;
    node *t2_s = tree2.root;
    int val = tree1.max();

    tree1.del(val);

    if (black_height(t1_s) > black_height(t2_s))
    {
        return joinRBtrees2to1(tree1, tree2, val);
    }
    else
        return joinRBtrees1to2(tree1, tree2, val);
}

RBtree join(RBtree tree1, RBtree tree2)
{
    if (tree1.min() >= tree2.max())
        return join_t1st2(tree2, tree1);
    else if (tree2.min() >= tree1.max())
        return join_t1st2(tree1, tree2);

    RBtree tree3;
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
    random();
    int ch, y = 0;
    vector<int> itr;
    RBtree tree1;
    string file1 = "tree1.txt", file2 = "tree2.txt";
    itr = read_input(file1);
    for (int i = 0; i < itr.size(); i++)
        tree1.insert(itr[i]);
    // tree1.insert(7);
    // tree1.insert(3);
    // tree1.insert(18);
    // tree1.insert(10);
    // tree1.insert(22);
    // tree1.insert(8);
    // tree1.insert(11);
    // tree1.insert(26);
    tree1.disp();

    cout << endl;

    RBtree tree2;
    itr = read_input(file2);
    for (int i = 0; i < itr.size(); i++)
        tree2.insert(itr[i]);
    // tree2.insert(100);
    // tree2.insert(90);
    // tree2.insert(120);
    tree2.disp();

    cout << endl;

    RBtree tree3 = join(tree1, tree2);
    cout << "Done" << endl;

    tree3.disp();

    return 0;
}