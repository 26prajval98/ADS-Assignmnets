#ifndef AVL_TREE
#define AVL_TREE

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
} Node;

int findHeight(Node *root);
int getBalance(Node *root);
int findMin(Node *root);
int findMin(Node *root);
Node *AVLInsert(Node *root, int data);
Node *delNode(Node *root, int data);
void display(Node *root);

#endif