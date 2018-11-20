/*
	Crible d'Eratosthene
	Pierre Delisle
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MIN(a, b)  ((a)<(b)?(a):(b))

int main(int argc, char* argv[]) {
	int n;                /* Dernier nombre premier a verifier (2..n)*/
	int taille;            /* Taille du tableau de nombres premiers a verifier */
	int* marques;        /* Tableau permettant de marquer les nombres verifies */
	int indexMarques;    /* Index du nb premier courant dans le tableau "marques" */
	int k;/* Nombre premier courant */
	int compte;            /* Compteur de nombres premiers */
	int indMin;        /* Indicateur de debut de marquage*/
	int i;
	int p, rank;
	int valMin, valMax;

	MPI_Init(&argc, &argv);
	if (argc != 2) {  /* Verifie que un seul argument a ete fourni */
		printf("Usage : %s n\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	n = atoi(argv[1]);

	valMin = (rank * (n - 1) / p) + 2, valMax = ((rank + 1) + ((n - 1) / p) + 2) - 1;

	taille = valMax - valMin + 1;

	marques = (int*) malloc(sizeof(int) * taille);
//#pragma omp parallel for //Pourrait être marrant.
	for (i = 0; i < taille; i++)
		marques[i] = 0;

	indexMarques = 0;
	k = 2;
	do {
		indMin = rank * (n - 1) / p;    /* Indice du 1er nombre a marquer (k2)*/
		for (i = indMin; i < taille; i += k) /* Pour tous les multiples du nb premier, */
			marques[i] = 1;                                            /* on marque le nombre*/

		while (marques[++indexMarques]);        /* On trouve l'indice de la prochaine case non marquee */
		k = indexMarques + 2;  /* ce qui donne le nb premier du prochain tour */

	} while (k * k <= n);  /* On arrete si son carre est > que n*/

	compte = 0;
	for (i = 0; i < taille; i++)
		if (!marques[i])
			compte++;

	printf("Il y a %d nombres premiers plus petits ou egaux a %d\n", compte, n);
	printf("Ces nombres sont : ");
	for (i = 0; i < taille; i++)
		if (!marques[i])
			printf("%d ", i + 2);
	printf("\n");

	free(marques);
	MPI_Finalize();
	return EXIT_SUCCESS;
}
