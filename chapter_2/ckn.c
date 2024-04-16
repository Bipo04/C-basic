#include <stdio.h>
#include <math.h>

#define N 1000

int k1, n1;
long long a[N][N] = { 0 };

long long C(int k, int n)
{
    if(k == 0 || k == n)
        a[k][n] = 1;
    else if(a[k][n] == 0)
        a[k][n] = (C(k-1, n-1) + C(k, n-1)) %1000000007;
    return a[k][n];
}
int main()
{
    scanf("%d %d", &k1, &n1);
    printf("%lld", C(k1, n1));
    return 0;
}