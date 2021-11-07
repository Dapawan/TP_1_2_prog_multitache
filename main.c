#include <stdio.h>
#include <stdlib.h>

enum matrice_type { BASE,
                    BASE_90_DEG,
                    BASE_180_DEG,
                    BASE_270_DEG,
                    TRANSPOSE,
                    TRANSPOSE_90_DEG,
                    TRANSPOSE_180_DEG,
                    TRANSPOSE_270_DEG };

char matrice_type_str[8][20] = {
    "BASE",
    "BASE_90_DEG",
    "BASE_180_DEG",
    "BASE_270_DEG",
    "TRANSPOSE",
    "TRANSPOSE_90_DEG",
    "TRANSPOSE_180_DEG",
    "TRANSPOSE_270_DEG"};

/***************** double **dmatrix() *******************/
//Alloue dynamiquement de la mémoire pour une matrice
double **dmatrix(long p, long q) {
    double **m = NULL;
    long i, t;

    t = q * sizeof(double);
    m = (double **)malloc(p * sizeof(double *));
    for (i = 0; i < p; i++)
        m[i] = (double *)malloc(t);
    return m;
}

double *matrice_vers_motif_1D(double **matrice_src, int nbr_ligne, int nbr_col) {
    double *tableau = (double *)malloc((nbr_ligne * nbr_col) * sizeof(double));

    tableau[0] = matrice_src[1][1];
    tableau[1] = matrice_src[0][1];
    tableau[2] = matrice_src[1][2];
    tableau[3] = matrice_src[2][1];
    tableau[4] = matrice_src[1][0];
    tableau[5] = matrice_src[0][0];
    tableau[6] = matrice_src[0][2];
    tableau[7] = matrice_src[2][2];
    tableau[8] = matrice_src[2][0];

    return tableau;
}

//Complète la matrice à l'aide d'un tableau 1D
void remplir_matrice(double **matrice, double *tableau_valeur, int nbr_ligne, int nbr_col) {
    for (int i = 0; i < nbr_col; i++) {
        for (int j = 0; j < nbr_ligne; j++) {
            matrice[i][j] = tableau_valeur[(i * nbr_col) + j];
        }
    }
}

//Effectue la transposée de la matrice source vers la matrice destination
void transpose_matrice(double **matrice_dst, double **matrice_src, int nbr_ligne, int nbr_col) {
    //Col => ligne
    for (int i = 0; i < nbr_col; i++) {
        for (int j = 0; j < nbr_ligne; j++)
            matrice_dst[j][i] = matrice_src[i][j];
    }
}

//Effectue une rotation de 90° de la matrice source vers la matrice destination
void remplir_90deg_matrice(double **matrice_dst, double **matrice_src, int nbr_ligne, int nbr_col) {
    for (int i = 0; i < nbr_col; i++) {
        for (int j = 0; j < nbr_ligne; j++)
            matrice_dst[j][nbr_col - (i + 1)] = matrice_src[i][j];
    }
}

