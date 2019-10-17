#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void trim(char *origine)
{
    int count = 0;

    for (int i = 0; origine[i]; i++)
    {
        origine[i] = tolower(origine[i]);
        if (origine[i] != ' ')
            origine[count++] = origine[i];
    }
    origine[count] = '\0';
}

int main(void)
{
    char test[] = "test coucou tetetEEEEEetetet ewqewqe ";
    trim(test);
    printf("origine %s\n", test);
    return 0;
}
