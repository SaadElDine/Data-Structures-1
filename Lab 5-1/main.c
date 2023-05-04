#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    struct node* next;
} node;

node* new_node(int data)
{
    node* n=malloc(sizeof(node));
    node->data = data;
    node->next = n;
    return n;
}

typedef struct
{
    node* tail;
} linked_listSC

linked_listSC* inititialize_ll()
{
    linked_listSC* l=malloc(sizeof(linked_listSC));
    l->tail = NULL;
    return l;
}

node* gethead(linked_listSC* l)
{
    if(l->tail)
       return l->tail->next;
    return NULL;
}

void insert_begin(linked_listSC* l,int data)
{
    node* n = new_node(data);
    if(l->tail)
    {
        l->tail->next = n;
    }
    else {l->tail = n;}
}

void insert_end(linked_listSC* l,int data)
{
    node* n = new_node(data);
    if(l->tail)
    {
        l->tail->next = n;
        l->tail = n;
    }
    else {l->tail = n;}
}

void delete_begin(linked_listSC* l)
{
    node* temp = NULL;
    if(l->tail)
    {
        temp = l->tail->next;
        l->tail->next = temp->next;
        free(temp);
}

int main()
{




    return 0;
}
