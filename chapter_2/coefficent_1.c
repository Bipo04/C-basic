#include <stdio.h>

#define N 1000

int a[N], sum = 0;
int n, m;

void printSolution()
{
    for(int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void try(int k)
{
    for(int i = 1; i <= m - sum -(n - k); i++)
    {
        a[k] = i;
        sum += i;
        if(k == n)
        {
            if(sum == m)
                printSolution();
        }
        else
            try(k+1);
        a[k] = 0;
        sum -= i;
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    try(1);
    return 0;
}