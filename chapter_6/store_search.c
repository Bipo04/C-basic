#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max 51
#define m 20001

typedef struct Node
{
    char key[max];
    struct Node* next;
} Node;

Node *T[m] = { NULL };

Node* makeNode(char *k)
{
    Node *p = (Node*)malloc(sizeof(Node));
    strcpy(p->key, k);
    p->next = NULL;
    return p;
}

int h(char *k)
{
    int c = 0;
    while(*k != '\0')
    {
        c = (c * 256 + *k) % m;
        k++;
    }
    return c;
}

void insertList(int id, char *k)
{
    Node *p = makeNode(k);
    p->next = T[id];
    T[id] = p;
}

Node *findList(int id, char *k)
{
    Node *temp = T[id];
    while(temp != NULL)
    {
        if(strcmp(temp->key, k) == 0)
            return temp;
    }
    return NULL;
}

int find(char *k)
{
    int id = h(k);
    Node *temp = findList(id, k);
    if(temp != NULL)
        return 1;
    return 0;
}

int insert(char *k)
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
    freopen("D:\\code\\ip.txt", "rt", stdin);
    char key[max];
    while(1){
        scanf("%s", key);
        if(strcmp(key, "*") == 0)
            break;
        else
            insert(key);
    }
    char cmd[20];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd,"find") == 0){
            scanf("%s", key);
            int ans = find(key);
            printf("%d\n", ans);
        }else if(strcmp(cmd,"insert") == 0){
            scanf("%s", key);
            int ans = insert(key);
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