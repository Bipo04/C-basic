#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode{
    int val;
    struct TNode *nodeLeft;
    struct TNode *nodeRight;
} TNode;

TNode *root = NULL;

TNode *makeNode(int k){
    TNode *p = (TNode*)malloc(sizeof(TNode));
    p->val = k;
    p->nodeLeft = NULL;
    p->nodeRight = NULL;
    return p;
}

void insert(int k){
    if(root == NULL){
        TNode *p = makeNode(k);
        root = p;
        return;
    }
    TNode *temp = root;
    while(temp != NULL){
        if(temp->val == k)
            return;
        else if(temp->val > k){
            if(temp->nodeLeft == NULL){
                TNode *p = makeNode(k);
                temp->nodeLeft = p;
                return;
            }
            temp = temp->nodeLeft;
        }
        else if(temp->val < k){
            if(temp->nodeRight == NULL){
                TNode *p = makeNode(k);
                temp->nodeRight = p;
                return;
            }
            temp = temp->nodeRight;
        }
    }
}

void postorder(TNode* root){
    if(root == NULL)
        return;
    postorder(root->nodeLeft);
    postorder(root->nodeRight);
    printf("%d ", root->val);
}

void preorder(TNode* root){
    if(root == NULL)
        return;
    printf("%d ", root->val);
    preorder(root->nodeLeft);
    preorder(root->nodeRight);
}

int main(){
    char cmd[20];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "#") == 0)
            break;
        else if(strcmp(cmd, "insert") == 0){
            int k;
            scanf("%d", &k);
            insert(k);
        }
        else if(strcmp(cmd, "preorder") == 0){
            preorder(root);
            printf("\n");
        }
        else if(strcmp(cmd, "postorder") == 0){
            postorder(root);
            printf("\n");
        }
    }
    return 0;
}