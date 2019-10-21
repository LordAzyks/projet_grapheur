#ifndef JETON_H_INCLUDED
#define JETON_H_INCLUDED

typedef enum
{
    REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FER,ABSOLU
}typelexem;

typedef enum
{
    PLUS,MOINS,FOIS,DIV,PUIS
}typeoperateur;

typedef enum{
    FONCTION_INCONNUE,CARACTERE_INCONNU
}typeerreur;

typedef enum
{
    ABS,SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG,SINC
}typefonction;

typedef union
{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
}typevaleur;

typedef struct
{
    typelexem lexem;
    typevaleur valeur;
}typejeton;

typedef struct Node
{
    typejeton jeton;
    struct Node *pjeton_preced;
    struct Node *pjeton_suiv;
}Node;

typedef Node* Arbre;

#endif // JETON_H_INCLUDED