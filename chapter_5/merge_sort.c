#include <stdio.h>

typedef struct dt
{
    long long dau;
    long long cuoi;
} dt;

dt *T = NULL;
int n;

void merge(int l, int m, int r){
    int len1 = m - l + 1, len2 = r - m;
    dt arr1[len1], arr2[len2];
    for(int i = 0; i < len1; i++){
        arr1[i] = T[l+i];
    } 
    for(int i = 0; i < len2; i++){
        arr2[i] = T[m+1+i];
    }
    int temp = l;
    int i = 0, j = 0;
    while(i < len1 && j < len2){
        T[temp++] = arr1[i].dau < arr2[j].dau ? arr1[i++] : arr2[j++];
    }
    while(i < len1){
        T[temp++] = arr1[i++];
    }
    while(j < len2){
        T[temp++] = arr2[j++];
    }
}

void mergeSort(int l, int r){
    if(l < r){
        int m = (l+r)/2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void solve()
{
    int ok = 1;
    for(int i = 0; i < n - 1; i++)
    {
        if(T[i].cuoi > T[i + 1].dau)
        {
            printf("TRUE");
            ok = 0;
            break;
        }       
    }
    if(ok == 1)
        printf("FALSE");
}

int main()
{
    freopen("D:\\code\\ip.txt", "rt", stdin);
    scanf("%d", &n);
    T = (dt*)malloc(n*sizeof(dt));
    for(int i = 0; i < n; i++)
    {
        scanf("%lld %lld", &T[i].dau, &T[i].cuoi);
    }
    mergeSort(0, n-1);
    solve();
    return 0;
}