#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 1000
typedef struct
{
    int items[MaxSize];
    int top;
} Stack;
Stack* initialize()
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
void display(Stack*s)
{
    Stack *temp=initialize();
    while(!is_empty(s))
    {
        int x=pop(s);
        printf("%d ",x);
        push(temp,x);
    }
    while(!is_empty(temp))
        push(s,pop(temp));
    printf("\n");
}
int countEven(Stack* s)
{
    Stack* temp=initialize();
    int x,c=0;
    while(!is_empty(s))
    {
        x=pop(s);
        if(!(x%2))
            c++;
        push(temp,x);

    }
    while(!is_empty(temp))
    {
        push(s,pop(temp));
    }
    return c;
}
char* reverse_string(char *str)
{
    Stack *string=initialize();
    int n=strlen(str);
    char *reversed_string=malloc(n+1);
    for(int i=0; i<n; i++)
        push(string,str[i]);
    int j;
    for(j=0; j<n; j++)
        reversed_string[j]=pop(string);
    reversed_string[j]='\0';
    return reversed_string;
}
int count(Stack*s)
{
    int c=0;
    Stack*temp=initialize();
    while(!is_empty(s))
    {
        c++;
        push(temp,pop(s));
    }
    while(!is_empty(temp))
        push(s,pop(temp));
    return c;
}
int check_sorted(Stack* s)
{
    int x,y,z,a,b;
    Stack* temp=initialize();
    if(count(s)==1) return 1;
    x=pop(s);
    y=pop(s);
    a=x;
    b=y;
    push(temp,x);
    push(temp,y);
    if(a>b)
    {
        while(!is_empty(s))
        {
            z=pop(s);
            if(y<z)
            {
                push(temp,z);
                while(!is_empty(temp))
                    push(s,pop(temp));
                return 0;
            }
            push(temp,z);
            y=z;
        }
        while(!is_empty(temp))
            push(s,pop(temp));
        return 1;
    }
    else
    {
        while(!is_empty(s))
        {
            z=pop(s);
            if(y>z)
            {
                push(temp,z);
                while(!is_empty(temp))
                    push(s,pop(temp));
                return 0;
            }
            push(temp,z);
            y=z;
        }
        while(!is_empty(temp))
            push(s,pop(temp));
        return 1;
    }
}
int is_prime(int x)
{
    int p=1;
    if (!x || x==1)
        return 0;
    for (int i=2; i<= x/2; i++)
    {
        if (x%i==0)
            return 0;
    }
    return 1;
}
void delete_nonprime(Stack* s)
{
    Stack* temp=initialize();
    int x;
    while(!is_empty(s))
    {
        x=pop(s);
        if(is_prime(x))
            push(temp,x);
    }
    while(!is_empty(temp))
        push(s,pop(temp));
    printf("Stack After Removing Non Primes :\n");
    display(s);
}
void sort(Stack* s)
{
    if(count(s)==0) return;
    if(check_sorted(s))
    {
        printf("' The Stack Enterred Is Already Sorted ! '\n");
        return;
    }
    Stack* temp=initialize();
    while(!is_empty(s))
    {
        int x=pop(s);
        while(!is_empty(temp) && peek(temp)>x)
           push(s,pop(temp));
        push(temp,x);
    }
    while(!is_empty(temp))
        push(s,pop(temp));
    printf("' Stack After Being Sorted: '\n");
    display(s);
}
void merge_sort(Stack* a,Stack* d)
{
    Stack* mergesorted=initialize();
    while(!is_empty(a) && !is_empty(d))
        {
            if(peek(a)<peek(d)) push(mergesorted,pop(a));
            else if(peek(a)>peek(d)) push(mergesorted,pop(d));
            else {push(mergesorted,pop(a)); push(mergesorted,pop(d));}
        }
    while(!is_empty(a)) push(mergesorted,pop(a));
    while(!is_empty(d)) push(mergesorted,pop(d));
    Stack* minontop=initialize();
    while(!is_empty(mergesorted)) push(minontop,pop(mergesorted));
    printf("Two Stacks After Merge 'min on top' :\n");
    display(minontop);
}
int main()
{
    printf("**************** Welcome To My Program! ****************\n\n");
    char str[1000];
    printf("String : %s\n","qwertyuiop2mnbvcxz");
    printf("The Reversed String: %s\n",reverse_string("qwertyuiop2mnbvcxz"));
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    Stack* s=initialize();
    Stack* a=initialize();
    Stack* d=initialize();
    Stack* m=initialize();
    Stack* me1=initialize();
    Stack* me2=initialize();
    printf("There are 4 Stacks S,D,A,M that will be used as shown:\n");
    for(int i=0; i<100; i++)
        push(s,i+1);
    printf("__________________________________________________________________\n");
    printf("Stack S:\n");
    display(s);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("Number Of Even Numbers In Stack S = %d\n",countEven(s));
    int x=check_sorted(s);
    if(x) printf("Stack S Is Sorted!\n");
    else  printf("Stack S Is NOT Sorted!\n");
    printf("Calling Sort Fn The outuput will be : ");
    sort(s);
    delete_nonprime(s);
    printf("__________________________________________________________________\n");
    for(int i=100; i>0; i-=2)
        push(d,i);
    printf("Stack D:\n");
    display(d);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("Number Of Even Numbers In Stack D = %d\n",countEven(d));
    x=check_sorted(d);
    if(x) printf("Stack S Is Sorted!\n");
    else  printf("Stack S Is NOT Sorted!\n");
    printf("Calling Sort Fn The outuput will be : ");
    sort(d);
    delete_nonprime(d);
    printf("__________________________________________________________________\n");
    for(int i=99; i>0; i-=2)
        push(a,i);
    printf("Stack A:\n");
    display(a);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("Number Of Even Numbers In Stack A = %d\n",countEven(a));
    x=check_sorted(a);
    if(x) printf("Stack S Is Sorted!\n");
    else  printf("Stack S Is NOT Sorted!\n");
    printf("Calling Sort Fn The outuput will be : ");
    sort(a);
    delete_nonprime(a);
    printf("__________________________________________________________________\n");
     push(m,1);
     push(m,100);
     push(m,2);
     push(m,60);
     push(m,3);
     push(m,10);
     push(m,9);
     push(m,5);
     push(m,3000);
     printf("Stack M:\n");
     display(m);
     printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
     printf("Number Of Even Numbers In Stack M = %d\n",countEven(m));
     x=check_sorted(m);
     if(x) printf("Stack S Is Sorted!\n");
     else  printf("Stack S Is NOT Sorted!\n");
     printf("Calling Sort Fn The outuput will be : ");
     sort(m);
     delete_nonprime(m);
     printf("__________________________________________________________________\n");
     printf("The Following Sorted Stacks 'min on top' Will Be merged as shown:\n");
     push(me1,50);push(me1,40);push(me1,30);push(me1,20);push(me1,10);
     printf("Stack 1:\n");
     display(me1);
     printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
     push(me2,10);push(me2,7);push(me2,6);push(me2,5);push(me2,2);push(me2,0);
     printf("Stack 2:\n");
     display(me2);
     printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
     printf("Calling The Merge Fn to Merge The 2 Stacks \nThe Output Will Be:\n");
     merge_sort(me1,me2);
     return 0;
}

