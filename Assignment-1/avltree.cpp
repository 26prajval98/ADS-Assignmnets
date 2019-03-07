#include "avltree.h"
#include <algorithm>
#include <iostream>

using namespace std;

Node *createNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
int findHeight(Node *root)
{
    if (root == NULL)
        return 0;
    else
        return std::max(findHeight(root->left), findHeight(root->right)) + 1;
}

int getBalance(Node *root)
{
    return findHeight(root->left) - findHeight(root->right);
}

int findMini(Node *temp)
{
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp->data;
}

int AVLtree::findMin()
{
    Node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp->data;
}

int AVLtree::findMax()
{
    Node *temp = root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp->data;
}

Node *leftRotate(Node *root)
{
    Node *temp = root;
    root = root->right;
    temp->right = root->left;
    root->left = temp;
    return root;
}

Node *rightRotate(Node *root)
{
    Node *temp = root;
    root = root->left;
    temp->left = root->right;
    root->right = temp;
    return root;
}

Node *AVLtree::insert(Node *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
    }
    else
    {
        if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
        else
        {
            root->left = insert(root->left, data);
        }
    }
    int balance = findHeight(root->left) - findHeight(root->right);
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
        int balance = findHeight(root->left) - findHeight(root->right);
    }
    return root;
}

Node *AVLtree::del(Node *root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    else
    {
        if (data < root->data)
        {
            root->left = del(root->left, data);
        }
        else if (root->data < data)
        {
            root->right = del(root->right, data);
        }
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                free(root);
                root = NULL;
            }
            else if (root->left == NULL)
            {
                Node *temp = root;
                free(temp);
                root = root->right;
            }
            else if (root->right == NULL)
            {
                Node *temp = root;
                free(temp);
                root = root->left;
            }
            else
            {
                int min = findMini(root->right);
                root->data = min;
                root->right = del(root->right, min);
            }
        }
    }
    if (root != NULL)
    {
        int balance = findHeight(root->left) - findHeight(root->right);
        if (balance > 1)
        {
            int balance2 = getBalance(root->left);
            if (balance2 >= 0)
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
            int balance2 = getBalance(root->right);
            if (balance2 <= 0)
            {
                root = leftRotate(root);
            }
            else
            {
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }
        }
    }
    return root;
}

Node *AVLtree::getRoot()
{
    return root;
}

void AVLtree::disp(Node *root)
{
    if (root != NULL)
    {
        printf("(%d,%d)", root->data, findHeight(root));
        disp(root->left);
        disp(root->right);
    }
}