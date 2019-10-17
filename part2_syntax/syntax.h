#ifndef SYNTAX_H_INCLUDED
#define SYNTAX_H_INCLUDED
#include "../jeton.h"

Arbre analyse_syntaxe(typejeton* tableau_jeton, int taille);
typejeton* subtab(typejeton* tableau_jeton, int index_deb, int index_fin);
Arbre creation_noeud(typejeton* tableau_jeton, int taille);
int indice_operateur(typejeton* tableau_jeton, int taille);
int indice_derniere_par_ferm(typejeton* tableau_jeton, int taille);
#endif // SYNTAX_H_INCLUDED
