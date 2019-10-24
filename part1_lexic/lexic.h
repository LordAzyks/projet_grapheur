#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../jeton.h"

void format_text(char *origine);
typejeton* decoupe_saisie(char *entree, int *taille_jeton);
typejeton* creation_jeton(typejeton **tableauJeton, typelexem lexem, typevaleur valeur, int *taille);