#include "./syntax.h"

// utilisé pour le debug, fonction d'affichage d'un jeton
void afficher_typejeton(typejeton jeton)
{
    //printf("\n--==JETON==--");
    switch (jeton.lexem)
    { //REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FER,ABSOLU
    case 0:
        printf("\nREEL");
        break;
    case 1:
        printf("\nOPERATEUR");
        break;
    case 2:
        printf("\nFONCTION");
        break;
    case 3:
        printf("\nERREUR");
        break;
    case 4:
        printf("\nFIN");
        break;
    case 5:
        printf("\nPAR_OUV");
        break;
    case 6:
        printf("\nPAR_FERM");
        break;
    case 7:
        printf("\nVARIABLE");
        break;
    case 8:
        printf("\nBAR_OUV");
        break;
    case 9:
        printf("\nBAR_FER");
        break;
    case 10:
        printf("\nABSOLU");
        break;
    default:
        printf("AUTRE");
        break;
    }
    switch (jeton.lexem)
    { //REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FER,ABSOLU
    case 0:
        printf("\nvaleur : %f", jeton.valeur.reel);
        break;
    case 1:
        printf("\nvaleur : %d", jeton.valeur.operateur);
        break;
    case 2:
        printf("\nvaleur : %f", jeton.valeur.reel);
        break;
    case 3:
        printf("\nvaleur : %d", jeton.valeur.erreur);
        break;
    default:
        printf("\nPas de valeur");
    }
    printf("\n--=======--");
}


//Entrée principale dans la partie syntaxique
Arbre analyse_syntaxe(/*typejeton* tableau_jeton, int taille,*/ char *fonction_string)
{
    int taille;
    typejeton *tableau_jeton;
    tableau_jeton = decoupe_saisie(fonction_string, &taille);//Appel à la partie lexicale

    Arbre arbre = creation_noeud(tableau_jeton, taille);
    return arbre;
}

//Fonction de debug, affiche le tableau de jeton
void afficher_tabjeton(typejeton *tableau_jeton, int taille)
{
    printf("\n");

    int i_jeton = 0;
    for (i_jeton = 0; i_jeton < taille; i_jeton++)
    {
        printf("\n--==JETON %d==--", i_jeton);
        printf("[%d]", tableau_jeton[i_jeton].lexem);
        afficher_typejeton(tableau_jeton[i_jeton]);
    }
}

