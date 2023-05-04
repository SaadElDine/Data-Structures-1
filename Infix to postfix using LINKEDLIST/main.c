#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    float data;
    struct node* next;
} node;

node* new_node(float data)
{
    node* n = malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}

node* next(node* n)
{
    return n ? n->next : n;
}

//typedef struct
//{
//    node* head;
//    node* tail;
//} linked_list_SG;
//
//linked_list_SG* initialize_linked_list()
//{
//    linked_list_SG* l = malloc(sizeof(linked_list_SG));
//    l->head = NULL;
//    l->tail = NULL;
//    return l;
//}
//
//node* get_head(linked_list_SG* l)
//{
//    return l->head;
//}
//
//int is_empty(linked_list_SG* l)
//{
//    return !l->head;
//}
//
//void insert_head(linked_list_SG* l,float data)
//{
//    node* n = new_node(data);
//    if(!is_empty(l))
//    {
//        n->next = get_head(l);
//        l->head = n;
//    }
//    else
//    {
//        l->head = l->tail = n;
//    }
//}
//
//float delete_head(linked_list_SG* l)
//{
//    float x;
//    node* temp = NULL;
//    if(!is_empty(l))
//    {
//        temp = get_head(l);
//        l->head = l->head->next;
//        x = temp->data;
//        free(temp);
//        if(is_empty(l))
//        {
//            l->tail = NULL;
//        }
//    }
//    return x;
//}


typedef struct
{
    node* top;
} Stack;

Stack* initialize_stack()
{
    Stack* s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack* s, float data)
{
    node* n = new_node(data);
    n->next = s->top;
    s->top = n;
}

float pop(Stack *s)
{
    node* n = s->top;
    int x = n->data;
    s->top = n->next;
    free(n);
    return x;
}

float peek(Stack* s)
{
    node* n = s->top->next;
    int x = n->data;
    free(n);
    return x;
}

int isEmpty(Stack* s)
{
    return (s->top == NULL) ;

}

///if the user entered the exp without spaces this fn should be used
//char* Handle_infix(char* infix)
//{
//    char str[100],current_ch;
//    int index = 0;
//    while(current_ch = *infix++)
//    {
//        if(current_ch == '(' || current_ch == ')')
//        {
//            str[index++] = ' ';
//            str[index++] = current_ch;
//            str[index++] = ' ';
//        }
//        else
//        {
//            if(isalnum(current_ch))
//                str[index++] = current_ch;
//            else
//            {
//                str[index++] = ' ';
//                str[index++] = current_ch;
//                str[index++] = ' ';
//            }
//        }
//    }
//    str[index++] = '\0';
//    char* handled_infix = malloc(strlen(str)+1);
//    strcpy(handled_infix,str);
//    return handled_infix;
//}

float calculate(float x,float y,char op)
{
    switch(op)
    {
    case '+':
        return x+y;
        break;
    case '-':
        return x-y;
        break;
    case '*':
        return x*y;
        break;
    case '/':
        return x/y;
        break;
    case '^':
        return pow(x,y);
        break;
    }
}

int priority(char operation)
{
    switch(operation)
    {
    case '(' :
        return 3;
        break;
    case '^' :
        return 2;
        break;
    case '*' :
        return 1;
        break;
    case '/' :
        return 1;
        break;
    default  :
        return 0;
        break;
    }
}

char* infixTopostfix(char *infix)
{
    char* postfix = malloc(2000);
    postfix[0] = '\0';
    int index = 0, n ;
    Stack* s = initialize_stack();
    char* tok = strtok(infix," ");
    while(tok)
    {
        if(isdigit(tok[0]) || strlen(tok)>1)
        {
            strcat(postfix,tok);
            n = strlen(postfix);
            postfix[n] = ' ';
            postfix[n+1] = '\0';

        }
        else if(isEmpty(s))
            push(s,tok[0]);
        else if(tok[0] == ')')
        {
            while(peek(s)!='(')
            {
                n = strlen(postfix);
                postfix[n] = pop(s);
                postfix[n+1] = ' ';
                postfix[n+2] = '\0';
            }
            pop(s);
        }
        else
        {
            while(!isEmpty(s) && priority(peek(s)) >= priority(tok[0]) && peek(s) != '(')
            {
                n = strlen(postfix);
                postfix[n] = pop(s);
                postfix[n+1] = ' ';
                postfix[n+2] = '\0';
            }
            push(s,tok[0]);
        }
        tok = strtok(NULL," ");
    }
    while(!isEmpty(s))
    {
        n = strlen(postfix);
        postfix[n] = pop(s);
        postfix[n+1] = ' ';
        postfix[n+2] = '\0';
    }
    n = strlen(postfix);
    postfix[n+1] = '\0';
    return postfix;
}

float evaluatePostfix(char* postfix)
{
    Stack* s = initialize_stack();
    char* tok = strtok(postfix," ");
    while(tok)
    {
        if(isdigit(tok[0]) || strlen(tok)>1 )
            push(s,atof(tok));
        else
        {
            float x = pop(s);
            float y = pop(s);
            float z = calculate(y,x,tok[0]);
            push(s,z);
        }
        tok = strtok(NULL," ");
    }
    return pop(s);
}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main()
{
    char infixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        char* postfix = infixTopostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
