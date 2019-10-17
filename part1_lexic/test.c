#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexic.h"

int main(void)
{
    char test[] = "test coucou tetetEEEEEetetet ewqewqe ";
    format_text(test);
    printf("origine %s\n", test);
    return 0;
}
