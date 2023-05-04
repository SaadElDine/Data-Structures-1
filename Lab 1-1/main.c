#include <stdio.h>
#include <stdlib.h>
//DYNAMIC ALLOCATION
int* koko(int n)
{
    //int x[n];
    int* x=malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
        x[i]=i+1;
    return x;
}
typedef struct
{
    char* name;
    int ID;
    float GPA;
}Student;
Student* cnst(int id,char* name,float gpa)
{
    Student* x=malloc(sizeof(Student));
    x->name=malloc(strlen(name)+1);
    strcpy(x->name,name);
    x->ID=id;
    x->GPA=gpa;
     return x;
}
void print(Student* x)
{
    printf("Student ID : %d\n",x->ID);
    printf("Student Name : %s\n",x->name);
    printf("Student GPA : %f",x->GPA);
}
void destruct(Student* x)
{
    free(x->name);
    free(x);
}

 main()
{
    int* x=koko(5);
    for(int i=0;i<5;i++)
    printf("%d\n",x[i]);
    free(x);
//    for(int i=0;i<5;i++)
//    printf("%d\n",x[i]);
    Student* s= cnst(7370,"
                     Saad",3.94);
    print(s);
    destruct(s);
    return 0;
}
