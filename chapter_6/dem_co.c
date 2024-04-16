#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

int arr[MAX] = { 0 };
int n, m;

void merge(int l, int m, int r)
{
    int tmp1 = l;
    int tmp2 = m + 1;
    int tmp = l;
    int *b = (int*)malloc((r - l + 1) * sizeof(int));
    int index = 0;
    while(tmp1 <= m && tmp2 <= r)
    {
        b[index++] = arr[tmp1] < arr[tmp2] ? arr[tmp1++] : arr[tmp2++];
    }
    while(tmp1 <= m)
    {
        b[index++] = arr[tmp1++];
    }
    while(tmp2 <= r)
    {
        b[index++] = arr[tmp2++];
    }
    memcpy(arr + l, b, (r - l + 1) * sizeof(int));
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

int find(int k)
{
    int max = n - 1;
    int min = 0;
    int mid = 0;
    while(max >= min)
    {
        mid = (max + min) / 2;
        if(arr[mid] == k)
        {
            return mid;
        }
        else if(arr[mid] > k)
        {
            max = mid - 1;
        }
        else
        {
            min = mid + 1;
        }
    }

    return max;
}

int main()
{
    freopen("D:\\code\\ip.txt", "rt", stdin);
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    mergeSort(0, n - 1);
    int maxArray = arr[n - 1];
    int a, b;
    while(m > 0)
    {
        scanf("%d %d", &a, &b);
        int tmp1 = find(a - 1) + 1;
        int tmp2 = find(b);
        printf("%d\n", tmp2 - tmp1 + 1);
        m--;
    }
    return 0;
}