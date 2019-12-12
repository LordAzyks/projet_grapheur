#include "lexic.h"


//Formatage du texte (Sans espace + minuscule)
void format_text(char *func)
{
    char *origine = (char *)malloc(sizeof(char) * (strlen(func) + 1));
    strcpy(origine, func);
    int count = 0;

    for (int i = 0; origine[i]; i++)
    {
        origine[i] = tolower(origine[i]);
        if (origine[i] != ' ')
            origine[count++] = origine[i];
    }
    origine[count] = '\0';
}

//Decoupe de la saisie pour creation de jeton
typejeton *decoupe_saisie(char *entree, int *taille_jeton)
{
    //Formatage du texte
    format_text(entree);

    char buffer[10];
    int tailleTab = 0, indexBuffer = 0;
    float valeur = 0;
    typelexem lexem = -1;
    typeoperateur operator= - 1;
    typefonction function = -1;
    typejeton *tableau = NULL;
    typevaleur *val;

    //Parcours de la chaine
    for (int i = 0; i < strlen(entree); i++)
    {
        val = malloc(sizeof(typevaleur));
        //printf(" car : %c \n", entree[i] );
        buffer[0] = '\0';
        indexBuffer = 0;
        //Si le caractere correspond a un operateur, variable ou parenthese
        switch (entree[i])
        {
        case 'x':
            lexem = VARIABLE;
            break;
        case '+':
            lexem = OPERATEUR;
            val->operateur = PLUS;
            break;
        case '-':
            lexem = OPERATEUR;
            val->operateur = MOINS;
            break;
        case '*':
            lexem = OPERATEUR;
            val->operateur = FOIS;
            break;
        case '/':
            lexem = OPERATEUR;
            val->operateur = DIV;
            break;
        case '^':
            lexem = OPERATEUR;
            val->operateur = PUIS;
            break;
        case '(':
            lexem = PAR_OUV;
            break;
        case ')':
            lexem = PAR_FERM;
            break;
        default:
            // Sinon prise en compte des éléments composés
            buffer[1] = '\0';
            //Si c'est un nombre
            if (entree[i] <= '9' && entree[i] >= '0')
            {
                while ((entree[i] <= '9' && entree[i] >= '0') || (entree[i] == '.'))
                {
                    //Stockage dans un buffer
                    buffer[indexBuffer] = entree[i];
                    i++;
                    indexBuffer++;
                }
                i--;
                buffer[indexBuffer] = '\0';
                lexem = REEL;
                val->reel = atof(buffer);
            }
            //Sinon c'est une fonction
            else if (entree[i] >= 'a' && entree[i] <= 'z')
            {
                //PArcours tant que caractere ou parenthese ou variable ou nombre
                while (entree[i] >= 'a' && entree[i] <= 'z' && entree[i] != '(' && entree[i+1] != 'x' && !(entree[i] <= '9' && entree[i] >= '0') || (entree[i] == '.'))
                {
                    //Stockage dans un buffer
                    buffer[indexBuffer] = entree[i];
                    i++;
                    indexBuffer++;
                }
                i--;
                buffer[indexBuffer] = '\0';
                lexem = FONCTION;
                //Comparaison du buffer aux fonctions connues
                if ((strcmp(buffer, "abs")) == 0)
                {
                    val->fonction = ABS;
                }
                else if ((strcmp(buffer, "sin")) == 0)
                {
                    val->fonction = SIN;
                }
                else if ((strcmp(buffer, "cos")) == 0)
                {
                    val->fonction = COS;
                }
                else if ((strcmp(buffer, "tan")) == 0)
                {
                    val->fonction = TAN;
                }
                else if ((strcmp(buffer, "exp")) == 0)
                {
                    val->fonction = EXP;
                }
                else if ((strcmp(buffer, "sqrt")) == 0)
                {
                    val->fonction = SQRT;
                }
                else if ((strcmp(buffer, "log")) == 0)
                {
                    val->fonction = LOG;
                }
                else
                {
                    //Erreur fonction inconnu
                    lexem = ERREUR;
                    val->erreur = FONCTION_INCONNUE;
                }
            }
            else
            {
                //Erreur caractere inconnu
                lexem = ERREUR;
                val->erreur = CARACTERE_INCONNU;
            }

            break;
        }

        //Ajout du jeton au tableau
        tableau = creation_jeton(&tableau, lexem, val, &tailleTab);

        
        lexem = -1;
    }
    //Ajout du jeton de fin
    lexem = FIN;
    val = malloc(sizeof(typevaleur));
    val->reel = 0;

    tableau = creation_jeton(&tableau, lexem, val, &tailleTab);

    //Taille du tableau
    *taille_jeton = tailleTab;

    return tableau;
}

//Creation des jetons et ajouts dans le tableau de jetons
typejeton *creation_jeton(typejeton **tableauJeton, typelexem lexem, typevaleur *valeur, int *taille)
{
    if (*taille == 0)
    {
        //Si le tableau est vide
        *tableauJeton = (typejeton *)malloc(sizeof(typejeton));
    }
    else
    {
        //Si il existe deja qque chose
        *tableauJeton = (typejeton *)realloc(*tableauJeton, sizeof(typejeton) * ((*taille) + 1));
    }

    typejeton jetonActu;
    jetonActu.lexem = lexem;
    jetonActu.valeur = *valeur;
    (*tableauJeton)[*taille] = jetonActu;

    (*taille) += 1;

    return *tableauJeton;
}