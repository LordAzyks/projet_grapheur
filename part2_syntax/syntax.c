#include <stdio.h>
#include <stdlib.h>
#include "../jeton.h"
#include "./syntax.h"

//On recoit en entr�e un tableau de typejeton

Arbre analyse_syntaxe(typejeton* tableau_jeton, int taille)
{
    Arbre arbre = creation_noeud(tableau_jeton,taille);

    return arbre;
}

Arbre creation_noeud(typejeton* tableau_jeton, int taille)
{
    printf("\njeton courant:lexem %d",tableau_jeton[0].lexem);
    if (tableau_jeton[0].lexem==FIN)
        return NULL;

    Arbre noeud_courant = (Arbre)malloc(sizeof(Node));
    noeud_courant->pjeton_preced = NULL;
    noeud_courant->pjeton_suiv   = NULL;
    int ind_operateur,ind_par_ferm;
    switch(tableau_jeton[0].lexem)
    {
        case REEL       :
            printf("\nREEL");
            ind_operateur = indice_operateur(tableau_jeton,taille);
            if (ind_operateur==-1)
            {
                noeud_courant->jeton = tableau_jeton[0];
            }
            else
            {
                noeud_courant->jeton = tableau_jeton[ind_operateur];
                noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton,0,ind_operateur),ind_operateur+1);

                noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton,ind_operateur+1,taille),taille-ind_operateur);
                printf("\nprec:%d\tsuiv:%d",noeud_courant->pjeton_preced->jeton.lexem,noeud_courant->pjeton_suiv->jeton.lexem);
            }
            break;
        case OPERATEUR  : break;
        case FONCTION   :
            printf("\nFONCTION");
            if (tableau_jeton[1].lexem!=PAR_OUV)
            {
                noeud_courant->jeton = (typejeton){ERREUR,  {0,NULL,NULL,SYNTAX_ERR}};
                printf("\nlexem exit : %d",tableau_jeton[1].lexem);
                exit(1);
            }
            ind_par_ferm = indice_derniere_par_ferm(tableau_jeton,taille,1);

            if (tableau_jeton[ind_par_ferm+1].lexem!=FIN)
            {
                if (tableau_jeton[ind_par_ferm+1].lexem!=OPERATEUR)
                {
                    noeud_courant->jeton = (typejeton){ERREUR,  {0,NULL,NULL,SYNTAX_ERR}};
                    exit(1);
                }

                noeud_courant->jeton = tableau_jeton[ind_par_ferm+1];
                noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton,0,ind_par_ferm+1),ind_par_ferm+2);
                noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton,ind_par_ferm+2,taille),taille-ind_par_ferm-1);
            }
            else
            {
                printf("\nNON");
                noeud_courant->jeton = tableau_jeton[0];
                noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton,2,ind_par_ferm),ind_par_ferm-1);
            }//sqrt(25)*x


            break;
        case ERREUR     : break;
        case FIN        : break;
        case PAR_OUV    :
            printf("\nPAR_OUV");
            ind_par_ferm=indice_derniere_par_ferm(tableau_jeton,taille,0);
            if (tableau_jeton[ind_par_ferm+1].lexem==OPERATEUR)
            {
                noeud_courant->jeton = tableau_jeton[ind_par_ferm+1];
                noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton,1,ind_par_ferm),ind_par_ferm);

                noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton,ind_par_ferm+2,taille),taille-ind_par_ferm-1);
            }
            if (tableau_jeton[ind_par_ferm+1].lexem==FIN)
            {
                free(noeud_courant);
                noeud_courant = creation_noeud(subtab(tableau_jeton,1,taille-1),taille+1);
            }
            break;
        case PAR_FERM   : break;
        case VARIABLE   :
            printf("\nVARIABLE");
            ind_operateur = indice_operateur(tableau_jeton,taille);
            if (ind_operateur==-1)
            {
                noeud_courant->jeton = tableau_jeton[0];
            }
            else
            {
                noeud_courant->jeton = tableau_jeton[ind_operateur];
                noeud_courant->pjeton_preced = creation_noeud(subtab(tableau_jeton,0,ind_operateur),ind_operateur+1);
                noeud_courant->pjeton_suiv = creation_noeud(subtab(tableau_jeton,ind_operateur+1,taille),ind_operateur+2);
            }
            break;
        case BAR_OUV    : break;
        case BAR_FER    : break;
        case ABSOLU     : break;
        default : printf("\nPas normal");
    }

    return noeud_courant;
}

typejeton* subtab(typejeton* tableau_jeton, int index_deb, int index_fin)
{
    typejeton* subtableau = (typejeton*)malloc(sizeof(typejeton)*(index_fin-index_deb+1));
    int i_jeton;
    for (i_jeton=index_deb; i_jeton<index_fin+1;i_jeton++)
    {
        if (i_jeton==index_fin)
            subtableau[i_jeton-index_deb] = (typejeton){FIN,{0,NULL,NULL,NULL}};
        else
        {
            subtableau[i_jeton-index_deb] = tableau_jeton[i_jeton];
            if (subtableau[i_jeton-index_deb].lexem==FIN)
                break;
        }

    }

    return subtableau;
}

int indice_derniere_par_ferm(typejeton* tableau_jeton, int taille,int indic_par_ouv)
{
    int nb_par_ouv=0;
    int indice_para_ferm=-1;
    int i_jeton;
    for (i_jeton=taille-1;i_jeton>=0;i_jeton--)
    {
        if (tableau_jeton[i_jeton].lexem==PAR_OUV)
        {
            nb_par_ouv++;
        }
        if (tableau_jeton[i_jeton].lexem==PAR_FERM)
        {
            if (nb_par_ouv==0)
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

int indice_operateur(typejeton* tableau_jeton, int taille) //return -1 si pas d'operateur
{
    int indice_operateur=-1;
    int i_jeton;
    for (i_jeton=0; i_jeton<taille-1; i_jeton++)
    {
        if (tableau_jeton[i_jeton].lexem==OPERATEUR)
        {
            indice_operateur = i_jeton;
            break;
        }
    }

    return indice_operateur;
}



