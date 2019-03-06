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

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

class AVLtree
{
  public:
	Node *root;
	AVLtree()
	{
		root = NULL;
	};

	AVLtree(Node *t)
	{
		root = t;
	}

	Node *insert(Node *root, int data);
	Node *del(Node *root, int data);
	Node *getRoot();
	int findMin();
	int findMax();
	void disp(Node *root);
};

namespace M
{
	int findMin(Node *);
}

int findHeight(Node *);
int getBalance(Node *root);
Node *leftRotate(Node *root);
Node *rightRotate(Node *root);

#endif