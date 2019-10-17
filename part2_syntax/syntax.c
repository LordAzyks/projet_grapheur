#include <stdio.h>
#include <stdlib.h>
#include "../jeton.h"
#include "./syntax.h"

//On recoit en entrée un tableau de typejeton

Arbre analyse_syntaxe(typejeton* tableau_jeton, int taille)
{
    int i_jeton=0;
    Arbre arbre = (Arbre)malloc(sizeof(Node));
    arbre->pjeton_preced = NULL;
    arbre->pjeton_suiv   = NULL;

    //REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FER,ABSOLU


    return arbre;
}

