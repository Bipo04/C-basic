#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct Node
{
    char k;
    int fre;
    int bit;
    struct Node *left;
    struct Node *right;
} Node;

Node *queue[100] = { NULL };
Node *arr[100] = { NULL };
int num = 0;

Node *makeNode(char k, int fre)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->fre = fre;
    newNode->bit = 0;
    newNode->k = k;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void pushUp(int k)
{
    int parent = (k - 1) / 2;
    if(parent >= 0 && queue[k]->fre < queue[parent]->fre)
    {
        Node *tmp = queue[parent];
        queue[parent] = queue[k];
        queue[k] = tmp;
        pushUp(parent);
    }
}

void pushDown(int k)
{
    int left = 2*k + 1;
    int right = 2*k + 2;
    int min = k;
    if(left < num && queue[left]->fre < queue[k]->fre)
        min = left;
    if(right < num && queue[right]->fre < queue[min]->fre)
        min = right;
    if(min != k)
    {
        Node *tmp = queue[k];
        queue[k] = queue[min];
        queue[min] = tmp;
        pushDown(min);
    }
}

void enqueue(Node* k)
{
    queue[num] = k;
    pushUp(num);
    num++;
}

Node* dequeue()
{
    Node* tmp = queue[0];
    queue[0] = queue[num - 1];
    num--;
    pushDown(0);
    return tmp;
}
int cnt = 0;

void duyet(Node* node)
{
    if(node == NULL)
        return;
    if(node->left != NULL)
        node->left->bit = 1 + node->bit;
        duyet(node->left);
    if(node->right != NULL)
        node->right->bit = 1 + node->bit; 
        duyet(node->right);
    if(node->left == NULL && node->right == NULL)
        cnt += node->bit * node->fre;
}

int main()
{
    freopen("D:\\code\\ip.txt", "rt", stdin);
    char str[1000] = { 0 };
    fgets(str, sizeof(str) - 1, stdin);
    int tmp = strlen(str) - 1;
    for(int i = 0; i < tmp; i++)
    {
        if(arr[str[i] - ' '] == NULL)
        {
            arr[str[i] - ' '] = makeNode(str[i], 1);
        }
        else
            arr[str[i] - ' ']->fre++;
    }
    
    for(int i = 0; i < 100; i++)
    {
        if(arr[i] != NULL)
            enqueue(arr[i]);
    }
    while(num > 1)
    {
        Node* tmp1 = dequeue();
        Node* tmp2 = dequeue();
        Node* newNode = makeNode(0,0);
        newNode->fre = tmp1->fre + tmp2->fre;
        newNode->left = tmp1;
        newNode->right = tmp2;
        enqueue(newNode);
    }
    Node *kq = dequeue();
    duyet(kq);
    printf("%d", cnt);
    return 0;
}