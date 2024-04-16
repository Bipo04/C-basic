#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode
{
    char value[1024];
    struct TNode *leftMostChild;
    struct TNode *rightSibling;
    int maxHeight;
} NODE;

NODE *g_root = NULL;
char g_line[1024][1024] = { 0 };
int g_cnt;
char key[1024] = { 0 };
int q_size = 0;

NODE *makeNode(char *s)
{
    NODE *newNode = (NODE*)calloc(1, sizeof(NODE));
    strcpy(newNode->value, s);
    newNode->leftMostChild = NULL;
    newNode->rightSibling = NULL;
    newNode->maxHeight = 0;
    return newNode;
}

NODE *addLast(NODE *p, char *s)
{
    NODE *newNode = makeNode(s);
    NODE *temp = p;
    if(temp == NULL)
    {
        return newNode;
    }
    else
    {
        while(temp->rightSibling != NULL)
        {
            temp = temp->rightSibling;
        }
        temp->rightSibling = newNode;
        return p;
    }
}

NODE *findNode(NODE *p ,char *s)
{
    if(p == NULL)
        return NULL;
    else
    {
        if(strcmp(p->value, s) == 0)
            return p;
        else
        {
            NODE *temp = findNode(p->leftMostChild, s);
            if(temp != NULL)
                return temp;
            else
            {
                NODE *tmp = p->rightSibling;
                if(tmp != NULL)
                {
                    NODE *tp = findNode(tmp, s);
                    if(tp != NULL)
                        return tp;
                }
            }
        }
    }
}

void addChild(char *parent, char *s)
{
    NODE *p = findNode(g_root, parent);
    if(p != NULL)
    {
        NODE *temp = p->leftMostChild;
        p->leftMostChild = addLast(temp, s);
    }
}

void findChildren(char *s)
{
    NODE *p = findNode(g_root, s);
    if(p != NULL)
    {
        NODE *temp = p->leftMostChild;
        while (temp != NULL)
        {
            printf("%s ", temp->value);
            temp = temp->rightSibling;
        }
        
    }
}

void printTree(NODE *p)
{
    if(p == NULL)
        return;
    printf("%s ", p->value);
    NODE *temp = p->leftMostChild;
    printTree(temp);
    NODE *tmp = p->rightSibling;
    printTree(tmp);
}

void preOrder(NODE *p)
{
    if(p == NULL)
        return;
    preOrder(p->leftMostChild);
    printf("%s ", p->value);
    preOrder(p->rightSibling);
    
}

void postOrder(NODE *p)
{
    if(p == NULL)
        return;
    printf("%s ", p->value);
    postOrder(p->leftMostChild);
    postOrder(p->rightSibling);
}

void InOrder(NODE *p){
    if (p==NULL){
        return;
    }
    NODE *tmp = p->leftMostChild;
    InOrder(tmp);
    printf("%s ", p->value);
    if(tmp != NULL) 
        tmp = tmp->rightSibling;
    while (tmp != NULL){
        InOrder(tmp);
        tmp = tmp->rightSibling;
    }
}

int heightTree(NODE *p)
{
    if(p == NULL)
        return 0;
    else
    {
        int h = 1;
        NODE *temp = p->leftMostChild;
        while(temp != NULL)
        {
            int h1 = heightTree(temp) + 1;
            if(h1 > h)
            {
                h = h1;
            }
            temp = temp->rightSibling;
        }
        p->maxHeight = h;
        return h;
    }

}

int countNode(NODE *p)
{
    if(p == NULL)
        return 0;
    else
    {
        int sum = 1;
        NODE *temp = p->leftMostChild;
        while(temp != NULL)
        {
            sum += countNode(temp);
            temp = temp->rightSibling;
        }
        return sum;
    }
}

void draw(NODE *p, char *str)
{
    sprintf(g_line[g_cnt++], "%s+---%s", str, p->value);
    NODE *temp = p->leftMostChild;
    while(temp != NULL)
    {
        char nextStr[1024] = { 0 };
        NODE *tmp = p->rightSibling;
        if(tmp != NULL)
        {
            sprintf(nextStr, "%s|   ", str);
            draw(temp, nextStr);
        }
        else
        {
            sprintf(nextStr, "%s    ", str);
            draw(temp, nextStr);
        }
        temp = temp->rightSibling;
    }
}

void drawTree()
{
    sprintf(g_line[g_cnt++], "%s", g_root->value);
    NODE *temp = g_root->leftMostChild;
    while(temp != NULL)
    {
        draw(temp, "");
        temp = temp->rightSibling;
    }
    for(int i = 0; i < g_cnt; i++)
    {
        printf("%s\n", g_line[i]);
    }
}

void maxHeightPath()
{
    printf("%d\n", heightTree(g_root));
    NODE *temp = g_root;
    while(temp != NULL)
    {
        NODE *tmp = temp;
        NODE *max = NULL;
        int a = 0;
        char path[1024];
        while(tmp != NULL)
        {
            if(tmp->maxHeight > a)
            {
                a = tmp->maxHeight;
                max = tmp;
                strcpy(path, tmp->value);
            }
            tmp = tmp->rightSibling;
        }
        printf("%s ", path);
        temp = max->leftMostChild;
    }
}

void input()
{
    freopen("input.txt", "rt", stdin);
    char buffer[1024] = { 0 };
    char name[1024] = { 0 };
    char parent[1024] = { 0 };
    int root = 0;
    while(0 == 0)
    {
        fgets(buffer, sizeof(buffer) - 1, stdin);
        if(strstr(buffer, "$$") == buffer)
            break;
        else
        {
            int cnt = 0;
            char *str = (char*)buffer;
            while(0 == 0)
            {
                sscanf(str, "%s", name);
                str = strstr(str, name) + strlen(name);
                if(strcmp(name, "$") == 0)
                    break;
                else
                {
                    if(cnt == 0)
                    {
                        strcpy(parent, name);
                        if(root == 0)
                        {
                            g_root = makeNode(parent);
                            root = 1;
                        }
                    }
                    else
                    {
                        addChild(parent, name);
                    }
                    cnt++;
                }
            }
        }
    }
}

typedef struct ListNode{
    char data[1024];
    struct ListNode *next;
} ListNode;

ListNode *queue = NULL;

ListNode* makeNode1(char *k){
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    strcpy(newNode->data, k);
    newNode->next = NULL;
    return newNode;
}

void Enqueue(char *k){
    q_size++;
    ListNode *newNode = makeNode1(k);
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

char* Deqeue(){
    q_size--;
    if(queue == NULL)
        return NULL;
    ListNode *temp = queue;
    queue = queue->next;
    char tmp[1024] = { 0 };
    strcpy(tmp, temp->data);
    char *a= tmp;
    free(temp);
    return a;
}

void findCousin()
{
    scanf("%s", key);
    Enqueue(g_root->value);
    int check = 1;
    while(queue != NULL)
    {
        int i = q_size;
        if(check == 1){
            for(int j = 0; j < i; j++)
            {
                char k[1024] = { 0 };
                strcpy(k, Deqeue());
                NODE *t1 = findNode(g_root, k);
                NODE *t2 = t1->leftMostChild;
                char a[10][1024] = { 0 };
                int tmp = 0;
                while(t2 != NULL)
                {
                    strcpy(a[tmp], t2->value);
                    tmp++;
                    t2 = t2->rightSibling;
                }
                int ok = 1;
                for(int i = 0; i < tmp; i++)
                {
                    if(strcmp(a[i], key) == 0)
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
        printf("%s ", Deqeue());
}

int main()
{
    input();
    findCousin();
    return 0;
}