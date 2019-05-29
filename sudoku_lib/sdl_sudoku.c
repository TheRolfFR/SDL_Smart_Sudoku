//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>

char *convertInt(int b) {
    //Fonction permettant de convertir un nombre en chaine de caractère

    char *a;
    int Count = 1, Temp = b;

    while (Temp > 0) //Boucle permettant d'obtenir le nombre de numéro du nombre demandé
    {
        Temp /= 10;
        Count++;
    }

    a = (char *)malloc(Count+1); //Allocation d'un espace mémoire suffisant pour la chaine de caractère

    sprintf(a, "%d", b); //Conversion de l'entier en chaine de caractère

    return a;
}