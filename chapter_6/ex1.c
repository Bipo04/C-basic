#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

Node *queue[100] = { NULL };
int num = 0;

Node *makeNode(int k)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = k;
    newNode->next = NULL;
    return newNode;
}

void pushUp(int k)
{
    int parent = (k - 1) / 2;
    if(parent >= 0 && queue[k]->val < queue[parent]->val)
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
    if(left < num && queue[left]->val < queue[k]->val)
        min = left;
    if(right < num && queue[right]->val < queue[min]->val)
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

Node *mergeKLists(Node **lists, int listSize)
{
    for(int i = 0; i < listSize; i++)
    {
        if(lists[i] != NULL)
            enqueue(lists[i]);
    }
    Node *kq = NULL;
    Node *tmp_kq = NULL;
    while(num != 0)
    {
        Node *tmp = dequeue();
        if(kq == NULL)
        {
            kq = makeNode(tmp->val);
            tmp_kq = kq;
        }
        else
        {
            kq->next = makeNode(tmp->val);
            kq = kq->next;
        }
        if(tmp->next != NULL)
            enqueue(tmp->next);
    }
    return tmp_kq;
}

void duyet(Node *node)
{
    while(node != NULL)
    {
        printf("%d ", node->val);
        node = node->next;
    }
}

int main()
{
    Node *list[3] = { NULL};
    Node *result = mergeKLists(list, 3);
    duyet(result);
    return 0;
}