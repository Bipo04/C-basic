#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

int a[MAX] = { 0 };


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

int binarySearch(int k, int l, int r)
{
    int tmpL = l;
    int tmpR = r;
    while(0 == 0)
    {
        if(tmpL == tmpR)
            return k == a[tmpL];
        else if(tmpL == tmpR - 1)
            return k == a[tmpL] || k == a[tmpR];
        else
        {
            int mid = (tmpL + tmpR) / 2;
            if(a[mid] == k)
                return 1;
            else if(a[mid] > k)
            {
                tmpR = mid - 1;
            }
            else
            {
                tmpL = mid + 1;
            }
        }
    }
}

int main()
{
    int n, Q, cnt = 0;
    scanf("%d %d", &n, &Q);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    mergeSort(0, n - 1);
    for(int i = 0; i < n - 1; i++)
    {
        if(binarySearch(Q - a[i], i + 1, n - 1) == 1)
        {
            cnt++;
        }
    }
    printf("%d", cnt);
    return 0;
}