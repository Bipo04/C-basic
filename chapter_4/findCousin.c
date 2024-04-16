#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int val;
    struct Node *leftMostChild;
    struct Node *rightSibling;
} Node;

Node *g_root = NULL;
char result[100][30];

Node *makeNode(int x)
{
    Node *newNode = (Node*)calloc(1, sizeof(Node));
    newNode->val = x;
    newNode->leftMostChild = NULL;
    newNode->rightSibling = NULL;
    return newNode;
}

Node *addLast(Node *p, int x)
{
    Node *newNode = makeNode(x);
    Node *temp = p;
    if(p == NULL)
        return newNode;
    else
    {
        while(temp->rightSibling != NULL)
            temp = temp->rightSibling;
        temp->rightSibling = newNode;
        return p;
    }
}

Node *findNode(Node *p ,int k)
{
    if(p == NULL)
        return NULL;
    else
    {
        if(p->val == k)
            return p;
        else
        {
            Node *temp = findNode(p->leftMostChild, k);
            if(temp != NULL)
                return temp;
            else
            {
                Node *t = findNode(p->rightSibling, k);
                if(t != NULL)
                    return t;
            }
        }
    }
}

void addChild(int parent, int k)
{
    Node *p = findNode(g_root, parent);
    if(p != NULL)
    {
        Node *temp = p->leftMostChild;
        p->leftMostChild = addLast(temp, k);
    }
}

void findChild(int k)
{
    Node *temp = findNode(g_root, k);
    if(temp != NULL)
    {
        Node *t = temp->leftMostChild;
        while(t != NULL)
        {
            printf("%d ", t->val);
            t = t->rightSibling;
        }
    }
}

int cnt = 0;

void Duyet(Node *p, char *str)
{
    strcat(result[cnt], str);
    if(cnt != 0){
        strcat(result[cnt], "+---");
    }
    char s[10] = { 0 };
    sprintf(s, "%d", p->val);
    strcat(result[cnt], s);
    cnt++;
    Node *parent = p;
    Node *temp = p->leftMostChild;

    while(temp != NULL)
    {
        if(p->rightSibling != NULL)
        {
            if(parent == g_root)
                Duyet(temp, "");
            else{
                char cmd[100] = { 0 };
                strcpy(cmd, str);
                strcat(cmd, "|   ");
                Duyet(temp, cmd);
            }
        }
        else
        {
            if(parent == g_root)
                Duyet(temp, "");
            else{
                char cmd[100] = { 0 };
                strcpy(cmd, str);
                strcat(cmd, "    ");
                Duyet(temp, cmd);
            }
        }
        temp = temp->rightSibling;
    }
}

typedef struct ListNode{
    int data;
    struct ListNode *next;
} ListNode;

ListNode *queue = NULL;

ListNode* makeNode1(int x){
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

void Enqueue(int x){
    ListNode *newNode = makeNode1(x);
    if(queue == NULL){
        queue = newNode;
        return;
    }
    ListNode *temp = queue;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

int Deqeue(){
    if(queue == NULL)
        return -1;
    ListNode *temp = queue;
    queue = queue->next;
    int a = temp->data;
    free(temp);
    return a;
}

int size_of_Node(){
    int cnt = 0;
    ListNode *temp = queue;
    while(temp != NULL){
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

int key;
void input()
{
    freopen("input.txt", "rt", stdin);
    char buffer[1024] = { 0 };
    char name[1024] = { 0 };
    int root = 1;
    scanf("%d", &key);
    getchar();
    while (0 == 0)
    {
        fgets(buffer, sizeof(buffer) - 1, stdin);
        if (strstr(buffer,"$$") == buffer) 
            break;
        else
        {
            int count = 0;
            char* tmpBuf = (char*)buffer;
            while (0 == 0)
            {
                sscanf(tmpBuf,"%s", name);
                tmpBuf = strstr(tmpBuf, name) + strlen(name);
                if (strcmp(name,"$") == 0)
                    break;
                else
                {
                    int k = atoi(name); 
                    int p;
                    if (count == 0)
                    {   
                        p = k;
                        if (root == 1)
                        {
                            root = 0;
                            g_root = makeNode(k);
                        }
                    }else
                    {
                        addChild(p, k);
                    }
                    count += 1;
                }
            }
        }
    }
}

void findCousin()
{
    Enqueue(g_root->val);
    int check = 1;
    while(queue != NULL)
    {
        int i = size_of_Node();
        if(check == 1){
            for(int j = 0; j < i; j++)
            {
                int k = Deqeue();
                Node *t1 = findNode(g_root, k);
                Node *t2 = t1->leftMostChild;
                int a[10] = { 0 };
                int tmp = 0;
                while(t2 != NULL)
                {
                    a[tmp] = t2->val;
                    tmp++;
                    t2 = t2->rightSibling;
                }
                int ok = 1;
                for(int i = 0; i < tmp; i++)
                {
                    if(a[i] == key)
                    {
                        ok = 0;
                        check = 0;
                    }
                }
                if(ok == 1)
                {
                    for(int i = 0; i < tmp; i++)
                        Enqueue(a[i]);
                }
            }
        }
        else 
            break;
    }

    while(queue != NULL)
        printf("%d ", Deqeue());
    
}

int main()
{
    input();
    findCousin();
    return 0;
}