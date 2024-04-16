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

bool check(int i, int k)
{
    if(k == 0)
        return true;
    else if((a[k - 1] == 1 && i == 1))
        return false;
    else
        return true;
}


void try(int k)
{
    for(int i = 0; i <= 1; i++)
    {
        if(check(i, k))
        {
            a[k] = i;
            if(k == n - 1) printfSolution();
            else try(k+1);
            a[k] = -1;
        }
    }
}

int main()
{
    scanf("%d", &n);
    try(0);
    return 0;
}
