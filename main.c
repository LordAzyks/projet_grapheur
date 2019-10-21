#include "header.h"
#include "part3_evelua/evalua.h"

int main() {
    printf("Hello le grapheur !\n");
    
    Arbre racine = (Arbre)malloc(sizeof(Node));
    racine->jeton.valeur.operateur = PLUS;
    
    Arbre rc = (Arbre)malloc(sizeof(Node));
    rc->jeton.valeur.fonction = FOIS;
    
    Arbre x = (Arbre)malloc(sizeof(Node));
    x->jeton.lexem = VARIABLE;
    x->pjeton_preced = NULL;
    x->pjeton_suiv = NULL;
    
    Arbre vc = (Arbre)malloc(sizeof(Node));
    vc->jeton.lexem = REEL;
    vc->jeton.valeur.reel = 55;
    vc->pjeton_preced = NULL;
    vc->pjeton_suiv = NULL;
    
    rc->pjeton_preced = vc;
    rc->pjeton_suiv = x;    
    
    Arbre neg = (Arbre)malloc(sizeof(Node));
    neg->jeton.lexem = REEL;
    neg->jeton.valeur.reel = 4;
    neg->pjeton_preced = NULL;
    neg->pjeton_suiv = NULL;
    
    Arbre ab = (Arbre)malloc(sizeof(Node));
    ab->jeton.valeur.operateur = PLUS;
    ab->pjeton_preced = vc;
    ab->pjeton_suiv = x;

	 rc->pjeton_preced = ab;
    rc->pjeton_suiv = neg;  
    
    racine->pjeton_preced = rc;
    racine->pjeton_suiv = NULL;
    
    float resultat = preffixeArbre(racine,1);
    printf("Le resultat est %f\n",resultat);
    
    calculValeur(-1,1,0.1,racine);

    return 0;
}