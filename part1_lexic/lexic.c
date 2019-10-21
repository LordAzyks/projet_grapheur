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
    int indexBuffer = 0;
    float valeur ;
    
    for (int i = 0; i < strlen(entree); i++)
    {
        typelexem lexem ;
        typeoperateur operator ;
        typefonction function ;
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
            operator = PLUS;
            break;
        case '-':
            lexem = OPERATEUR;
            operator = MOINS;
            break;
        case '*':
            lexem = OPERATEUR;
            operator = FOIS;
            break;
        case '/':
            lexem = OPERATEUR;
            operator = DIV;
            break;
        case '^':
            lexem = OPERATEUR;
            operator = PUIS;
            break;
        case '(':
            lexem = PAR_OUV;
            //printf("  ( \n");
            break;
        case ')':
            lexem = PAR_FERM;
            //printf("  ) \n");
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
                printf("nb %lf \n", valeur);
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


                if((strcmp(buffer,"abs"))== 0){
                    printf("\n %s \n", buffer);
                    function = ABS;
                }else if((strcmp(buffer,"sin"))== 0){
                    function = SIN;
                    //printf("\n SIN = %d", function);
                }else if((strcmp(buffer,"cos"))== 0){
                    function = COS;
                }else if((strcmp(buffer,"tan"))== 0){
                    function = TAN;
                }else if((strcmp(buffer,"exp"))== 0){
                    function = EXP;
                }else if((strcmp(buffer,"sqrt"))== 0){
                    function = SQRT;
                }else if((strcmp(buffer,"log"))== 0){
                    function = LOG;
                }
            }
            
            break;
        }
        typevaleur val ;
        printf("\n Valeur = %lf", valeur);
        val.reel = valeur;
        printf("\n Fonction = %d", function);
        val.fonction = function;
        printf("\n OPerateur = %d", operator);
        val.operateur = operator;

        /*
          printf("\n TEST affichage typevaleur") ;
        printf("\n Valeur : %lf", val.reel);
        printf("\n Fonction : %d", val.fonction);
        printf("\n Operateur : %d \n", val.operateur);      
         */
    }
}

void creation_jeton(typejeton *tableauJeton, typelexem lexem, typevaleur valeur, int indexJeton)
{
    typejeton jetonActu;
    jetonActu.lexem = lexem;
    jetonActu.valeur = valeur;
    tableauJeton[indexJeton] = jetonActu;
}