//Fonction recursive de création de noeud
Arbre creation_noeud(typejeton *tableau_jeton, int taille)
{
    // afficher_typejeton(tableau_jeton[0]);
    if (tableau_jeton[0].lexem == FIN)
        return NULL;

    // afficher_tabjeton(tableau_jeton, taille);
    Arbre noeud_courant = (Arbre)malloc(sizeof(Node));
    noeud_courant->pjeton_preced = NULL;
    noeud_courant->pjeton_suiv = NULL;
    int ind_operateur, ind_par_ferm;
    switch (tableau_jeton[0].lexem)
    {
    case REEL:
        // printf("\nREEL");
        ind_operateur = indice_operateur(tableau_jeton, taille);
        if (ind_operateur == -1)
        {
            noeud_courant->jeton = tableau_jeton[0];
        }
        else
        {
            noeud_courant->jeton = tableau_jeton[ind_operateur];
            noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton, 0, ind_operateur), ind_operateur + 1);

            noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton, ind_operateur + 1, taille), taille - ind_operateur);
            // printf("\nprec:%d\tsuiv:%d", noeud_courant->pjeton_preced->jeton.lexem, noeud_courant->pjeton_suiv->jeton.lexem);
        }
        break;
    case FONCTION:
        if (tableau_jeton[1].lexem != PAR_OUV)
        {
            noeud_courant->jeton = (typejeton){ERREUR};
            noeud_courant->jeton.valeur = (typevaleur){.reel = 0, .fonction = -1, .operateur = -1, .erreur = SYNTAX_ERR};
            // printf("\nlexem exit : %d", tableau_jeton[1].lexem);
            printf("Erreur : parenthèse ouvrante de fonction manquante.\n");
            break;
        }
        ind_par_ferm = indice_derniere_par_ferm(tableau_jeton, taille, 1);
        if (ind_par_ferm == -1) {
            printf("Erreur : Parenthèse fermante manquante.\n");
            break;
        }
        if (tableau_jeton[ind_par_ferm + 1].lexem != FIN)
        {
            if (tableau_jeton[ind_par_ferm + 1].lexem != OPERATEUR)
            {
                noeud_courant->jeton = (typejeton){ERREUR};
                noeud_courant->jeton.valeur = (typevaleur){.reel = 0, .fonction = -1, .operateur = -1, .erreur = SYNTAX_ERR};
                printf("Erreur : opérateur manquant.\n");
                break;
            }

            noeud_courant->jeton = tableau_jeton[ind_par_ferm + 1];
            noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton, 0, ind_par_ferm + 1), ind_par_ferm + 2);
            noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton, ind_par_ferm + 2, taille), taille - ind_par_ferm - 1);
        }
        else
        {
            // printf("\nNON");
            noeud_courant->jeton = tableau_jeton[0];
            //noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton,2,ind_par_ferm),ind_par_ferm-1);
            noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton, 2, ind_par_ferm), ind_par_ferm - 1);
        } //sqrt(25)*x

        break;
    case FIN:
        printf("Erreur : opérande manquant.\n");
        break;
    case PAR_OUV:
        ind_par_ferm = indice_derniere_par_ferm(tableau_jeton, taille, 0);
        
        if (ind_par_ferm == -1) {
            printf("Erreur : Parenthèse fermante manquante.\n");
            break;
        }
        if (tableau_jeton[ind_par_ferm + 1].lexem == OPERATEUR)
        {
            // printf("\nPAR_OUV OUI %d", ind_par_ferm);
            noeud_courant->jeton = tableau_jeton[ind_par_ferm + 1];
            noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton, 1, ind_par_ferm), ind_par_ferm);
            noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton, ind_par_ferm + 2, taille), taille - ind_par_ferm);
        }
        if (tableau_jeton[ind_par_ferm + 1].lexem == FIN)
        {
            // printf("\nPAR_OUV NON %d", ind_par_ferm);
            free(noeud_courant);
            noeud_courant = creation_noeud(subtab(tableau_jeton, 1, ind_par_ferm), ind_par_ferm);
        }
        break;
    case PAR_FERM:
        break;
    case VARIABLE:
        // printf("\nVARIABLE");
        ind_operateur = indice_operateur(tableau_jeton, taille);
        if (ind_operateur != 1 && ind_operateur != -1)
        {
            printf("Erreur : opérateur manquant.\n");
            break;
        }

        if (ind_operateur == -1)
        {
            noeud_courant->jeton = tableau_jeton[0];
        }
        else
        {
            noeud_courant->jeton = tableau_jeton[ind_operateur];
            noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton, 0, ind_operateur), ind_operateur + 1);
            noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton, ind_operateur + 1, taille), taille - ind_operateur);
        }
        break;
    case BAR_OUV:
        break;
    case BAR_FER:
        break;
    case ABSOLU:
        break;
    case ERREUR:
        break;
    case OPERATEUR:
        break;
    default:
        printf("\nErreur : lexem inconnu.\n");
    }

    return noeud_courant;
}

//Crée un sous tableau de tableau_jeton[index_deb] à tableau_jeton[index_fin]
typejeton *subtab(typejeton *tableau_jeton, int index_deb, int index_fin)
{
    typejeton *subtableau = (typejeton *)malloc(sizeof(typejeton) * (index_fin - index_deb + 1));
    int i_jeton;
    for (i_jeton = index_deb; i_jeton < index_fin + 1; i_jeton++)
    {
        if (i_jeton == index_fin) {
            subtableau[i_jeton - index_deb] = (typejeton){FIN};
            subtableau[i_jeton - index_deb].valeur = (typevaleur) {.reel = 0, .fonction = -1, .operateur = -1, .erreur = -1};
        }
        else
        {
            subtableau[i_jeton - index_deb] = tableau_jeton[i_jeton];
            if (subtableau[i_jeton - index_deb].lexem == FIN)
                break;
        }
    }

    return subtableau;
}

//Retourne l'indice dans le tableau de la parenthese fermante correspondante à la parenthese ouvrante donnée en parametre
int indice_derniere_par_ferm(typejeton *tableau_jeton, int taille, int indic_par_ouv)
{
    int nb_par_ouv = 0;
    int indice_para_ferm = -1;
    int i_jeton;
    for (i_jeton = indic_par_ouv + 1; i_jeton < taille - 1; i_jeton++)
    {
        if (tableau_jeton[i_jeton].lexem == PAR_OUV)
        {
            nb_par_ouv++;
        }
        if (tableau_jeton[i_jeton].lexem == PAR_FERM)
        {
            if (nb_par_ouv == 0)
            {
                indice_para_ferm = i_jeton;
                break;
            }
            else
            {
                nb_par_ouv--;
            }
        }
    }
    return indice_para_ferm;
}

