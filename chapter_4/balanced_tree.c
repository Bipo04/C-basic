#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int val;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

Node *g_root = NULL;

Node *T[50001] = { NULL };

Node *makeNode(int x)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = x;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void AddLeft(Node *node, int u, int v)
{
    Node *temp = T[v];
    temp->left = makeNode(u);
    T[u] = temp->left; 
}

void AddRight(Node *node, int u, int v)
{
    Node *temp = T[v];
    temp->right = makeNode(u);
    T[u] = temp->right; 
}

int max(int a, int b) 
{ 
	return (a > b) ? a : b; 
} 

int height(Node* node)
{
    if(node == NULL)
        return 0;
    int h = 1 + max(height(node->left), height(node->right));
    node->height = h;
    return h;
}
int isAVL(Node* root) {
    if(root == NULL)
        return 1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) <= 1 && isAVL(root->left) && isAVL(root->right))
        return 1;
    return 0;
}

int main()
{
    char cmd[20];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "*") == 0)
            break;
        else if(strcmp(cmd, "MakeRoot") == 0){
            int a; 
            scanf("%d", &a);
            g_root = makeNode(a);
            T[a] = g_root;
        }
        else if(strcmp(cmd, "AddLeft") == 0){
            int a, b; 
            scanf("%d %d", &a, &b);
            AddLeft(g_root, a, b);
        }
        else if(strcmp(cmd, "AddRight") == 0){
            int a, b; scanf("%d %d", &a, &b);
            AddRight(g_root, a, b);
        }
    }
    height(g_root);
    printf("%d %d", isAVL(g_root), g_root->left->height);
    return 0;
}
// MakeRoot 1
// AddLeft 2 1
// AddRight 3 1
// AddLeft 9 2
// AddRight 4 2
// AddLeft 6 3
// AddRight 5 3
// AddLeft 7 4
// AddRight 8 4
// *
