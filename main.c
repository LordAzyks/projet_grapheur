#include "header.h"
#include "part3_evelua/evalua.h"

// CECI EST UN MAIN DE TEST UNIQUEMENT
int main(int argc, char const *argv[]) {
    printf("CECI EST UN MAIN DE TEST UNIQUEMENT\n");
    float borneMin = -5.0;
    float borneMax = 5.0;
    float pas = 1.0;
    float** tab = calculValeur(-5.0, 5.0, 1.0, argv[1]);
    int i = (borneMax - borneMin) / pas;
    while(i--){
        printf("x=%f, y=%f\n",tab[i][0],tab[i][1]);
    }

    return 0;
}
