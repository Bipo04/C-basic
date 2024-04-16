#include <stdio.h>

#define MAX 100000

int arr[MAX] = { 0 };
int num = 0;
int n;

void pushUp(int k)
{
    int parent = (k - 1) / 2;
    if(parent >= 0 && arr[k] < arr[parent])
    {
        int tmp = arr[parent];
        arr[parent] = arr[k];
        arr[k] = tmp;
        pushUp(parent);
    }
}

void pushDown(int k)
{

        int left = 2*k + 1;
        int right = 2*k + 2;
        int min = k;
        if(left < num && arr[left] < arr[k])
            min = left;
        if(right < num && arr[right] < arr[min])
            min = right;
        if(min != k)
        {
            int tmp = arr[k];
            arr[k] = arr[min];
            arr[min] = tmp;
            pushDown(min);
        }

}

void enqueue(int k)
{
    arr[num] = k;
    pushUp(num);
    num++;
}

int dequeue()
{
    int tmp = arr[0];
    arr[0] = arr[num - 1];
    num--;
    pushDown(0);
    return tmp;
}

int main()
{
    freopen("D:\\code\\ip.txt", "rt", stdin);
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        enqueue(tmp);
    }
    int kq = 0;
    while(num >= 2)
    {
        int a = dequeue();
        int b = dequeue();
        enqueue(a + b);
        kq += a + b;
    }

    printf("%d", kq);


    return 0;
}