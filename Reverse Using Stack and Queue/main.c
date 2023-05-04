#include <stdio.h>
#include <stdlib.h>
#define MaxSize 1000
typedef struct
{
    int items[MaxSize];
    int top;
} Stack;
typedef struct
{
    int front,rear,capacity,nb_of_elements;
    int *items;
} Queue;
Stack* initialize_stack()
{
    Stack* s=malloc(sizeof(Stack));
    s->top=0;
    return s;
}
void push(Stack* s,int x)
{
    s->items[s->top++]=x;
}
int pop(Stack* s)
{
    return s->items[--s->top];
}
int peek(Stack* s)
{
    return s->items[s->top-1];
}
int is_empty(Stack* s)
{
    if(s->top==0)
        return 1;
    return 0;
}
int is_full(Stack* s)
{
    if(s->top==MaxSize)
        return 1;
    return 0 ;
}
Queue* initialize(int capacity)
{
    Queue* s=malloc(sizeof(Queue));
    s->items=malloc(capacity*sizeof(int));
    s->front=0;
    s->rear=0;
    s->capacity=capacity;
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
int count(Queue* s)
{
    return s->nb_of_elements;
//    int c=0;
//    Queue* temp=initialize(1000);
//    while(!isEmpty(s))
//    {
//        int x=dequeue(s);
//        c++;
//        enqueue(temp,x);
//    }
//    while(!isEmpty(temp))
//    {
//        enqueue(s,dequeue(temp));
//    }
//    return c;
}
void display(Queue* s)
{
    Queue* temp=initialize(count(s));
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
    printf("\n");
}
int countEven(Queue* s)
{
    int c=0;
    Queue* temp=initialize(count(s));
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
int get_max_value(Queue* s)
{
    Queue* temp=initialize(count(s));
    int max=dequeue(s);
    enqueue(temp,max);
    while(!isEmpty(s))
    {
        int y = dequeue(s);
        if(y > max)  max = y;
        enqueue(temp,y);
    }
    while(!isEmpty(temp))
    {
        enqueue(s,dequeue(temp));
    }
    return max;
}
void swap_front_rear(Queue* s)
{
    Queue* temp=initialize(count(s));
    int x=dequeue(s);
    int n=count(s)-2;
    for(int i=0; i<n; i++)
    {
        enqueue(temp,dequeue(s));
    }
    enqueue(temp,dequeue(s));
    while(!isEmpty(temp))
        enqueue(s,dequeue(temp));
    enqueue(s,x);
    printf("After Swapping the value of the head and the tail:\n");
    display(s);
}
void insert(Queue* s,int x,int index)
{
    Queue* temp=initialize(count(s)+1);
    int i=0,p=0;
    while(!isEmpty(s))
    {
        enqueue(temp,dequeue(s));
        i++;
        if(i==index)
        {
            enqueue(temp,x);
            p=1;
        }
    }

    while(!isEmpty(temp))
        enqueue(s,dequeue(temp));
    if(!p) enqueue(s,x);
    printf("After inserting the %d in index %d:\n",x,index);
    display(s);
}
Queue* reverse_odd(Queue* s)
{
    Stack* onlyOdd=initialize_stack();
    Queue* temp=initialize(count(s));
    while(!isEmpty(s))
    {
        int x=dequeue(s);
        if(x%2)
        {
            push(onlyOdd,x);
            enqueue(temp,x);
        }
        else enqueue(temp,x);
    }
    while(!isEmpty(temp))
    {
        int y=dequeue(temp);
        if(y%2) enqueue(s,pop(onlyOdd));
        else enqueue(s,y);
    }
    return s;
}
void reverse_Queue(Queue* s,int k)
{
    char file_name[100];
    printf("Enter The File Name That Contain The Queue You Want to Modify:\n");
    gets(file_name);
    Queue* temp=initialize(1000);
    Stack* temps=initialize_stack();
    FILE* f=fopen(file_name,"r");
    if(!f)
    {
        printf("Error Occurs While Oppening the file!!\n");
        exit(-1);
    }
    int x,c=0;
    while(!feof(f))
    {
        fscanf(f,"%d",&x);
        c++;
        enqueue(s,x);
    }
    fclose(f);
    printf("Original Queue Found In Your File:\n");
    display(s);
    if(c==1)
    {
        printf("Your File Contain Only One Element So It Will Remain the same!!\n");
        return;
    }
    for(int i=0; i<k; i++)
        push(temps,dequeue(s));
    while(!isEmpty(s)) enqueue(temp,dequeue(s));
    while(!is_empty(temps)) enqueue(s,pop(temps));
    while(!isEmpty(temp)) enqueue(s,dequeue(temp));
    printf("Reversing The First %dth Elements, The Queue Will be Saved in %s AS SHOWN:\n",k,file_name);
    display(s);
    FILE* f1=fopen(file_name,"w");
    if(!f1)
    {
        printf("Error Occurs!!\n");
        exit(-1);
    }
    int n=count(s)-1;
    for(int i=0; i<n; i++)
        fprintf(f1,"%d ",dequeue(s));
    fprintf(f1,"%d",dequeue(s));
    fclose(f1);
}
int main()
{
    printf("**************** Welcome To My Program! ****************\n\n");
    Queue* s=initialize(1000);
    Queue* a=initialize(1000);
    Queue* b=initialize(1000);
    Queue* c=initialize(1000);
    printf("Queue S:\n");
    enqueue(s,1);
    enqueue(s,2);
    enqueue(s,1000);
    enqueue(s,100);
    enqueue(s,50);
    enqueue(s,20000);
    enqueue(s,50);
    enqueue(s,7);
    enqueue(s,9);
    enqueue(s,222);
    enqueue(s,3333);
    display(s);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("Number of even numbers in the queue enterred = %d\n",countEven(s));
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("Max Value in the queue enterred = %d\n",get_max_value(s));
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    swap_front_rear(s);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("_______________________________________________________________________ \n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("Queue A:\n");
    enqueue(a,14);
    enqueue(a,13);
    enqueue(a,17);
    enqueue(a,8);
    enqueue(a,4);
    enqueue(a,10);
    enqueue(a,11);
    enqueue(a,4);
    enqueue(a,15);
    enqueue(a,18);
    enqueue(a,19);
    display(a);
    insert(a,3,5);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    c=reverse_odd(a);
    printf("After Reversing The Odd Numbers In Your Queue, It Will Be:\n");
    display(c);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("_______________________________________________________________________ \n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    reverse_Queue(b,5);
    printf("\n************************************** END *************************************");
    return 0;
}
