#include <stdio.h>
#include <stdlib.h>

typedef struct dt
{
    int dau;
    int cuoi;
} dt;

dt* T;
int n;

int cmpfunc(const void* a, const void* b)
{
    return ((dt*)a)->dau - ((dt*)b)->dau;
}

void solve()
{
    int ok = 1;
    for(int i = 0; i < n - 1; i++)
    {
        if(T[i].cuoi > T[i + 1].dau)
        {
            printf("TRUE");
            ok = 0;
            break;
        }       
    }
    if(ok == 1)
        printf("FALSE");
}

int main()
{
    //freopen("D:\\code\\ip.txt", "rt", stdin);
    scanf("%d", &n);
    T = (dt*)malloc(n*sizeof(dt));
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &T[i].dau, &T[i].cuoi);
    }
    qsort(T, n, sizeof(dt), cmpfunc);
    solve();
    free(T);
    return 0;
}