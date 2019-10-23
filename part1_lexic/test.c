#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexic.h"

int main(void)
{
    char test[] = "sin(220.203 + 20)";
    int taille ;
    format_text(test);
    decoupe_saisie(test,&taille);
    printf("taille %d\n", taille);
    return 0;
}
