#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

typedef struct TNode
{
    long long val;
    struct TNode *next;
} Node;

Node *T[10001] = { NULL };

Node *makeNode(long long k)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = k;
    newNode->next = NULL;
    return newNode;
}

int h(long long k)
{
    int temp =(int)( k % MAX );
    return temp;
}

void insertList(int id, long long k)
{
    Node *p = makeNode(k);
    Node *temp = T[id];
    if(temp == NULL)
        T[id] = p;
    else
    {
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = p;
    }
}

Node *findList(int id, long long k)
{
    Node *temp = T[id];
    while(temp != NULL)
    {
        if(temp->val == k)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int find(long long k)
{
    int id = h(k);
    Node *temp = findList(id, k);
    if(temp != NULL)
        return 1;
    return 0;
}

int insert(long long k)
{
    int id = h(k);
    if(find(k) == 0)
    {
        insertList(id, k);
        return 1;
    }
    return 0;
}

void solve(){
    long long k;
    while(1){
        int check = scanf("%lld", &k);
        if(check == 1)
            insert(k);
        else{
            getchar();
            break;
        }
    }

    char cmd[20];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd,"find") == 0){
            scanf("%lld", &k);
            int ans = find(k);
            printf("%d\n", ans);
        }else if(strcmp(cmd,"insert") == 0){
            scanf("%lld", &k);
            int ans = insert(k);
            printf("%d\n", ans);
        }else if(strcmp(cmd,"***") == 0){
            break;
        }
    }
}


int main()
{
    solve();
    return 0;
}