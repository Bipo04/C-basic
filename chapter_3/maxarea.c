#include <stdio.h>
#include <stdlib.h>

#define N 1000

typedef struct ListNode{
    int data;
    struct ListNode *next;
} ListNode;

ListNode *makeNode(int x){
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

void push(ListNode **top, int x){
    ListNode *newNode = makeNode(x);
    newNode->next = *top;
    *top = newNode;
}

void pop(ListNode **top){
    if(*top == NULL)
        return;
    ListNode *temp = *top;
    *top = (*top)->next;
    free(temp);
}

int top(ListNode *top){
    if(top != NULL)
        return top->data;
}

int main(){
    ListNode *stack = NULL;
    int a[N] = { 0 };
    int n, S = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    int i;
    for(i = 1; i <= n; i++){
        if(stack == NULL || a[top(stack)] <= a[i])
            push(&stack, i);
        else if(a[top(stack)] > a[i]){
            while(size_of_Node(stack) != 0 && a[top(stack)] > a[i]){
                int t = top(stack);
                if(size_of_Node(stack) == 1){
                    pop(&stack);
                    int temp = a[t] * (i - 1);
                    if(temp > S)
                        S = temp;
                }
                else{
                    pop(&stack);
                    int t2 = top(stack);
                    int temp = a[t] *(i - t2 - 1);
                    if(temp > S)
                        S = temp;
                }
            }
            push(&stack, i);
        }
    }

    while(stack == NULL){
        int t = top(stack);
        if(size_of_Node(stack) == 1){
            pop(&stack);
            int temp = a[t] * (i - 1);
            if(temp > S)
                S = temp;
        }
        else{
            pop(&stack);
            int t2 = top(stack);
            int temp = a[t] *(i - t2 - 1);
            if(temp > S)
                S = temp;
        }
    }
    printf("%d", S);
    return 0;
}