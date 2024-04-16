#include <stdio.h>
#include <malloc.h>
#include <string.h>
struct node_
{
    char value[256];
    struct node_* leftMostChild;
    struct node_* rightSibling;
};
typedef struct node_ NODE;
NODE* makeNode(char* name);
NODE* findNode(NODE* p, char* name);
NODE* addLast(NODE* p, char* name);
void addChild(char* parent, char* child);
void storeTree(FILE* f, NODE* p);

NODE* g_root = NULL;

NODE* makeNode(char* name)
{
    NODE* newNode = (NODE*)calloc(1 , sizeof(NODE));
    strcpy(newNode->value, name);
    newNode->leftMostChild = NULL;
    newNode->rightSibling = NULL;
}

//Add a node "name" to the end of the list started by p
NODE* addLast(NODE* p, char* name)
{
    NODE* newNode = makeNode(name);
    NODE* tmp = p;
    if (tmp == NULL)
    {
        return newNode;
    }else
    {
        while (tmp->rightSibling != NULL)
        {
            tmp = tmp->rightSibling;
        }
        tmp->rightSibling = newNode;
        return p;
    }
}

//Add "child" as a child of "parent"
void addChild(char* parent, char* child)
{
    NODE* p = findNode(g_root, parent);
    if (p != NULL)
    {
        NODE* tmp = p->leftMostChild;
        p->leftMostChild = addLast(tmp, child);
    }
}

//Find a node with value "name"
NODE* findNode(NODE* p, char* name)
{
    if (p == NULL)
        return NULL;
    else
    {
        if (strcmp(p->value, name) == 0)
        {
            return p;
        }else
        {
            NODE* tmp = findNode(p->leftMostChild, name);
            if (tmp != NULL)
            {
                return tmp;
            }else
            {
                NODE* tmp = p->rightSibling;
                if (tmp != NULL)
                {
                    NODE* tmp1 = findNode(tmp, name);
                    if (tmp1 != NULL)
                    {
                        return tmp1;
                    }
                }
            }
        }
    }
}

void findChilren(char* name)
{
    NODE* tmp = findNode(g_root, name);
    if (tmp != NULL)
    {
        NODE* tmp1 = tmp->leftMostChild;
        while (tmp1 != NULL)
        {
            printf("%s ", tmp1->value);
            tmp1 = tmp1->rightSibling;
        }
    }
    printf("\n");
}

void printTree(NODE* p)
{
    if (p != NULL)
    {
        printf("%s ",p->value);
        NODE* tmp = p->leftMostChild;
        printTree(tmp);
        tmp = p->rightSibling;
        if (tmp != NULL)
        {
            printTree(tmp);
        }
    }
}

int heightTree(NODE* p)
{
    if (p == NULL)
        return 0;
    else
    {
        int h = 1;
        NODE* tmp = p->leftMostChild;
        while (tmp != NULL)
        {
            int h1 = heightTree(tmp) + 1;
            if (h1 > h)
            {
                h = h1;        
            }
            tmp = tmp->rightSibling;
        }
        return h;
    }
}

int countTree(NODE* p)
{
    if (p == NULL)
        return 0;
    else
    {
        int sum = 1;
        NODE* tmp = p->leftMostChild;
        while (tmp != NULL)
        {
            sum += countTree(tmp);
            tmp = tmp->rightSibling;
        }
        return sum;
    }
}

void processStore(char* path)
{
    FILE* f = fopen(path, "wt");
    storeTree(f, g_root);
    fprintf(f, "$$\n");
    fclose(f);
}

void storeTree(FILE* f, NODE* p)
{
    if (p != NULL)
    {
        NODE* tmp = p->leftMostChild;
        if (tmp != NULL)
        {
            fprintf(f, "%s ", p->value);
            while (tmp != NULL)
            {
                fprintf(f, "%s ", tmp->value);
                tmp = tmp->rightSibling;
            }
            fprintf(f, "$\n");
            tmp = p->leftMostChild;
            while (tmp != NULL)
            {
                storeTree(f, tmp);
                tmp = tmp->rightSibling;
            }
        }
    }
}

int main()
{
    freopen("input.txt", "rt", stdin);
    char buffer[1024] = { 0 };
    char name[1024] = { 0 };
    char parent[1024] = { 0 };
    int root = 1;
    while (0 == 0)
    {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer) - 1, stdin);
        if (strstr(buffer,"$$") == buffer) 
            break;
        else
        {
            int count = 0;
            char* tmpBuf = (char*)buffer;
            while (0 == 0)
            {
                memset(name, 0, sizeof(name));
                sscanf(tmpBuf,"%s", name);
                tmpBuf = strstr(tmpBuf, name) + strlen(name);
                if (strcmp(name,"$") == 0)
                    break;
                else
                {
                    if (count == 0)
                    {
                        memset(parent, 0, sizeof(parent));
                        strcpy(parent, name);        
                        if (root == 1)
                        {
                            root = 0;
                            g_root = makeNode(name);
                        }
                    }else
                    {
                        addChild(parent, name);
                    }
                    count += 1;
                }
            }
        }
    }
    printTree(g_root);
    printf("\n");
    printf("%d\n", heightTree(g_root));
    printf("%d\n", countTree(g_root));
    processStore("out.txt");
}