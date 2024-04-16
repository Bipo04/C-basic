#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check(char* str){
    char queue[1000000];
    int top = -1;
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        if (str[i] == '(' || str[i] == '[' || str[i] == '{'){
            queue[++top] = str[i];
        } 
        else if(str[i] == ')' || str[i] == ']' || str[i] == '}'){
            if(top == -1){
                return false;
            } 
            else if((str[i] == ')' && queue[top] == '(') || (str[i] == ']' && 
                     queue[top] == '[') || (str[i] == '}' && queue[top] == '{')){
                top--;
            } 
            else{
                return false;
            }
        }
    }
    return top == -1;
}

int main(){
    char str[1000000];
    scanf("%s", str);
    if(check(str)){
        printf("1");
    } 
    else{
        printf("0");
    }
    return 0;
}