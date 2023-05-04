#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    //char* other;
    struct node* left;
    struct node* right;
} node;

node* newnode(int x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node* insert(node* root,int x)
{
    if(root==NULL)
    {
        root = newnode(x);
    }
    else if(x < root->data)
    {
        root->left = insert(root->left,x);
    }
    else if(x > root->data)
    {
        root->right = insert(root->right,x);
    }
    return root;
}

node* search(node* root, int x)
{
    if(root==NULL)
    {
        return NULL;
    }
    else if(x == root->data)
    {
        return root;
    }
    else if(x < root->data)
    {
        return search(root->left,x);
    }
    else if(x > root->data)
    {
        return search(root->right,x);
    }
    return root;
}

void inOrder(node* root)
{
    if(root)
    {
        inOrder(root->left);
        printf("%d ",root->data);
        inOrder(root->right);
    }
}

int main()
{
    node* root = NULL;
    root = insert(root,5);
    insert(root,3);
    insert(root,7);
    insert(root,4);
    insert(root,12);
    inOrder(root);
    node* s = search(root,12);
    printf("\n");
    if(s)
    {
        printf("FOUND!");
    }
    else
    {
        printf("7aloof");
    }



    return 0;
}
