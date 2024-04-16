#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef char STRING[1024];

struct node_
{
    char value[256];
    struct node_* leftMostChild;
    struct node_* rightSibling;
    struct node_* maxHeightChild1;
    struct node_* maxHeightChild2;
    struct node_* maxDiameterChild;
    struct node_* maxHeightChild;
    int maxHeight;
    int order;
};
typedef struct node_ NODE;
NODE* makeNode(char* name);
NODE* findNode(NODE* p, char* name);
NODE* addLast(NODE* p, char* name);
void addChild(char* parent, char* child);
void storeTree(FILE* f, NODE* p);

NODE* g_root = NULL;
STRING g_lines[1024];
int g_count = 0;
int g_order = 0;

NODE* makeNode(char* name)
{
    NODE* newNode = (NODE*)calloc(1 , sizeof(NODE));
    strcpy(newNode->value, name);
    newNode->leftMostChild = NULL;
    newNode->rightSibling = NULL;
    newNode->maxHeightChild1 = NULL;
    newNode->maxHeightChild2 = NULL;
    newNode->maxDiameterChild = NULL;
    newNode->maxHeightChild = NULL;
    newNode->maxHeight = 0;
    newNode->order = 0;
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

void visitTree(NODE* p)
{
    if (p != NULL)
    {
        g_order += 1;
        p->order = g_order;
        NODE* tmp = p->leftMostChild;
        visitTree(tmp);
        tmp = p->rightSibling;
        if (tmp != NULL)
        {
            visitTree(tmp);
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
                p->maxHeightChild = tmp;
            }
            tmp = tmp->rightSibling;
        }
        p->maxHeight = h;
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

void drawTree(NODE* p, char* prefix)
{
	sprintf(g_lines[g_count++],"%s+---%s", prefix, p->value);
	NODE* tmp = p->leftMostChild;
	while (tmp != NULL)
	{
        char nextPrefix[1024] = { 0 };
		if (p->rightSibling != NULL)
        {
            sprintf(nextPrefix,"%s|   ", prefix);
			drawTree(tmp, nextPrefix);
        }
		else
        {
            sprintf(nextPrefix,"%s    ", prefix);
			drawTree(tmp, nextPrefix);
        }	
		tmp = tmp->rightSibling;
	}
}

int diameterTree(NODE* p)
{
    if (p == NULL)
        return 0;
    int max1 = 0, max2 = 0;
    NODE* tmp = p->leftMostChild;
    NODE* maxNode1 = NULL, *maxNode2 = NULL;
    while (tmp != NULL)
    {
        int h = heightTree(tmp);
        if (h > max1)
        {
            max2 = max1;
            maxNode2 = maxNode1;
            max1 = h;
            maxNode1 = tmp;

        }else if (h > max2)
        {
            max2 = h;
            maxNode2 = tmp;
        }
        tmp = tmp->rightSibling;
    }
    NODE* maxDiameterNode = NULL;
    int maxChildD = 0;
    tmp = p->leftMostChild;
    int d = 0;
    while (tmp != NULL)
    {
        int d = diameterTree(tmp);
        if (d > maxChildD)
        {
            maxChildD = d;
            maxDiameterNode = tmp;
        }
        tmp = tmp->rightSibling;
    }
    if (maxChildD > max1 + max2)
    {
        p->maxDiameterChild = maxDiameterNode;
        return maxChildD;
    }
    else
    {
        p->maxHeightChild1 = maxNode1;
        p->maxHeightChild2 = maxNode2;
        return max1 + max2;
    }
}

int main()
{
    freopen("input.txt","rt",stdin);
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
    
    sprintf(g_lines[g_count++],"%s", g_root->value);
    NODE* tmp = g_root->leftMostChild;
	while (tmp != NULL)
	{
		drawTree(tmp, "");
        tmp = tmp->rightSibling;
	}

    for (int i = 0;i < g_count;i++)
    {
        printf("%s\n", g_lines[i]);
    }



    int d = diameterTree(g_root);
    printf("%d\n", d);
    STRING* nodes = (STRING*)calloc(d + 1, sizeof(STRING));
    tmp = g_root;
    int i = 0;
    while (tmp->maxDiameterChild != NULL)
    {
        tmp = tmp->maxDiameterChild;
    }

    NODE* tmp1 = tmp->maxHeightChild1;
    int h1 = tmp1->maxHeight;
    while (tmp1 != NULL)
    {
        strcpy(nodes[h1 - i - 1], tmp1->value);
        tmp1 = tmp1->maxHeightChild;
        i += 1;
    }
    strcpy(nodes[i++], tmp->value);
    NODE* tmp2 = tmp->maxHeightChild2;
    while (tmp2 != NULL)
    {
        strcpy(nodes[i++], tmp2->value);
        tmp2 = tmp2->maxHeightChild;
    }
    visitTree(g_root);
    if (tmp->maxHeightChild1->order < tmp->maxHeightChild2->order)
    {
        for (int i = 0;i < d;i++)
        {
            printf("%s ", nodes[i]);
        }
    }else
    {
        for (int i = d ;i >= 0;i--)
        {
            printf("%s ", nodes[i]);
        }
    }
    printf("\n");
}