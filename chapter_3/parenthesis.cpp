#include <bits/stdc++.h>
#include <string>

using namespace std;

bool check(string str)
{
    stack<char> s;
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            s.push(str[i]);
        } 
        else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
        {
            if(s.empty())
            {
                return false;
            } 
            else if((str[i] == ')' && s.top() == '(') || (str[i] == ']' && 
                    s.top() == '[') || (str[i] == '}' && s.top() == '{'))
            {
                s.pop();
            } 
            else
            {
                return false;
            }
        }
    }
    return s.empty();
}

int main(){
    string str;
    cin>>str;
    if(check(str)){
        printf("1");
    } 
    else{
        printf("0");
    }
    return 0;
}