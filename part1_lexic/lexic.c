#include "lexic.h"

char *minuscule(char *origine){

    char *resultat = malloc(sizeof(char) * strlen(origine));

    for (int i = 0; i<strlen(origine); i++){
        if(origine[i] >='A' && origine[i]<='Z'){
            // C'est une majuscule
            resultat[i] = (origine[i]+32);
        } else if(origine[i] >='a' && origine[i]<='z') {
            // C'est une minuscule
            resultat[i] = origine[i];
        } else {
            // C'est un opérateur
            resultat[i] = origine[i];
        }
    }
    return resultat;
}



int main(){

    char *chaine = "BoNjOuR ! = Sin - + COnnarD !" ;
    printf("\n Phrase avant moulinette : %s", chaine);
    chaine = minuscule(chaine);
    printf("\n Phrase apres moulinette : %s \n", chaine);
    //free(chaine);

    return 0;
}