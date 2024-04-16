// Data:
// AI
// Artificial Intelligence
// Recently, AI is a key technology. AI enable efficient operations in many fields.
// Output
// Recently, Artificial Intelligence is a key technology. Artificial Intelligence enable efficient operations in many fields.

#include <stdio.h>
#include <string.h>


int main()
{
    char str1[1000], str2[1000], str3[1000], kq[1000] = "";
    fgets(str1, sizeof(str1), stdin);
    str1[strlen(str1) - 1] = '\0';
    fgets(str2, sizeof(str2), stdin);
    str2[strlen(str2) - 1] = '\0';
    fgets(str3, sizeof(str3), stdin);
    str3[strlen(str3) - 1] = '\0';

    char *p1 = str3, a[1000] = { 0 };
    char *p2 = strstr(p1, str1);
    while(p2 != NULL)
    {   
        strncpy(a, p1, p2 - p1);
        p1 = p2;
        p1 += strlen(str1) + 1;
        strcat(kq, a);
        strcat(kq, str2);
        strcat(kq, " ");
        p2 = strstr(p1, str1);
    }
    strcat(kq, p1);
    printf("%s", kq);
    return 0;
}