#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	int height;
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

	int findHeight(Node *);
	int getBalance(Node *root);
	int findMin(Node *root);
	int findMax(Node *root);
	Node *leftRotate(Node *root);
	Node *rightRotate(Node *root);
	Node *AVLInsert(Node *root, int data);
	Node *delNode(Node *root, int data);
	Node *_get_printf_count_output(Node *);
	void printInorder(Node *root);
};
