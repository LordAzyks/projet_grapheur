#include "evalua.h"



float preffixeArbre(Arbre arb, float var){
	
	//valeur	
	if(arb->pjeton_preced == NULL){
		if(arb->jeton.lexem == REEL) {
			return arb->jeton.valeur.reel;
		} else {
			return var;
		}
	} else {
		
		//fonction		
		if(arb->pjeton_suiv == NULL){
			switch(arb->jeton.valeur.fonction){
				case ABS:
					return fabs(preffixeArbre(arb->pjeton_preced,var));
					break;
				case SIN:
					return sin(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case SQRT:
					return sqrt(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case LOG:
					return log(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case COS:
					return cos(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case TAN:
					return tan(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case EXP:
					return exp(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case ENTIER:
					return floor(preffixeArbre(arb->pjeton_preced,var));
					break;	
				case VAL_NEG:
					return preffixeArbre(arb->pjeton_preced,var)*(-1);
					break;	
				case SINC:
					return sin(preffixeArbre(arb->pjeton_preced,var))/preffixeArbre(arb->pjeton_preced,var);
					break;	
				default:
					return 0;
					break;			
			}
			
		//operateur		
		} else {
			switch(arb->jeton.valeur.operateur) {
				case PLUS:
					return preffixeArbre(arb->pjeton_preced,var)+preffixeArbre(arb->pjeton_suiv,var);
					break;
				case MOINS:
					return preffixeArbre(arb->pjeton_preced,var)-preffixeArbre(arb->pjeton_suiv,var);
					break;
				case FOIS:
					return preffixeArbre(arb->pjeton_preced,var)*preffixeArbre(arb->pjeton_suiv,var);
					break;
				case DIV:
					return preffixeArbre(arb->pjeton_preced,var)/preffixeArbre(arb->pjeton_suiv,var);
					break;
				case PUIS:
					return pow(preffixeArbre(arb->pjeton_preced,var),preffixeArbre(arb->pjeton_suiv,var));
					break;
				default:
					return 0;
					break;
			}	
		}
	}
	
}

float** calculValeur(float borneMin, float borneMax, float pas, Arbre tri){
	int j =0;
	float i;
	int nbValues;
	nbValues = (borneMax-borneMin)/pas;
	//float resultat[nbValues][2];
	float** resultats;
	resultats = (float**)malloc(nbValues*sizeof(float*));
	
	for(i=borneMin; i <= borneMax; i=i+pas){
			resultats[j] = (float*)malloc(2*sizeof(float));			
			resultats[j][0] = i;
			resultats[j][1] = preffixeArbre(tri, i);
			j++;
	}
	return resultats;
}