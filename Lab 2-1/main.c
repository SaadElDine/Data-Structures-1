#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
//Queue
typedef struct
{
    int front,rear,capacity,nb_of_elements;
    int *items;
} Queue;
Queue* initialize(int n)
{
    Queue* s=malloc(sizeof(Queue));
    s->items=malloc(n*sizeof(int));
    s->front=0;
    s->rear=0;
    s->capacity=n;
    s->nb_of_elements=0;
    return s;
}
void enqueue(Queue* s,int x)
{
    s->items[s->rear]=x;
    s->rear=(s->rear+1)%(s->capacity);
    s->nb_of_elements++;
}
int dequeue(Queue* s)
{
    int x=s->items[s->front];
    s->front=(s->front+1)%(s->capacity);
    s->nb_of_elements--;
    return x;
}
int isEmpty(Queue* s)
{
    return s->nb_of_elements == 0 ;
}
int isFull(Queue* s)
{
    return (s->nb_of_elements == s->capacity);
}
void display(Queue* s)
{
    Queue* temp=initialize(999);
    while(!isEmpty(s))
    {
         int x=dequeue(s);
         printf("%d ",x);
         enqueue(temp,x);
    }
    while(!isEmpty(temp))
    {
        enqueue(s,dequeue(temp));
    }
}
int countEven(Queue* s)
{
    int c=0;
    Queue* temp=initialize(1000);
    while(!isEmpty(s))
    {
         int x=dequeue(s);
         if(!(x%2)) c++;
         enqueue(temp,x);
    }
    while(!isEmpty(temp))
    {
        enqueue(s,dequeue(temp));
    }
    return c;
}

int main()
{
    Queue* s=initialize(1000);
    int i;
    for(i=0;i<500;i++)
        enqueue(s,i+1);
    display(s);
    printf("\n");
    printf("%d",countEven(s));
    return 0;
}
