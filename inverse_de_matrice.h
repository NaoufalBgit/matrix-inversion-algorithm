#ifndef inverse_de_matrice_h
#define inverse_de_matrice_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float **lireMatrice(const char  *nomFichier, int *N);
void multiplier(float **matrice1, float **matrice2, int N);
bool zero(float **tab, int taille);
float **tableau(int taille);
void somme(float **matrice, float **matrice1, float **matrice2, int N);
void copie(float **matrice1, float **matrice2, int N);
void soustraction(float **matrice, float **matrice1, float **matrice2, int N);
void moins(float **matrice, int N);
float ***Decomposeur(float **matrice, int N);
void trnaspose(float **matrice1, int N);
int inverse(float **tab, int N);

#endif // inverse_de_matrice_h
