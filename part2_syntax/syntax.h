#ifndef SYNTAX_H_INCLUDED
#define SYNTAX_H_INCLUDED
#include "../part1_lexic/lexic.h"

Arbre analyse_syntaxe(/*typejeton* tableau_jeton, int taille,*/ char* fonction_string);
typejeton* subtab(typejeton* tableau_jeton, int index_deb, int index_fin);
Arbre creation_noeud(typejeton* tableau_jeton, int taille);
int indice_operateur(typejeton* tableau_jeton, int taille);
int indice_derniere_par_ferm(typejeton* tableau_jeton, int taille,int indic_par_ouv);
void afficher_arbre(Arbre arbre);
#endif // SYNTAX_H_INCLUDED
