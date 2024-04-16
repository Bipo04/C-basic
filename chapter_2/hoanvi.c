#include <stdio.h>
#define N 100
int n;
int k;
int a[N] = { 0 }, b[N] = { 0 };
int cnt;

void solution(){
    for(int i = 1; i <= n; i++) 
        printf("%d ", a[i]);
    printf("\n");
}

void Try(int j){
    for(int i = 1; i <= n; i++){
        if(b[i] == 0){
            a[j] = i;
            b[i] = 1;
            if (j == n) 
                solution();
            else
                Try(j+1);
            a[j] = 0;
            b[i] = 0;
        }
    }
}

int main(){
    n = 3;
    Try(1);
    return 0;
}