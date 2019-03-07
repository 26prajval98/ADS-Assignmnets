#include <iostream>
#include <vector>
#include <fstream>
#include "avltree.h"

using namespace std;

typedef struct splt
{
    Node *tree1;
    Node *tree2;
} Split;

Node *AVLise(Node *root, int data)
{
    int balance = getBalance(root);
    if (balance > 1)
    {
        if (data < root->left->data)
        {
            root = rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
    }
    else if (balance < -1)
    {
        if (data > root->right->data)
        {
            root = leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
    }
    return root;
}

// All elements of tree1 is smaller than all elements of tree2
Node *jointrees(Node *tree1, Node *tree2, int val)
{
    if (findHeight(tree1) > findHeight(tree2))
    {
        tree1->right = jointrees(tree1->right, tree2, val);
        return AVLise(tree1, val);
    }
    else if (findHeight(tree1) > findHeight(tree2))
    {
        tree2->left = jointrees(tree1, tree2->left, val);
        return AVLise(tree2, val);
    }
    else
    {
        Node *temp = new Node;
        temp->data = val;
        temp->left = tree1;
        temp->right = tree2;

        return temp;
    }
}

Node *join(Node *tree1, Node *tree2)
{
    Node *t1_s = tree1;
    Node *t2_s = tree2;
    int val;

    if (tree1 != NULL)
    {
        val = findMax(tree1);
        tree1 = delNode(tree1, val);
    }
    else if (tree2 != NULL)
    {
        val = findMin(tree2);
        tree2 = delNode(tree2, val);
    }
    else
    {
        return NULL;
    }

    // Assuming tree1 has all elements smaller than tree2
    Node *tree3 = jointrees(tree1, tree2, val);

    return tree3;
}

Split *split(Node *tree, int key)
{
    Split *temp = new Split;
    temp->tree1 = NULL;
    temp->tree2 = NULL;

    if (tree == NULL)
    {
        return temp;
    }

    if (tree->data < key)
    {
        int val = tree->data;
        Node *temp_tree = tree->left;
        temp = split(tree->right, key);
        temp_tree = AVLInsert(temp_tree, val);
        temp->tree1 = join(temp_tree, temp->tree1);
        return temp;
    }
    else if (tree->data > key)
    {
        int val = tree->data;
        Node *temp_tree = tree->right;
        temp = split(tree->left, key);
        temp_tree = AVLInsert(temp_tree, val);
        temp->tree2 = join(temp_tree, temp->tree2);
        return temp;
    }
    else
    {
        temp->tree1 = tree->left;
        temp->tree2 = tree->right;
        display(temp->tree1);
        cout << endl;
        return temp;
    }
}

Split * splitinto(Node * tree, int val){
    tree = AVLInsert(tree, val);
    // display(tree);
    cout << endl;
    return split(tree, val);
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
    Node *tree1 = NULL;
    string file1 = "tree1.txt", file2 = "tree2.txt";
    itr = read_input(file1);
    for (int i = 0; i < itr.size(); i++)
    {
        tree1 = AVLInsert(tree1, itr[i]);
    }
    // tree1.insert(7);
    // tree1.insert(3);
    // tree1.insert(18);
    // tree1.insert(10);
    // tree1.insert(22);
    // tree1.insert(8);
    // tree1.insert(11);
    // tree1.insert(26);
    display(tree1);

    cout << endl;

    Node *tree2 = NULL;
    itr = read_input(file2);
    for (int i = 0; i < itr.size(); i++)
    {
        tree2 = AVLInsert(tree2, itr[i]);
    }
    // tree2.insert(100);
    // tree2.insert(90);
    // tree2.insert(120);
    display(tree2);
    cout << endl;

    Node *tree3 = join(tree1, tree2);
    cout << "Done" << endl;

    display(tree3);
    cout << endl;
    cout << endl;

    Split * splittrees = splitinto(tree3, 100);

    display(splittrees->tree1);
    cout << endl;

    display(splittrees->tree2);
    cout << endl;

    return 0;
}