#include <stdio.h>

int main()
{
    char buff[200];
    fgets(buff , sizeof(buff), stdin);
    printf("%s\n",buff);
}