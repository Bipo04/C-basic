#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct TNode
{
    int coefficient;
    int exponent;
    struct TNode *next;
} TNode;

TNode *makeNode(int heso, int mu)
{
    TNode *p = (TNode*)malloc(sizeof(TNode));
    p->coefficient = heso;
    p->exponent = mu;
    p->next = NULL;
    return p;
}

TNode *T[10] = { NULL };

void AddTerm(int pol, int coef, int exp)
{
    TNode *p = makeNode(coef, exp);
    TNode *temp = T[pol];
    if(temp == NULL)
        T[pol] = p;
    else if(exp > (temp)->exponent)
    {
        p->next = T[pol];
        T[pol] = p;
    }
    else
    {
        TNode *pre = temp;
        while(temp){
            if(temp->exponent == exp)
            {
                temp->coefficient += coef;
                return;
            }
            else if(exp > temp->exponent)
            {
                pre->next = p;
                p->next = temp;
                return;
            }
            pre = temp;
            temp = temp->next;
        }
        if(temp == NULL)
            pre->next = p;
    }
}

void PrintPoly(int pol)
{
    TNode *temp = T[pol];
    while(temp)
    {
        printf("%d %d ", temp->coefficient, temp->exponent);
        temp = temp->next;
    }
    printf("\n");
}

void AddPoly(int p1, int p2, int p3)
{
    TNode *temp = T[p1];
    while(temp)
    {
        AddTerm(p3, temp->coefficient, temp->exponent);
        temp = temp->next;
    }
    temp = T[p2];
    while(temp)
    {
        AddTerm(p3, temp->coefficient, temp->exponent);
        temp = temp->next;
    }
}

int EvaluatePoly(int pol, int x)
{
    int kq = 0;
    TNode *temp = T[pol];
    while(temp)
    {
        kq += temp->coefficient * pow(x, temp->exponent);
        temp = temp->next;
    }
    return kq;
}

int main()
{
    char cmd[20];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "*") == 0)
            break;
        else{
            if(strcmp(cmd, "AddTerm") == 0){
                int a, b, c;
                scanf("%d %d %d", &a, &b, &c);
                AddTerm(a, b, c);
            }
            else if(strcmp(cmd, "PrintPoly") == 0){
                int a;
                scanf("%d", &a);
                PrintPoly(a);
            }
            else if(strcmp(cmd, "AddPoly") == 0){
                int a, b, c;
                scanf("%d %d %d", &a, &b, &c);
                AddPoly(a, b, c);
            }
            else if(strcmp(cmd, "EvaluatePoly") == 0){
                int a, b;
                scanf("%d %d", &a, &b);
                printf("%d", EvaluatePoly(a, b));
            }
        }
    }
    return 0;
}