//Affiche la matrice
void print_matrice(double **matrice, int nbr_ligne, int nbr_col) {
    printf("\n[\n");
    for (int i = 0; i < nbr_col; i++) {
        for (int j = 0; j < nbr_ligne; j++) {
            printf("%d ", (int)matrice[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

//Crée les 8 matrices
void create_matrices(double ***tableau_matrice_2d) {
    int nbr_col = 3;
    int nbr_ligne = 3;

    //Création dynamique des matrices
    for (int i = 0; i < 9; i++)
        tableau_matrice_2d[i] = dmatrix(nbr_ligne, nbr_col);
    /* Old way
    double **matrice_base = dmatrix(nbr_ligne, nbr_col);
    double **matrice_transpose = dmatrix(nbr_ligne, nbr_col);

    double **matrice_90_deg = dmatrix(nbr_ligne, nbr_col);
    double **matrice_180_deg = dmatrix(nbr_ligne, nbr_col);
    double **matrice_270_deg = dmatrix(nbr_ligne, nbr_col);

    double **matrice_transpose_90_deg = dmatrix(nbr_ligne, nbr_col);
    double **matrice_transpose_180_deg = dmatrix(nbr_ligne, nbr_col);
    double **matrice_transpose_270_deg = dmatrix(nbr_ligne, nbr_col);
    

    //Copie les adresses des matrices dans notre tableau de matrice
    tableau_matrice_2d[BASE] = matrice_base;
    tableau_matrice_2d[BASE_90_DEG] = matrice_90_deg;
    tableau_matrice_2d[BASE_180_DEG] = matrice_180_deg;
    tableau_matrice_2d[BASE_270_DEG] = matrice_270_deg;
    tableau_matrice_2d[TRANSPOSE] = matrice_transpose;
    tableau_matrice_2d[TRANSPOSE_90_DEG] = matrice_transpose_90_deg;
    tableau_matrice_2d[TRANSPOSE_180_DEG] = matrice_transpose_180_deg;
    tableau_matrice_2d[TRANSPOSE_270_DEG] = matrice_transpose_270_deg;
    */

    //Matrice de base en format ligne
    double matrice_base_[9] = {2, 2, 4, 1, 1, 3, 2, 1, 1};

    //Calcul des différentes matrices
    remplir_matrice(tableau_matrice_2d[BASE], matrice_base_, nbr_ligne, nbr_col);
    remplir_90deg_matrice(tableau_matrice_2d[BASE_90_DEG], tableau_matrice_2d[BASE], nbr_ligne, nbr_col);
    remplir_90deg_matrice(tableau_matrice_2d[BASE_180_DEG], tableau_matrice_2d[BASE_90_DEG], nbr_ligne, nbr_col);
    remplir_90deg_matrice(tableau_matrice_2d[BASE_270_DEG], tableau_matrice_2d[BASE_180_DEG], nbr_ligne, nbr_col);

    transpose_matrice(tableau_matrice_2d[TRANSPOSE], tableau_matrice_2d[BASE], nbr_ligne, nbr_col);
    remplir_90deg_matrice(tableau_matrice_2d[TRANSPOSE_90_DEG], tableau_matrice_2d[TRANSPOSE], nbr_ligne, nbr_col);
    remplir_90deg_matrice(tableau_matrice_2d[TRANSPOSE_180_DEG], tableau_matrice_2d[TRANSPOSE_90_DEG], nbr_ligne, nbr_col);
    remplir_90deg_matrice(tableau_matrice_2d[TRANSPOSE_270_DEG], tableau_matrice_2d[TRANSPOSE_180_DEG], nbr_ligne, nbr_col);
}

//Fait l'extraction d'une matrice en une matrice de plus petite taille
void extractionSousMatrice(double **matrice_src, double **matrice_dst, int indice_ligne_depart, int indice_col_depart, int nbr_ligne_sous_matrice, int nbr_col_sous_matrice) {
    for (int i = indice_col_depart; (i - indice_col_depart) < nbr_col_sous_matrice; i++) {
        for (int j = indice_ligne_depart; (j - indice_ligne_depart) < nbr_ligne_sous_matrice; j++) {
            matrice_dst[i - indice_col_depart][j - indice_ligne_depart] = matrice_src[i][j];
        }
    }
}

//Compare les 2 tableaux 1D retourne 1 si le contenu est identique sinon 0
int compareMotifs(double *motif_1, double *motif_2, int nbr_col, int nbr_ligne) {
    for (int i = 0; i < (nbr_col * nbr_ligne); i++) {
        if (motif_1[i] != motif_2[i])  // si une valeur est différente alors le motif est différent !
            return 0;
    }

    return 1;
}

int main(void) {
    int nbr_col = 3;
    int nbr_ligne = 3;

    double **tableau_matrice_2d[8];
    //Crée les 8 matrices
    create_matrices(tableau_matrice_2d);

    // int rot_90[9] = {2, 1, 2, 1, 1, 2, 1, 3, 4};
    // int rot_180[9] = {1, 1, 2, 3, 1, 1, 4, 2, 2};

    //On récupère la matrice 14*14 -> on itère en se déplacant pour extraire une 3*3 -> On get le motif et on le compare avec le notre
    double matrice_14_14_1D[] =
        {
            4, 1, 0, 3, 1, 0, 3, 2, 3, 4, 2, 2, 2, 2,
            0, 3, 1, 4, 4, 3, 1, 0, 2, 0, 3, 2, 3, 1,
            3, 3, 1, 4, 4, 4, 3, 0, 4, 1, 3, 3, 1, 0,
            1, 2, 2, 3, 3, 1, 2, 2, 1, 1, 1, 0, 1, 4,
            1, 0, 1, 4, 3, 0, 3, 3, 2, 0, 2, 1, 0, 0,
            2, 0, 3, 0, 0, 3, 2, 4, 0, 1, 2, 4, 2, 2,
            3, 0, 3, 4, 0, 1, 3, 3, 3, 3, 2, 1, 0, 2,
            4, 3, 0, 2, 0, 0, 4, 0, 4, 2, 3, 4, 4, 2,
            2, 3, 4, 1, 2, 1, 4, 3, 2, 1, 1, 4, 2, 0,
            1, 4, 0, 2, 2, 0, 4, 1, 1, 1, 3, 1, 2, 3,
            4, 1, 3, 0, 0, 0, 1, 4, 2, 2, 4, 1, 2, 2,
            0, 3, 0, 2, 4, 2, 4, 3, 4, 4, 1, 1, 4, 0,
            4, 2, 0, 4, 4, 3, 4, 0, 1, 0, 4, 1, 3, 4,
            3, 1, 4, 2, 3, 4, 2, 2, 3, 1, 4, 0, 2, 4};

    double **matrice_14_14 = dmatrix(14, 14);
    remplir_matrice(matrice_14_14, matrice_14_14_1D, 14, 14);

    //print_matrice(matrice_14_14, 14, 14);

    double **matrice_3_3 = dmatrix(3, 3);
    double *motif_matrice_3_3;

    //Récupère les 8 matrices en format 1D (avec la manière de récupérer le motif)
    double *tableau_motif_a_comparer[9];
    for (int i = 0; i < 8; i++) {
        tableau_motif_a_comparer[i] = matrice_vers_motif_1D(tableau_matrice_2d[i], 3, 3);
    }

    // for (int i = 0; i < 8; i++) {
    //     printf("Motif : ");
    //     for (int a = 0; a < 9; a++) {
    //         printf("%d", (int)tableau_motif_a_comparer[i][a]);
    //     }
    //     printf("\n");
    // }
    // for (int a = 0; a < 9; a++) {
    //     printf("%d", (int)test[a]);
    // }
    // printf("\n");

    //On extrait une matrice 3*3 de la matrice 14*14
    for (int i = 0; i <= 14 - 3; i += 1) {
        for (int j = 0; j <= 14 - 3; j += 1) {
            // matrice_vers_motif_1D(matrice_13_13[i][j], nbr_ligne, nbr_col);
            extractionSousMatrice(matrice_14_14, matrice_3_3, j, i, 3, 3);
            printf("Matrice 3*3 à col = %d et ligne = %d\n", i, j);
            print_matrice(matrice_3_3, 3, 3);

            motif_matrice_3_3 = matrice_vers_motif_1D(matrice_3_3, 3, 3);
            printf("Motif : ");
            for (int i = 0; i < 9; i++) {
                printf("%d", (int)motif_matrice_3_3[i]);
            }
            printf("\n");

            for (int x = 0; x < 8; x++) {
                if (compareMotifs(motif_matrice_3_3, tableau_motif_a_comparer[x], 3, 3) == 1) {
                    //Motifs identiques
                    printf("Le motif %s est equivalent\n", matrice_type_str[x]);
                    printf("Motif a comparer : ");
                    print_matrice(tableau_matrice_2d[x], 3, 3);
                    printf("Motif : ");
                    print_matrice(matrice_3_3, 3, 3);
                    return 0;
                }
            }
        }
    }

    /*
    Test de la conversion de matrice à motif 1D
    double test[9] = {1, 3, 1, 2, 2, 1, 2, 3, 3};

    double **matrice_test = dmatrix(nbr_ligne, nbr_col);
    remplir_matrice(matrice_test,test,nbr_ligne,nbr_col);

    double *result = matrice_vers_motif_1D(matrice_test,nbr_ligne,nbr_col);

    for(int i = 0; i < 9;i++)
    {
        printf("%d",(int)result[i]);
    }
    */
    /*
    printf("Matrice base\n");
    print_matrice(tableau_matrice_2d[BASE], nbr_ligne, nbr_col);

    printf("Matrice +90°\n");
    print_matrice(tableau_matrice_2d[BASE_90_DEG], nbr_ligne, nbr_col);

    printf("Matrice +180°\n");
    print_matrice(tableau_matrice_2d[BASE_180_DEG], nbr_ligne, nbr_col);

    printf("Matrice +270°\n");
    print_matrice(tableau_matrice_2d[BASE_270_DEG], nbr_ligne, nbr_col);

    printf("Transpose\n");
    print_matrice(tableau_matrice_2d[TRANSPOSE], nbr_ligne, nbr_col);

    printf("Matrice transpose +90°\n");
    print_matrice(tableau_matrice_2d[TRANSPOSE_90_DEG], nbr_ligne, nbr_col);

    printf("Matrice transpose +180°\n");
    print_matrice(tableau_matrice_2d[TRANSPOSE_180_DEG], nbr_ligne, nbr_col);

    printf("Matrice transpose +270°\n");
    print_matrice(tableau_matrice_2d[TRANSPOSE_270_DEG], nbr_ligne, nbr_col);
*/
    return 0;
}

// Stocker les différentes matrices (8) dans un fichier pour pouvoir l'utiliser par la suite
// On enleve les cotes (1ere ligne, 1ere colonne, derniere ligne, derniere colonne) --> ON passe en 12*12
// Partie 2 : autant de thread que de matrices (8)
// Partie 3 : On découpe la matrice 12*12 en sous matrices avec des tasks qui recherchent les 8 matrices
// Derniere partie : Indiquer les coordonnées du pixel central

// Fournir le prog source à la séance prochaine
// Indiquer la commande pour compiler le prog !
// Indiquer le nom du binôme dans le code