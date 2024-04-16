#include <stdio.h>
#include <stdlib.h>

typedef struct Tnode
{
    int row;
    int col;
    int dist;
    struct Tnode *next;
    struct Tnode *prev;
} Node;

int n, m, r, c;
int a[1001][1001] = { 0 };
int marker[1001][1001] = { 0 };
Node *queue_start = NULL;
Node *queue_end = NULL;

Node *makeNode(int r, int c, int d)
{
    Node *newNode = (Node*)calloc(1, sizeof(Node));
    newNode->row = r;
    newNode->col = c;
    newNode->dist = d;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void Enqueue(int r, int c, int d)
{
    marker[r][c] = 1;
    Node *new = makeNode(r, c, d);
    if(queue_start == NULL)
    {
        queue_start = new;
        queue_end = new;
    }
    else
    {
        new->next = queue_start;
        queue_start->prev = new;
        queue_start = new;
    }
}

Node *Dequeue(){
    Node *temp = queue_end;
    Node *prev = temp == NULL ? NULL : temp->prev;
    if(temp != NULL)
    {
        Node *result = makeNode(0,0,0);
        result->row = temp->row;
        result->col = temp->col;
        result->dist = temp->dist;
        free(temp);
        if(prev != NULL)
        {
            prev->next = NULL;
            queue_end = prev;
        }
        else
        {
            queue_start = NULL;
            queue_end = NULL;
        }
        return result;
    }
    else
        return NULL;
}

void Enqueue2(int r, int c, int d)
{
    marker[r][c] = 1;
    Node *new = makeNode(r, c, d);
    if(queue_start == NULL)
    {
        queue_start = new;
        queue_end = new;
    }
    else
    {
        queue_end->next = new;
        new->prev = queue_end;
        queue_end = new;
    }
}

Node *Dequeue2(){
    if(queue_start == NULL)
        return NULL;
    Node *temp = queue_start;
    queue_start = queue_start->next;
    if(queue_start == NULL)
        queue_end = NULL;
    else{
        queue_start->prev = NULL;
    }
    Node *result = makeNode(0,0,0);
    result->row = temp->row;
    result->col = temp->col;
    result->dist = temp->dist;
    free(temp);
    return result;
}

int check(int row, int col)
{
    return row == 0 || row == n - 1 || col == 0 || col == m - 1;
}

int duyet(int r, int c)
{
    int ro[] = {1,-1,0,0};
    int co[] = {0,0,1,-1};

    Enqueue2(r,c,0);
    while(0 == 0)
    {
        Node *temp = Dequeue2();
        if(temp != NULL)
        {
            int rt = temp->row;
            int ct = temp->col;
            int dt = temp->dist;
            free(temp);
            if(check(rt, ct) == 1)
                return dt+1;
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    int newr = rt + ro[i];
                    int newc = ct + co[i];
                    if(newr >= 0 && newr < n && newc >= 0 && newc < m && 
                       a[newr][newc] == 0 && marker[newr][newc] == 0 )
                        Enqueue2(newr, newc, dt + 1);
                }
            }
        }
        else
            return -1;
    }
    
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &r, &c);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    int result = duyet(r-1, c-1);
    printf("%d", result);
    return 0;
}