#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexic.h"

int main(void)
{
    char test[] = "sin(220.20)";
    decoupe_saisie(test);
    //format_text(test);
    //printf("origine %s\n", test);
    return 0;
}
