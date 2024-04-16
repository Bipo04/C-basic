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

void preOrder(NODE *p)
{
    if(p == NULL)
        return;
    printf("%s ", p->value);
    preOrder(p->leftMostChild);
    preOrder(p->rightSibling);
    
}

void postOrder(NODE *p)
{
    if(p == NULL)
        return;
    postOrder(p->leftMostChild);
    printf("%s ", p->value);
    postOrder(p->rightSibling);
}

void inOrder(NODE *p){
    if (p==NULL){
        return;
    }
    NODE *tmp = p->leftMostChild;
    inOrder(tmp);
    printf("%s ", p->value);
    if(tmp != NULL) 
        tmp = tmp->rightSibling;
    while (tmp != NULL){
        inOrder(tmp);
        tmp = tmp->rightSibling;
    }
}

int main()
{
    char cmd[1024] = { 0 };
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "*") == 0)
            break;
        else{
            if(strcmp(cmd, "MakeRoot") == 0){
                char k[1024] = { 0 };
                scanf("%s", k);
                g_root = makeNode(k);
            }
            else if(strcmp(cmd, "Insert") == 0){
                char k1[1024] = { 0 }, k2[1024] = { 0 };
                scanf("%s %s", k1, k2);
                addChild(k2, k1);
            }
            else if(strcmp(cmd, "InOrder") == 0){
                inOrder(g_root);
                printf("\n");
            }
            else if(strcmp(cmd, "PreOrder") == 0){
                preOrder(g_root);
                printf("\n");
            }
            else if(strcmp(cmd, "PostOrder") == 0){
                postOrder(g_root);
                printf("\n");
            }
        }
    }
    return 0;
}