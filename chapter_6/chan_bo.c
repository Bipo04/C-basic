#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

int a[MAX] = { 0 };
int n, c;

void merge(int l, int m, int r)
{
    int tmp1 = l;
    int tmp2 = m + 1;
    int tmp = l;
    int *b = (int*)malloc((r - l + 1) * sizeof(int));
    int index = 0;
    while(tmp1 <= m && tmp2 <= r)
    {
        b[index++] = a[tmp1] < a[tmp2] ? a[tmp1++] : a[tmp2++];
    }
    while(tmp1 <= m)
    {
        b[index++] = a[tmp1++];
    }
    while(tmp2 <= r)
    {
        b[index++] = a[tmp2++];
    }
    memcpy(a + l, b, (r - l + 1) * sizeof(int));
    free(b);
}

void mergeSort(int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

int solve(int v)
{
    int temp = c - 1;
    int i = 0;

    for(int j = i + 1; j < n; j++)
    {
        if(temp == 0)
            break;
        else if(a[j] - a[i] >= v)
        {
            i = j;
            temp--;
        }
    }

    return temp == 0;
}

int main()
{
    scanf("%d %d", &n, &c);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    mergeSort(0, n - 1);
    int max = a[n-1];
    int min = 0;
    int mid = 0;
    int kq;
    do
    {
        mid = (max + min) / 2;
        if(solve(mid))
        {
            kq = mid;
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    } while(max >= min);
    printf("%d", kq);
    return 0;
}