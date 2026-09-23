#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inverse_de_matrice.h"

float **lireMatrice(const char  *nomFichier, int *N) { // fonction qui lit la taille de la matrice A et les éléments de la matrice A
    FILE *file = fopen(nomFichier, "r");
    if (file == NULL) {
        printf("Echec de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", N);
    float **matrice = (float **)malloc(*N * sizeof(float *));
    for (int i = 0; i < *N; i++) {
        matrice[i] = (float *)malloc(*N * sizeof(float));
        for (int j = 0; j < *N; j++) {
            fscanf(file, "%f", &matrice[i][j]);
        }
    }
	
    fclose(file);
    return matrice;
}

void multiplier(float **matrice1, float **matrice2, int N) // focntion qui fait la multiplication standard de deux matrices 
{
  float resultat[N][N];
  int i, j, k;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      resultat[i][j] = 0;
      for (k = 0; k < N; k++)
      {
        resultat[i][j] += matrice1[i][k] * matrice2[k][j];
      }
    }
  }
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      matrice1[i][j] = resultat[i][j];
    }
  }
}

bool zero(float **tab, int taille) // fonction qui renvoie si une matrice est nulle 
{
  int i, j;
  for (i = 0; i < taille; i++)
  {
    for (j = 0; j < taille; j++)
    {
      if (tab[i][j] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

float **tableau(int taille) // fonction qui crée un tableau de matrice
{
  float **tab = (float **)malloc(taille * sizeof(float *));
  if (tab == NULL)
  {
    printf("Echec de l'allocation");
    return NULL; 
  }

  for (int i = 0; i < taille; i++)
  {
    tab[i] = (float *)malloc(taille * sizeof(float));
    if (tab[i] == NULL)
    {
      printf("Echec de l'allocaiton");
      
      for (int j = 0; j < i; j++)
      {
        free(tab[j]);
      }
      free(tab);
      return NULL; 
    }
  }
  return tab;
}

void somme(float **matrice, float **matrice1, float **matrice2, int N) // fonction qui fait la somme de deux matrices 
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      matrice[i][j] = matrice1[i][j] + matrice[i][j];
    }
  }
}

void copie(float **matrice1, float **matrice2, int N) // fonction qui copie les éléments d'une matrice dans une autre 
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      matrice1[i][j] = matrice2[i][j];
    }
  }
}

void soustraction(float **matrice, float **matrice1, float **matrice2, int N) // fonction qui fait la soustraction de deux matrices 
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      matrice[i][j] = matrice1[i][j] - matrice2[i][j];
    }
  }
}

void moins(float **matrice, int N) // fonction qui innverse les éléments (et non la matrice) d'une matrice 
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      matrice[i][j] = -matrice[i][j];
    }
  }
}

float ***Decomposeur(float **matrice, int N) // fonction qui decompose la matrice A en quatre sous matrices 
{
  float ***tableau_de_matrice = (float ***)malloc(4 * sizeof(float **));
  if (tableau_de_matrice == NULL)
  {
    printf("Echec, le tableau de matrice n'a pas été crée");
  }
  int i, j, k;
  for (k = 0; k < 4; k++)
  {
    tableau_de_matrice[k] = (float **)malloc(N / 2 * sizeof(float *));
    for (i = 0; i < N / 2; i++)
    {
      tableau_de_matrice[k][i] = (float *)malloc(N / 2 * sizeof(float));
    }
  }
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      if (i < N / 2 && j < N / 2)
      {
        tableau_de_matrice[0][i][j] = matrice[i][j];
      }
      else if (i < N / 2 && j >= N / 2)
      {
        tableau_de_matrice[1][i][j - N / 2] = matrice[i][j];
      }
      else if (i >= N / 2 && j < N / 2)
      {
        tableau_de_matrice[2][i - N / 2][j] = matrice[i][j];
      }
      else
      {
        tableau_de_matrice[3][i - N / 2][j - N / 2] = matrice[i][j];
      }
    }
  }

  return tableau_de_matrice;
}

void trnaspose(float **matrice1, int N) // fonction qui fait la transposee d'une matrice 
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      float temp = matrice1[i][j];
      matrice1[i][j] = matrice1[j][i];
      matrice1[j][i] = temp;
    }
  }
}

