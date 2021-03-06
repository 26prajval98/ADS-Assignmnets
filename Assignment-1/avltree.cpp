#include "avltree.h"
#define INF 100000

int max(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}

Node* createNode(int data){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int findHeight(Node* root){
    if(root == NULL)
        return 0;
    else
        return max(findHeight(root->left),findHeight(root->right))+1;
}

int getBalance(Node* root){
    return findHeight(root->left)-findHeight(root->right);
}
int findMin(Node* root){
    if(root == NULL){
        return -INF;
    }
    while(root->left!=NULL){
        root = root->left;
    }
    //printf("test - %d",root->data);
    return root->data;
}

int findMax(Node* root){
    if(root == NULL){
        return INF;
    }
    while(root->right!=NULL){
        root = root->right;
    }
    //printf("test - %d",root->data);
    return root->data;
}

Node* leftRotate(Node* root){
    Node* temp = root;
    root = root->right;
    temp->right = root->left;
    root->left = temp;
    return root;
}

Node* rightRotate(Node* root){
    Node* temp = root;
    root = root->left;
    temp->left = root->right;
    root->right = temp;
    return root;
}

Node* AVLInsert(Node* root, int data){
    if(root == NULL){
        root = createNode(data);
    }
    else{
        if(data>root->data){
            root->right = AVLInsert(root->right,data);
        }
        else{
            root->left = AVLInsert(root->left,data);
        }
    }
    int balance = findHeight(root->left)-findHeight(root->right);
    if(balance>1){
        if(data < root->left->data){
            root = rightRotate(root);
        }
        else{
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
    }
    else if(balance<-1){
        if(data  > root->right->data){
            root = leftRotate(root);
        }
        else{
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
    }
    return root;
}


Node* delNode(Node* root, int data){
    if(root == NULL){
        return root;
    }
    else{
        if(data<root->data){
            root->left = delNode(root->left,data);
        }
        else if(root->data<data){
            root->right = delNode(root->right,data);
        }
        else{
            if(root->left == NULL && root->right == NULL){
                free(root);
                root = NULL;
            }
            else if(root->left == NULL){
                Node* temp = root;
                free(temp);
                root = root->right;
            }
            else if(root->right == NULL){
                Node* temp = root;
                free(temp);
                root = root->left;
            }
            else{
                int min = findMin(root->right);
                root->data = min;
                root->right = delNode(root->right,min);
            }
        }

    }
    if(root!=NULL){
        int balance = findHeight(root->left)-findHeight(root->right);
        if(balance>1){
            int balance2 = getBalance(root->left);
            if(balance2>=0){
                root = rightRotate(root);
            }
            else{
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }
        }
        else if(balance<-1){
            int balance2 = getBalance(root->right);
            if(balance2 <= 0){
                root = leftRotate(root);
            }
            else{
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }
        }
    }
    return root;
}

void display(Node* root){
    if(root!=NULL){
        printf("(%d,%d)",root->data,findHeight(root));
        display(root->left);
        display(root->right);
    }
}