#include "lexic.h"

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

typejeton *decoupe_saisie(char *entree, int *taille_jeton)
{
    format_text(entree);

    char buffer[10];
    int tailleTab = 0, indexBuffer = 0;
    float valeur = 0;
    typelexem lexem = -1;
    typeoperateur operator= - 1;
    typefonction function = -1;
    typejeton *tableau = NULL;
    typevaleur *val;

    for (int i = 0; i < strlen(entree); i++)
    {
        val = malloc(sizeof(typevaleur));
        //printf(" car : %c \n", entree[i] );
        buffer[0] = '\0';
        indexBuffer = 0;
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
            // Prise en compte des éléments composés
            buffer[1] = '\0';
            if (entree[i] <= '9' && entree[i] >= '0')
            {
                while ((entree[i] <= '9' && entree[i] >= '0') || (entree[i] == '.'))
                {
                    buffer[indexBuffer] = entree[i];
                    i++;
                    indexBuffer++;
                }
                i--;
                buffer[indexBuffer] = '\0';
                lexem = REEL;
                val->reel = atof(buffer);
            }
            else if (entree[i] >= 'a' && entree[i] <= 'z')
            {

                while (entree[i] >= 'a' && entree[i] <= 'z')
                {
                    buffer[indexBuffer] = entree[i];
                    i++;
                    indexBuffer++;
                }
                i--;
                buffer[indexBuffer] = '\0';
                lexem = FONCTION;

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
                    // erreur fonction inconnu
                    lexem = ERREUR;
                    val->erreur = FONCTION_INCONNUE;
                }
            }
            else
            {
                // erreur caractere inconnu
                lexem = ERREUR;
                val->erreur = CARACTERE_INCONNU;
            }

            break;
        }


        tableau = creation_jeton(&tableau, lexem, val, &tailleTab);

        /*
        printf("\n TEST affichage typevaleur") ;
        printf("\n Valeur : %lf", val.reel);
        printf("\n Fonction : %d", val.fonction);
        printf("\n Operateur : %d \n", val.operateur);      
         */
        lexem = -1;
    }
    lexem = FIN;
    val = malloc(sizeof(typevaleur));
    val->reel = 0;

    tableau = creation_jeton(&tableau, lexem, val, &tailleTab);
    *taille_jeton = tailleTab;

    return tableau;
}

typejeton *creation_jeton(typejeton **tableauJeton, typelexem lexem, typevaleur *valeur, int *taille)
{
    if (*taille == 0)
    {
        *tableauJeton = (typejeton *)malloc(sizeof(typejeton));
    }
    else
    {
        *tableauJeton = (typejeton *)realloc(*tableauJeton, sizeof(typejeton) * ((*taille) + 1));
    }

    typejeton jetonActu;
    jetonActu.lexem = lexem;
    jetonActu.valeur = *valeur;
    (*tableauJeton)[*taille] = jetonActu;

    (*taille) += 1;

    return *tableauJeton;
}