//Retounre l'indice de l'operateur de meme niveau
int indice_operateur(typejeton *tableau_jeton, int taille) //return -1 si pas d'operateur
{
    int indice_operateur = -1;
    int i_jeton;
    for (i_jeton = 0; i_jeton < taille - 1; i_jeton++)
    {
        if (tableau_jeton[i_jeton].lexem == OPERATEUR)
        {
            indice_operateur = i_jeton;
            break;
        }
    }

    return indice_operateur;
}

//fonction de debug, affiche l'arbre
void afficher_arbre(Arbre arbre)
{
    switch (arbre->jeton.lexem)
    {
    case REEL:
        printf("REEL[%f]", arbre->jeton.valeur.reel);
        break;
    case OPERATEUR:
        printf("OPERATEUR[%d]", arbre->jeton.valeur.operateur);
        break;
    case FONCTION:
        printf("FONCTION[%d]", arbre->jeton.valeur.fonction);
        break;
    case ERREUR:
        printf("ERREUR[%d]", arbre->jeton.valeur.erreur);
        break;
    case FIN:
        printf("FIN");
        break;
    case PAR_OUV:
        printf("PAR_OUV");
        break;
    case PAR_FERM:
        printf("PAR_FERM");
        break;
    case VARIABLE:
        printf("VARIABLE");
        break;
    case BAR_OUV:
        printf("BAR_OUV");
        break;
    case BAR_FER:
        printf("BAR_FER");
        break;
    case ABSOLU:
        printf("ABSOLU");
        break;
    }

    if (arbre->pjeton_preced != NULL)
    {
        switch (arbre->pjeton_preced->jeton.lexem)
        {
        case REEL:
            printf(" PREC:REEL[%f]", arbre->pjeton_preced->jeton.valeur.reel);
            break;
        case OPERATEUR:
            printf(" PREC:OPERATEUR[%d]", arbre->pjeton_preced->jeton.valeur.operateur);
            break;
        case FONCTION:
            printf(" PREC:FONCTION[%d]", arbre->pjeton_preced->jeton.valeur.fonction);
            break;
        case ERREUR:
            printf(" PREC:ERREUR[%d]", arbre->pjeton_preced->jeton.valeur.erreur);
            break;
        case FIN:
            printf(" PREC:FIN");
            break;
        case PAR_OUV:
            printf(" PREC:PAR_OUV");
            break;
        case PAR_FERM:
            printf(" PREC:PAR_FERM");
            break;
        case VARIABLE:
            printf(" PREC:VARIABLE");
            break;
        case BAR_OUV:
            printf(" PREC:BAR_OUV");
            break;
        case BAR_FER:
            printf(" PREC:BAR_FER");
            break;
        case ABSOLU:
            printf(" PREC:ABSOLU");
            break;
        }
    }
    else
        printf(" PREC:NULL");

    if (arbre->pjeton_suiv != NULL)
    {
        switch (arbre->pjeton_suiv->jeton.lexem)
        {
        case REEL:
            printf(" SUIV:REEL[%f]\n", arbre->pjeton_suiv->jeton.valeur.reel);
            break;
        case OPERATEUR:
            printf(" SUIV:OPERATEUR[%d]\n", arbre->pjeton_suiv->jeton.valeur.operateur);
            break;
        case FONCTION:
            printf(" SUIV:FONCTION[%f]", arbre->pjeton_suiv->jeton.valeur.reel);
            break;
        case ERREUR:
            printf(" SUIV:ERREUR[%d]\n", arbre->pjeton_suiv->jeton.valeur.erreur);
            break;
        case FIN:
            printf(" SUIV:FIN\n");
            break;
        case PAR_OUV:
            printf(" SUIV:PAR_OUV\n");
            break;
        case PAR_FERM:
            printf(" SUIV:PAR_FERM\n");
            break;
        case VARIABLE:
            printf(" SUIV:VARIABLE\n");
            break;
        case BAR_OUV:
            printf(" SUIV:BAR_OUV\n");
            break;
        case BAR_FER:
            printf(" SUIV:BAR_FER\n");
            break;
        case ABSOLU:
            printf(" SUIV:ABSOLU\n");
            break;
        }
    }
    else
        printf(" SUIV:NULL\n");

    if (arbre->pjeton_preced != NULL)
        afficher_arbre(arbre->pjeton_preced);
    if (arbre->pjeton_suiv != NULL)
        afficher_arbre(arbre->pjeton_suiv);
}
