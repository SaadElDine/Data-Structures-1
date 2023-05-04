#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    struct node* next;
} node;

typedef struct
{
    node* head;
    node* tail;
} linked_list;

linked_list* initialize_linked_list()
{
    linked_list* l = malloc(sizeof(linked_list));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

node* new_node(int x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;
    return n;
}

void display_linked_list(linked_list* l)
{
    node* current = l->head;
    while(current)
    {
        printf("%d ",current->data);
        current = current->next;
    }
}

void insert_node_after(node* n , int x)
{
    if(n)
    {
        node* gdeed = newnode(x);
        gdeed->next = n->next;
        n->next = gdeed;
    }
}

void delete_node_after(node* n)
{
    if(n)
    {
        node* temp = n->next;
        if(temp)
        {
            n->next = temp->next;
            free(temp);
        }
    }
}

node* search_node(node* n, int x)
{
    node* temp = n;
    while(temp)
    {
        if(temp->data == x) return temp;
        temp = temp->next;
    }
    return NULL;
}

void insert_begin(linked_list* l , int x)
{
    node* n = new_node(x);
    if(l->head == NULL)
    {
        l->head = n;
        l->tail = n;
    }
    else
    {
        n->next = l->head;
        l->head = n;
    }

}

void insert_end(linked_list* l , int x)
{
    node* n = new_node(x);
    if(l->head == NULL)
    {
        l->head = n;
        l->tail = n;
    }
    else
    {
        l->tail->next = n;
        l->tail = n;
    }
}

void delete_begin(linked_list* l)
{
    node* temp = NULL;
    if(l->head)
    {
        temp = l->head;
        l->head = l->head->next;
        free(temp);
        if(!l->head) l->tail = NULL;
    }
}

void delete_end(linked_list* l)
{
    if(l->head)
    {
        if(l->head->next == NULL)
        {
            free(l->head);
            l->head = l->tail = NULL;
        }
        else
        {
        node* temp = l->head;
        node* pre_tail = NULL;
        while(temp->next)
        {
            pre_tail = temp;
            temp = temp->next;
        }
        pre_tail->next = NULL;
        l->tail = pre_tail;
        free(temp);
        }
    }
}
















int main()
{
    linked_list* l = initialize_linked_list();
    insert_begin(l,1);
    insert_begin(l,2);
    insert_begin(l,15);
    insert_begin(l,120);
    insert_begin(l,7);
    insert_begin(l,3);
    insert_end(l,13);
    insert_end(l,2);
    insert_end(l,33);
    insert_end(l,40);
    display_linked_list(l);
    delete_end(l);
    printf("\n");
    display_linked_list(l);

    return 0;
}
