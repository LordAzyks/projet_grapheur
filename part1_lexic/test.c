#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexic.h"

int main(void)
{
    char test[] = "sin(220.20)";
    format_text(test);
    decoupe_saisie(test);
    //printf("origine %s\n", test);
    return 0;
}
