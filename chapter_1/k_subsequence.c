#include<stdio.h>

int main()
{
    int n, m;
    scanf("%d",&n);
    scanf("%d",&m);
    int a[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int sum = 0, check = 0, cnt = 0;
    for(int i = 0; i < m; i++)
    {
        sum+=a[i];
    }
    check = sum%2;
    if(check == 0)
    {
        cnt++;
    }
    for(int i = 0; i < n-m; i++)
    {
        sum-=a[i];
        sum+=a[i+m];
        check =s um%2;
    if(check == 0)
    {
        cnt++;
    }
    }
    printf("%d", cnt);
    return 0;
}