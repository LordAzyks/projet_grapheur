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
    
    for (int i = 0; i < strlen(entree); i++)
    {
        //printf(" car : %c \n", entree[i] );
        buffer[0] = '\0';
        indexBuffer = 0;
        switch (entree[i])
        {
        case 'x':
            break;
        case '+':
            /* code */
            break;
        case '-':
            /* code */
            break;
        case '(':
            /* code */
            printf("  ( \n");
            break;
        case ')':
            /* code */
            printf("  ) \n");
            break;
        default:
            // Prise en compte des elements composés
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
                printf("nb %lf \n", atof(buffer));
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
                if((strcmp(buffer,"sin"))== 0){
                    printf("\n %s \n", buffer);
                    
                }else if((strcmp(buffer,"cos"))== 0){
                    
                }else if((strcmp(buffer,"tan"))== 0){
                    
                }
            }
            

            break;
        }
    }
}

void creation_jeton(typejeton *tableauJeton, typelexem lexem, typevaleur valeur, int indexJeton)
{
    typejeton jetonActu;
    jetonActu.lexem = lexem;
    jetonActu.valeur = valeur;
    tableauJeton[indexJeton] = jetonActu;
}