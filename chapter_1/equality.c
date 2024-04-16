#include <stdio.h>
#include <stdlib.h>

int check(int a[], int b[], int m)
{
    for(int i = 0; i < m; i++)
    {
        if(a[i] != b[i])
            return 0;
    }
    return 1;
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n)
    {
        int m, l; 
        scanf("%d %d", &m, &l);
        int *a = (int*)malloc(m*sizeof(int));
        int *b = (int*)malloc(l*sizeof(int));
        for(int i = 0; i < m; i++)
        {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < l; i++)
        {
            scanf("%d", &b[i]);
        }
        if(m != l)
            printf("0\n");
        else if(check(a, b, m))
            printf("1\n");
        else
            printf("0\n");
        n--;
    }
    
    return 0;
}