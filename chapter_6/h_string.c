#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 10000

int n;
long long m;

long long h(char *k)
{
    long long result = 0;
    long long temp = 1;
    for(int i = strlen(k) - 1; i >= 0; i--){
        long long b = k[i] * temp % m;
        result = result + b;
        temp = temp * 256 % m;
    }
    return result % m;
}


int main()
{
    scanf("%d %lld", &n, &m);
    for(int i = 0; i < n; i++){
        char str[MAX];
        scanf("%s", str);
        printf("%lld\n", h(str));
    }
    return 0;
}