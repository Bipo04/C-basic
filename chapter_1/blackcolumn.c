#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        a[i] = (int *)malloc(m * sizeof(int));
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    int cnt = 0;
    for(int i = 0; i < m; i++)
    {
        int temp = 1;
        for(int j = 0; j < n; j++)
        {
            temp *= a[j][i];
            if(temp == 0)
                break;
        }
        if(temp != 0)
            cnt++;
    }
    free(a);
    printf("%d", cnt);
}