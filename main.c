#include "header.h"
#include "part3_evelua/evalua.h"

int main(int argc, char** argv) {

    printf("Hello le grapheur !\n");
    /*
    Arbre racine = (Arbre)malloc(sizeof(Node));
    racine->jeton.valeur.fonction = SQRT;

    Arbre cosinus = (Arbre)malloc(sizeof(Node));
    cosinus->jeton.valeur.fonction = COS;

    Arbre moins = (Arbre)malloc(sizeof(Node));
    moins->jeton.valeur.operateur = MOINS;

    Arbre fois = (Arbre)malloc(sizeof(Node));
    fois->jeton.valeur.operateur = FOIS;

    Arbre plus = (Arbre)malloc(sizeof(Node));
    plus->jeton.valeur.operateur = PLUS;

    Arbre puis = (Arbre)malloc(sizeof(Node));
    puis->jeton.valeur.operateur = PUIS;

    Arbre x = (Arbre)malloc(sizeof(Node));
    x->jeton.lexem = VARIABLE;

    Arbre cinq = (Arbre)malloc(sizeof(Node));
    cinq->jeton.lexem = REEL;
    cinq->jeton.valeur.reel = 5;
    cinq->pjeton_preced = NULL;
    cinq->pjeton_suiv = NULL;

    Arbre deux = (Arbre)malloc(sizeof(Node));
    deux->jeton.lexem = REEL;
    deux->jeton.valeur.reel = 2;
    deux->pjeton_preced = NULL;
    deux->pjeton_suiv = NULL;

    puis->pjeton_preced = x;
    puis->pjeton_suiv = deux;
    cosinus->pjeton_preced = puis;
    cosinus->pjeton_suiv = NULL;
    plus->pjeton_preced = cosinus;
    plus->pjeton_suiv = cinq;
    fois->pjeton_preced = cinq;
    fois->pjeton_suiv = x;
    moins->pjeton_preced = plus;
    moins->pjeton_suiv = fois;
    racine->pjeton_preced = moins;
    racine->pjeton_suiv = NULL;

    afficher_arbre(racine);
    //Arbre racine = analyse_syntaxe("sin(220.203+20)");
    float resultat = prefixeArbre(racine,1);
    printf("Le resultat est %f\n",resultat);


    float **tableauExemple1;
    tableauExemple1 = calculValeur(-5,5,0.1,racine);

    float tableauExemple2[2][101] = {{-5,-4.9,-4.8,-4.7,-4.6,-4.5,-4.4,-4.3,-4.2,-4.1,-4,
    											-3.9,-3.8,-3.7,-3.6,-3.5,-3.4,-3.3,-3.2,-3.1,-3,
    											-2.9,-2.8,-2.7,-2.6,-2.5,-2.4,-2.3,-2.2,-2.1,-2,
    											-1.9,-1.8,-1.7,-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1,
    											-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,
    											0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,
    											1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,
    											2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,
    											3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,
    											4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5},
    										{5,4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,
    											4.5,4.8,4.2,4.9,4.7,4.2,4.9,2,2.3,2.7,}};
    */

    //Test avec l'arbre créé par la partie 2
    float borneMin = -5.0;
    float borneMax = 5.0;
    float pas = 1.0;
    float** tab;
    if (argc==2)
        tab = calculValeur(-5.0, 5.0, 1.0, argv[1]);
    else
        tab = calculValeur(-5.0, 5.0, 1.0, "sin(x+2)");
    int i = (borneMax - borneMin) / pas;
    while(i--){
        printf("x=%f, y=%f\n",tab[i][0],tab[i][1]);
    }


    return 0;
}
