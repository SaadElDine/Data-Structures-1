//بسم الله الرحمن الرحيم
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char* word;
    struct node* left;
    struct node* right;
} node;

node* new_node(char* word)
{
    node* n = malloc(sizeof(node));
    n->word = malloc(strlen(word)+1);
    strcpy(n->word,word);
    n->left = n->right = NULL;
    return n;
}

node* insert(node* root, char* word)
{
    if(!root)
        root = new_node(word);
    else if(strcasecmp(word,root->word) < 0)
        root->left = insert(root->left,word);
    else if(strcasecmp(word,root->word) > 0)
        root->right = insert(root->right,word);
    return root;
}

void inOrder(node* root)
{
    if(root)
    {
        inOrder(root->left);
        printf("%s\n",root->word);
        inOrder(root->right);
    }
}

node* searchREC(node*root, char* word)
{
    if(root==NULL)
        return NULL;
    else if(!(strcasecmp(word,root->word)))
        return root;
    else if(strcasecmp(word,root->word) < 0)
        return searchREC(root->left,word);
    else
        return searchREC(root->right,word);
}

node* pre_node(node* root, char* word)
{
    node* temp = root;
    node* pre = NULL;
    while(temp)
    {
        if(strcasecmp(word,temp->word) < 0)
        {
            pre = temp;
            temp = temp->left;
        }
        else if(strcasecmp(word,temp->word) > 0)
        {
            pre = temp;
            temp = temp->right;
        }
    }
    return pre;
}

node* min_word(node* root)
{
    if(!root)
        return NULL;
    if(!root->left)
        return root;
    else
        return min_word(root->left);
}

node* max_word(node* root)
{
    if(!root)
        return NULL;
    if(!root->right)
        return root;
    else
        return max_word(root->right);
}

node* inOrderSuccessor(node* root, char* word)
{
    if (!root)
        return NULL;
    node *successor = NULL;
    node *current  = root;
    while(current && strcasecmp(current->word, word))
    {
        if(strcasecmp(current->word, word) > 0)
        {
            successor = current;
            current= current->left;
        }
        else current = current->right;
    }
    if (!current)
        return NULL;
    if(current && current->right)
        successor = min_word(current->right);
    return successor;
}

node* inOrderPredeccessor(node* root, char* word)
{
    if (!root)
        return NULL;
    node *deccessor = NULL;
    node *current  = root;
    while(current && strcasecmp(current->word, word))
    {
        if(strcasecmp(current->word, word) < 0)
        {
            deccessor = current;
            current= current->right;
        }
        else current = current->left;
    }
    if (!current)
        return NULL;
    if(current && current->left)
        deccessor = max_word(current->left);
    return deccessor;
}

void check_correctness(node* root, char* word)
{
    if(searchREC(root,word))
        printf("%s - Correct!\n",word);
    else
    {
        node* leaf = pre_node(root,word);
        printf("%s - Incorrect! -> Suggestions : ",word);
        printf(" %s  -  ",leaf->word);
        node* successor = inOrderSuccessor(root,leaf->word);
        if(successor)
            printf(" %s  -  ",successor->word);
        node* deccessor = inOrderPredeccessor(root,leaf->word);
        if(deccessor)
            printf(" %s \n",deccessor->word);
    }
}

int size(node* root)
{
    if(!root)
        return 0;
    return 1+size(root->left)+size(root->right);
}

int max(int x,int y)
{
    return x>y?x:y;
}

int height(node*root)
{
    if(root==NULL)
        return -1;
    else
        return 1+max(height(root->left),height(root->right));
}

node* load(node* root)
{
    FILE* f = fopen("EN-US-Dictionary.txt","r");
    char words[50];
    if(!f)
    {
        printf("ERROR!....");
        return NULL;
    }
    while(!feof(f))
    {
        fscanf(f,"%s",words);
        root = insert(root,words);
    }
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    fclose(f);
    return root;
}

int main()
{
    node* root = NULL;
    char sentence[1000];
    root = load(root);
    printf("Size = %d\n",size(root));
    printf("..................................\n");
    printf("Height = %d\n",height(root));
    printf("..................................\n");
    printf("Enter A Sentence :\n");
    fgets(sentence,999,stdin);
    char* tok = strtok(sentence," \n");
    while(tok)
    {
        check_correctness(root,tok);
        tok = strtok(NULL," \n");
    }
    return 0;
}
