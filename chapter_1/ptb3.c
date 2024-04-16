#include <stdio.h>
#include <math.h>

void sapxep(int a[], int n)
{
    for(int i = 0 ; i < n - 1; i++){
        for(int j = i; j < n; j++){
            if(a[i] > a[j]){
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
int main()
{
    int a1, b1, c1;
    scanf("%d %d %d", &a1, &b1, &c1);
    
    double x,y = 0;
    do
    {
        x = y;
        y = x - ((x*x*x + a1*x*x + b1*x + c1)/(3*x*x + 2*a1*x + b1));
    } while (fabs(x-y)>0.00001);
    
    int d = round(y);
    //chia pt cho x-d tro thanh x*x + (a+d)*x + (b+a*d+d*d)
    int a = 1, b = a1+d, c = b1+a1*d+d*d;
    int delta = b*b - 4*a*c;
    if(delta < 0)
        printf("NO SOLUTION");
    else if(delta == 0)
    {
        int e = -b/(2*a);
        d < e ? printf("%d 1\n%d 2", d, e) : printf("%d 2\n%d 1", e, d);
    }
    else
    {
        float x1 = (-b - sqrt(delta))/(2*a);
        float x2 = (-b + sqrt(delta))/(2*a);
        int e = round(x1), f = round(x2);
        int a[3];
        a[0] = d;
        a[1] = e;
        a[2] = f;
        sapxep(a, 3);
        printf("%d 1\n%d 1\n%d 1", a[0], a[1], a[2]);
    }
    return 0;
}