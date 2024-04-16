#include <stdio.h>
#include <stdbool.h>

#define N 10000
int a[N] = { -1 }, n;

void printfSolution()
{
    for(int i = 0; i < n; i++)
        printf("%d", a[i]);
    printf("\n");
}

void try(int k)
{
    for(int i = 0; i <= 1; i++)
    {
        a[k] = i;
        if(k == n - 1) printfSolution();
        else try(k+1);
        a[k] = -1;
    }
}

int main()
{
    scanf("%d", &n);
    try(0);
    return 0;
}
