#include "lexic.h"

void format_text(char *origine)
{
    int count = 0;

    for (int i = 0; origine[i]; i++)
    {
        origine[i] = tolower(origine[i]);
        if (origine[i] != ' ')
            origine[count++] = origine[i];
    }
    origine[count] = '\0';
}

void decoupe_saisie(char *entree)
{
    char buffer[10];
    int tailleTab = 0, indexBuffer = 0;
    float valeur;
    typelexem lexem;
    typeoperateur operator;
    typefonction function;
    typejeton *tableau = NULL;

    for (int i = 0; i < strlen(entree); i++)
    {
        valeur = 0;
        lexem = -1;
        operator= - 1;
        function = -1;

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
            operator= PLUS;
            break;
        case '-':
            lexem = OPERATEUR;
            operator= MOINS;
            break;
        case '*':
            lexem = OPERATEUR;
            operator= FOIS;
            break;
        case '/':
            lexem = OPERATEUR;
            operator= DIV;
            break;
        case '^':
            lexem = OPERATEUR;
            operator= PUIS;
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
                valeur = atof(buffer);
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
                    function = ABS;
                }
                else if ((strcmp(buffer, "sin")) == 0)
                {
                    function = SIN;
                    //printf("\n SIN = %d", function);
                }
                else if ((strcmp(buffer, "cos")) == 0)
                {
                    function = COS;
                }
                else if ((strcmp(buffer, "tan")) == 0)
                {
                    function = TAN;
                }
                else if ((strcmp(buffer, "exp")) == 0)
                {
                    function = EXP;
                }
                else if ((strcmp(buffer, "sqrt")) == 0)
                {
                    function = SQRT;
                }
                else if ((strcmp(buffer, "log")) == 0)
                {
                    function = LOG;
                }
            }

            break;
        }
        typevaleur val;
        printf("\n-----------------");
        printf("\n Valeur = %lf", valeur);
        val.reel = valeur;
        printf("\n Fonction = %d", function);
        val.fonction = function;
        printf("\n OPerateur = %d", operator);
        val.operateur = operator;

        tableau = creation_jeton(&tableau,lexem,val,&tailleTab);

        /*
        printf("\n TEST affichage typevaleur") ;
        printf("\n Valeur : %lf", val.reel);
        printf("\n Fonction : %d", val.fonction);
        printf("\n Operateur : %d \n", val.operateur);      
         */
    }

    // Mettre ici la fonction d'appel a l'analyse syntaxique
}

typejeton* creation_jeton(typejeton **tableauJeton, typelexem lexem, typevaleur valeur, int *taille)
{
    if (*taille == 0)
    {
        *tableauJeton = (typejeton *)malloc(sizeof(typejeton));
        printf("malloc\n");
    }
    else
    {
        *tableauJeton = (typejeton *)realloc(*tableauJeton, sizeof(typejeton) * ((*taille) + 1));
        printf("realloc\n");
    }

    typejeton jetonActu;
    jetonActu.lexem = lexem;
    jetonActu.valeur = valeur;
    (*tableauJeton)[*taille] = jetonActu;

    (*taille) += 1;

    return *tableauJeton;
}