#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode{
    char data[1024];
    struct TNode *next;
} TNode;

TNode *head = NULL;
TNode *tail = NULL;

TNode *makeNode(char *k){
    TNode *p = (TNode*)malloc(sizeof(TNode));
    strcpy(p->data, k);
    p->next = NULL;
    return p;
}

TNode *find(char *k){
    TNode *temp = head;
    for(temp; temp != NULL; temp = temp->next){
        if(strcmp(temp->data, k) == 0)
            return temp;
    }
    return NULL;
}

TNode *findPre(char *k){
    TNode *temp = head;
    if(strcmp(head->data, k) == 0)
        return NULL;
    for(temp; temp->next != NULL; temp = temp->next){
        if(strcmp(temp->next->data, k) == 0)  
            return temp;
    }
    return NULL;
}

void addLast(char *k){
    if(find(k) == NULL)
    {
        TNode *p = makeNode(k);
        if(head != NULL)
        {
            tail->next = p;
            tail = tail->next;
        }
        else
        {
            head = tail = p;
        }
    }
}

void addFirst(char *k){
    if(find(k) == NULL)
    {
        TNode *p = makeNode(k);
        if(head == NULL)
            head = tail = p;
        else
        {
            p->next = head;
            head = p;
        }
    }
}

void addAfter(char *u, char *v){
    TNode *f1 = find(u), *f2 = find(v);
    if(f1 == NULL && f2 != NULL){
        TNode *p = makeNode(u);
        p->next = f2->next;
        f2->next = p;
    }
}

void addBefore(char *u, char *v){
    TNode *f1 = find(u), *f2 = find(v);
    if(f1 == NULL && f2 != NULL){
        TNode *temp = head;
        if(head->data == v){
            addFirst(u);
            return;
        }
        TNode *p = makeNode(u);
        TNode *pre = findPre(v);
        p->next = pre->next;
        pre->next = p;
    }
}

void remove_k(char *k){
    TNode *f = find(k);
    if(f == NULL)
        return;
    else if(strcmp(head->data, k) == 0){
        TNode *temp = head;
        head = head->next;
        free(temp);
        return;
    }
    else
    {
        TNode *f1 = findPre(k);
        if(f->next == NULL){
            f1->next = NULL;
            tail = f1;
            free(f);
            return;
        }
        else{
            f1->next = f->next;
            free(f);
            return;
        }
    }
    
}

void reverse(){
    TNode *pre = NULL;
    TNode *curr = head;
    TNode *nextNode = curr->next;
    while(nextNode != NULL){
        nextNode = curr->next;
        curr->next = pre;
        pre = curr;
        curr = nextNode;
    }
    head = pre;
}

int main(){
    int n; scanf("%d", &n);

    for(int i = 0; i < n; i++){
        char k[1024] = { 0 };
        scanf("%s", k);
        addLast(k);
    }
    char cmd[10];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "#") == 0)
            break;
        if(strcmp(cmd, "addlast") == 0){
            char key[1024] = { 0 };
            scanf("%s", key);
            addLast(key);
        }
        if(strcmp(cmd, "addfirst") == 0){
            char key[1024] = { 0 };
            scanf("%s", key);
            addFirst(key);
        }
        if(strcmp(cmd, "addafter") == 0){
            char key1[1024] = { 0 }, key2[1024] = { 0 };
            scanf("%s %s", key1, key2);
            addAfter(key1, key2);
        }
        if(strcmp(cmd, "addbefore") == 0){
            char key1[1024] = { 0 }, key2[1024] = { 0 };
            scanf("%s %s", key1, key2);
            addBefore(key1, key2);
        }
        if(strcmp(cmd, "remove") == 0){
            char key[1024] = { 0 };
            scanf("%s", key);
            remove_k(key);
        }
        if(strcmp(cmd, "reverse") == 0){
            reverse();
        }
    }

    TNode *temp = head;
    while(temp != NULL){
        printf("%s ", temp->data);
        temp = temp->next;
    }
    return 0;
}