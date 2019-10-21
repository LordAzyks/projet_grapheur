#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../jeton.h"

void format_text(char *origine);
typejeton* decoupe_saisie(char *entree);
typejeton* creation_jeton(typejeton **tableauJeton, typelexem lexem, typevaleur valeur, int *taille);