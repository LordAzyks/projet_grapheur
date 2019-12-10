#include "evalua.h"

float prefixeArbre(Arbre arb, float var){
	
	//valeur	
	if(arb->pjeton_preced == NULL){ 
		if(arb->jeton.lexem == REEL) { //si la valeur est un reel
			//if(arb->jeton.valeur.reel != NULL) { //si le reel n'est pas nul, on le retourne
				return arb->jeton.valeur.reel;
			/*} else { //sinon, on retourne 0
				printf("Erreur : le reel est nul\n");
				return 0;
			}*/
		} else { //si la valeur est x, on le retourne
			return var;
		}
	} else {
		
		//fonction		
		if(arb->pjeton_suiv == NULL && arb->jeton.lexem == FONCTION){
			switch(arb->jeton.valeur.fonction){
				case ABS:
					return fabs(prefixeArbre(arb->pjeton_preced,var));
					break;
				case SIN:
					return sin(prefixeArbre(arb->pjeton_preced,var));
					break;	
				case SQRT:
					//if(prefixeArbre(arb->pjeton_preced,var)>=0) {
						return sqrt(prefixeArbre(arb->pjeton_preced,var));
					/*} else {
						printf("Erreur : impossible de trouver la racine carree d'un nombre negatif\n");
						return 0;
					}*/
					break;	
				case LOG:
					//if(prefixeArbre(arb->pjeton_preced,var)>0) {
						return log(prefixeArbre(arb->pjeton_preced,var));
					/*} else {
						printf("Erreur : la valeur pour la fonction log() est inferieure ou egale a 0\n");
						return 0;
					}*/
					break;	
				case COS:
					return cos(prefixeArbre(arb->pjeton_preced,var));
					break;	
				case TAN:
					return tan(prefixeArbre(arb->pjeton_preced,var));
					break;	
				case EXP:
					return exp(prefixeArbre(arb->pjeton_preced,var));
					break;	
				case ENTIER:
					return floor(prefixeArbre(arb->pjeton_preced,var));
					break;	
				case VAL_NEG:
					return prefixeArbre(arb->pjeton_preced,var)*(-1);
					break;	
				case SINC:
					return sin(prefixeArbre(arb->pjeton_preced,var))/prefixeArbre(arb->pjeton_preced,var);
					break;	
				default:
					return 0;
					break;			
			}
			
		//operateur		
		} else if (arb->pjeton_suiv == NULL && arb->jeton.lexem != FONCTION)
		{
			return MAXFLOAT;
		} else {
			switch(arb->jeton.valeur.operateur) {
				case PLUS:
					return prefixeArbre(arb->pjeton_preced,var)+prefixeArbre(arb->pjeton_suiv,var);
					break;
				case MOINS:
					return prefixeArbre(arb->pjeton_preced,var)-prefixeArbre(arb->pjeton_suiv,var);
					break;
				case FOIS:
					return prefixeArbre(arb->pjeton_preced,var)*prefixeArbre(arb->pjeton_suiv,var);
					break;
				case DIV:
					if(prefixeArbre(arb->pjeton_suiv,var)!=0) {
						return prefixeArbre(arb->pjeton_preced,var)/prefixeArbre(arb->pjeton_suiv,var);
					} else {
						printf("Erreur : la division par 0 est impossible\n");
						return prefixeArbre(arb->pjeton_preced,var);
					}					
					break;
				case PUIS:
					return pow(prefixeArbre(arb->pjeton_preced,var),prefixeArbre(arb->pjeton_suiv,var));
					break;
				default:
					return 0;
					break;
			}	
		}
	}
	
}

float** calculValeur(float borneMin, float borneMax, float pas, char *chaine){
	int j = 0;
	float i;
	int nbValues;
	nbValues = (borneMax-borneMin)/pas;
	//float resultat[nbValues][2];
	float** resultats;
	resultats = (float**)malloc((nbValues+2)*sizeof(float*));
	Arbre tree = analyse_syntaxe(chaine);
	// printf("BorneMin = %f, BorneMax = %f, Pas = %f\n",borneMin,borneMax,pas);	
	
	for(i=borneMin; i<=borneMax+pas; i=i+pas){
			resultats[j] = (float*)malloc(2*sizeof(float));			
			resultats[j][0] = i;
			resultats[j][1] = prefixeArbre(tree, i);
			if ( resultats[j][1] == MAXFLOAT ) {
				printf("Erreur : Opérande manquant.\n");
				resultats = (float**)realloc(resultats,2*sizeof(float*));
				resultats[0][0] = MAXFLOAT;
				resultats[0][1] = MAXFLOAT;
				return resultats;
			}
			// printf("X = %f ; Valeur : %f\n",i,prefixeArbre(tree,i));
			j++;
	}
	return resultats;
}

void tempmain(){
	float borneMin = -5.0;
	float borneMax = 5.0;
	float pas = 0.5;
	float** tab = calculValeur(borneMin, borneMax, pas, "sin(x+2)");
	int i = (borneMax - borneMin) / pas;
	while(i--){
		printf("x=%f, y=%f\n",tab[i][0],tab[i][1]);
	}
}

