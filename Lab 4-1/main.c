#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int data;
    struct node* next;
    struct node* previous;
} node;

typedef struct
{
    node* head;
    node* tail;
} linked_list;

node* new_node(int x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;
    n->previous = NULL;
    return n;
}

linked_list* initialize_linked_list()
{
    linked_list* l = malloc(sizeof(linked_list));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void insert_begin_dll(linked_list* l , int x)
{
    node* n = new_node(x);
    if(!l->head)
        l->head = l->tail = n;
    else
    {
        n->next = l->head;
        l->head->previous = n;
        l->head = n;
    }
}

void insert_end_dll(linked_list* l , int x)
{
    node* n = new_node(x);
    if(!l->head)
        l->head = l->tail = n;
    else
    {
        l->tail->next = n;
        n->previous = l->tail;
        l->tail = n;
    }
}

void delete_begin_dll(linked_list* l)
{
    if(l->head != NULL)
    {
        node* temp = l->head;
        l->head = l->head->next;
        free(temp);
        if(l->head == NULL) l->tail = NULL;
        else
        {
            l->head->previous = NULL;
        }
    }
}

void delete_end_dll(linked_list* l)
{
    if(l->head != NULL)
    {
        node* temp = l->tail;
        l->tail = l->tail->previous;
        free(temp);
        if(l->tail == NULL) l->head = NULL;
        else
        {
            l->tail->next = NULL;
        }
}
}

void display_linked_list_dll(linked_list* l)
{
    node* temp = l->head;
    while(temp)
    {
        printf("%d ",temp->data);
        temp = temp ->next;
    }
}

void display_linked_list_dll_reversed(linked_list *l)
{
    node* temp = l->tail;
    while(temp)
    {
        printf("%d ",temp->data);
        temp = temp ->previous;
    }
}

int main()
{
    linked_list* l = initialize_linked_list(l);
    insert_begin_dll(l,1);
    insert_begin_dll(l,2);
    insert_begin_dll(l,3);
    insert_begin_dll(l,4);
    insert_begin_dll(l,5);
    insert_end_dll(l,6);
    insert_end_dll(l,7);
    insert_end_dll(l,8);
    insert_end_dll(l,9);
    insert_end_dll(l,10);
    display_linked_list_dll(l);
    printf("\n");
    display_linked_list_dll_reversed(l);
    printf("\n");
    delete_begin_dll(l);
    display_linked_list_dll(l);
    printf("\n");
    delete_end_dll(l);
    display_linked_list_dll(l);



    return 0;
}