int inverse(float **tab, int N) // fonction qui inverse une matrice 
{
  if (N == 1 && tab[0][0 != 0])
  {
    tab[0][0] = 1 / tab[0][0];
  }
  else
  {
    float ***bloc = Decomposeur(tab, N);
    if (zero(bloc[0], N / 2))
    {
      printf("la matrice B est nulle donc S est nulle donc A est non inversible \n");
      return 0;
    }
    float **S = tableau(N / 2);

    float **B_1 = tableau(N / 2);
    copie(B_1, bloc[0], N / 2);
    inverse(B_1, N / 2);
    copie(S, bloc[2], N / 2);
    multiplier(S, B_1, N / 2);
    multiplier(S, bloc[1], N / 2);
    soustraction(S, bloc[3], S, N / 2);
    if (zero(S, N / 2))
    {
      printf("la matrice S est nulle donc A est non inversible \n");
      return 0;
    } // matrice S est prète
    
    float **S_1 = tableau(N / 2);
    copie(S_1, S, N / 2);
    inverse(S_1, N / 2);

    // maintenant on décris les quatres composants de (ATA)⁻¹ qui sont des tableaux 
    float **bloc0 = tableau(N / 2);
    float **bloc1 = tableau(N / 2);
    float **bloc2 = tableau(N / 2);
    float **bloc3 = tableau(N / 2);
    copie(bloc0, B_1, N / 2);
    multiplier(bloc0, bloc[1], N / 2);
    multiplier(bloc0, S_1, N / 2);
    multiplier(bloc0, bloc[2], N / 2);
    multiplier(bloc0, B_1, N / 2);
    somme(bloc0, B_1, bloc0, N / 2);
    copie(bloc1, B_1, N / 2);
    multiplier(bloc1, bloc[1], N / 2);
    multiplier(bloc1, S_1, N / 2);
    moins(bloc1, N / 2);
    copie(bloc2, S_1, N / 2);
    multiplier(bloc2, bloc[2], N / 2);
    multiplier(bloc2, B_1, N / 2);
    moins(bloc2, N / 2);
    copie(bloc3, S_1, N / 2);
    for (int k = 0; k < N / 2; k++)
    {
      free(bloc[0][k]);
      free(bloc[1][k]);
      free(bloc[2][k]);
      free(bloc[3][k]);
    }
    free(bloc[0]);
    free(bloc[1]);
    free(bloc[2]);
    free(bloc[3]);
    free(bloc);
    int i, j;
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < N; j++)
      {
        if (i < N / 2 && j < N / 2)
        {
          tab[i][j] = bloc0[i][j];
        }
        else if (i < N / 2 && j >= N / 2)
        {
          tab[i][j] = bloc1[i][j - (N / 2)];
        }
        else if (i >= N / 2 && j < N / 2)
        {
          tab[i][j] = bloc2[i - N / 2][j];
        }
        else
        {
          tab[i][j] = bloc3[i - N / 2][j - N / 2];
        }
      }
    }
    for (int j = 0; j < N / 2; j++)
    {
      free(bloc0[j]);
      free(bloc1[j]);
      free(bloc2[j]);
      free(bloc3[j]);
      free(S[j]);
      free(B_1[j]);
      free(S_1[j]);
    }
    free(bloc0);
    free(bloc1);
    free(bloc2);
    free(bloc3);
    free(S);
    free(B_1);
    free(S_1);
  }
  return 1;
}


int main()
{

  float **A = NULL;
  int M;
  printf("Voici la matrice A :\n\n");
  A=lireMatrice("matrice.txt", &M);
  
  int i, j;
  
  for (i = 0; i < M; i++)
  {
    for (j = 0; j < M; j++)
    {
    
      printf("%.0f  ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  float **AT = tableau(M);
  copie(AT, A, M);
  trnaspose(AT, M); // ici on a AT

  float **ATA = tableau(M);
  copie(ATA, AT, M);
  multiplier(ATA, A, M); // voila ATA

  float **ATA_1 = tableau(M);
  copie(ATA_1, ATA, M);
  if (inverse(ATA_1, M) == 0)
  {
    return 0;
  } // voila (ATA)⁻¹
  
  float **A_1 = tableau(M);
  copie(A_1, ATA_1, M);
  multiplier(A_1, AT, M); // voila A⁻¹

  printf("Voici la matrice A⁻¹ :\n\n");
  for (i = 0; i < M; i++)
  {
    for (j = 0; j < M; j++)
    {
      printf("%.2f  ", A_1[i][j]);
    }
    printf("\n");
  }
  for (int k = 0; k < M; k++)
  {
    free(A[k]);
    free(AT[k]);
    free(ATA[k]);
    free(ATA_1[k]);
    free(A_1[k]);
  }
  free(A);
  free(AT);
  free(ATA);
  free(ATA_1);
  free(A_1);
}
