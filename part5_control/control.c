#include "control.h"

void menu(){ 
    char fonction[400];
    char tempo[20];
    char *token, *min, *max;
    int cpt;
    float var;
    printf("\n Entrez votre fonction : \n");
    fgets(fonction,strlen(fonction),stdin);
    while ((getchar()) != '\n'); // Clear Buffer
    do{
        printf("\n Entrez votre interval avec ce format < min;max >: \n ");
        fgets(tempo,strlen(tempo),stdin);
        cpt = 1;
        token = strtok(tempo,";");
        while( token != NULL ) {
            //printf( " %s\n", token );
            if (cpt==1){
                min = strcpy(min,token);
                cpt++;
            }else{
                max = strcpy(max,token);
            }
            token = strtok(NULL, ";");
        }
    } while ((!(var = atof(min))) && (!(var = atof(max))) && ((var = atof(min))>(var = atof(max))));
}