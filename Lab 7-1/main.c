#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    struct node* left;
    struct node* right;
} node;

node* newNode(int x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->left = n->right = NULL;
    return n;
}

node* insert(node* root,int x)
{
    if(!root)
    {
        root = newNode(x);
        return root;
    }
    if(x<root->data)
        root->left = insert(root->left,x);
    else if(x>root->data)
        root->right = insert(root->right,x);
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

node* find_min (node* root)
{
    if(!root)
        return NULL;
    else if (!root->left)
        return root;
    else
        return find_min(root->left);
}

node* deleteBST(node* root,int x)
{
    if(!root)
        return NULL;
    else if (x<root->data)
        root->left = deleteBST(root->left,x);
    else if (x>root->data)
        root->right = deleteBST(root->right,x);
    else
    {
        if(root->left && root->right)
        {
            node* temp = find_min(root->right);
            root->data = temp->data;
            root->right = deleteBST(root->right,temp->data);
        }
        else
        {
            node* temp1 = root;
            if(!temp1->left)
                root = root->right;
            else if(!temp1->right)
                root = root->left;
            free(temp1);
        }
        return root;
    }
}





int main()
{
    node* root =  NULL;
    root = insert(root,5);
    insert(root,3);
    insert(root,6);
    insert(root,7);
    insert(root,10);
    insert(root,1);
    inOrder(root);
    root = deleteBST(root,3);
    printf("\n");
    inOrder(root);
    return 0;
}
