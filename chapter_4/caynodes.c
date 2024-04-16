#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode{
    int val;
    struct TNode *son[3];
} TNode;

TNode *makeNode(int k){
    TNode *new = (TNode*)malloc(sizeof(TNode));
    new->val = k;
    new->son[0] = NULL;
    new->son[1] = NULL;
    new->son[2] = NULL;
    return new;
}

void makeRoot(TNode **root, int k){
    *root = makeNode(k);
}

void insert(TNode *root, int u, int v){
    if(root == NULL)
        return;
    else{
        if(root->val != v){
            for(int i = 0; i < 3; i++){
                insert(root->son[i], u, v);
            }
        }
        else{
            for(int i = 0; i < 3; i++){
                if(root->son[i] == NULL){
                    root->son[i] = makeNode(u);
                    return;
                }
            }
        }
    }
    
}

void inorder(TNode *root){
    if(root == NULL)
        return;
    else{
        inorder(root->son[0]);
        printf("%d ", root->val);
        inorder(root->son[1]);
        inorder(root->son[2]);
    }
}

void preorder(TNode *root){
    if(root == NULL)
        return;
    else{
        printf("%d ", root->val);
        preorder(root->son[0]);
        preorder(root->son[1]);
        preorder(root->son[2]);
    }
}

void postorder(TNode *root){
    if(root == NULL)
        return;
    else{
        postorder(root->son[0]);
        postorder(root->son[1]);
        postorder(root->son[2]);
        printf("%d ", root->val);
    }
}

int main(){
    TNode *root = NULL;
    char cmd[20];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "*") == 0)
            break;
        else{
            if(strcmp(cmd, "MakeRoot") == 0){
                int a;
                scanf("%d", &a);
                makeRoot(&root, a);
            }
            else if(strcmp(cmd, "Insert") == 0){
                int a, b;
                scanf("%d %d", &a, &b);
                insert(root, a, b);
            }
            else if(strcmp(cmd, "InOrder") == 0){
                inorder(root);
                printf("\n");
            }
            else if(strcmp(cmd, "PreOrder") == 0){
                preorder(root);
                printf("\n");
            }
            else if(strcmp(cmd, "PostOrder") == 0){
                postorder(root);
                printf("\n");
            }
        }
    }
    return 0;
}