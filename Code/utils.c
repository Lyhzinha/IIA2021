#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

void init_rand() { srand((unsigned)time(NULL)); }

int random_l_h(int min, int max) { return min + rand() % (max - min + 1); }

float rand_01() { return ((float)rand()) / RAND_MAX; }

int** init_dados(char* nome, int* elementos, int* subconjuntos) {
	FILE* f;
	int linhasLidas = 0;
	char linha[MAXCHARSIZE];
	int** matriz = NULL;
	int pontoA, pontoB, distancia;

	f = fopen(nome, "rt");
	if (!f) {
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
	while (fgets(linha, MAXCHARSIZE - 1, f)) {

		if (linhasLidas == 0) {
			sscanf(linha, "%d %d", elementos, subconjuntos);

			matriz = malloc((*elementos) * (sizeof(int*)));
			if (matriz == NULL) {
				printf("Erro na alocação de memória");
				return NULL;
			}

			for (int i = 0; i < *elementos; i++) {
				matriz[i] = (int*)malloc((*elementos) * (sizeof(int)));
			}

			linhasLidas = 1;

		}
		else {

			sscanf(linha, "%d %d %d", &pontoA, &pontoB, &distancia);
			matriz[pontoA][pontoB] = distancia;
			matriz[pontoB][pontoA] = distancia;
		}
	}
	fclose(f);
	return matriz;
}

void substitui(int a[], int b[], int n) {
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}
}


int flip() {
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}
void gera_solucao_inicial(int* solucao, int elementos, int subconjuntos) {

	int numElementosSubconjuntos = elementos / subconjuntos;
	int controloSubconjuntos[MAX_ELEMENTS];
	int aux;
	for (int i = 0; i < elementos; i++) {
		solucao[i] = 0;
	}

	for (int i = 0; i < subconjuntos; i++) {
		controloSubconjuntos[i] = 0;
	}

	for (int i = 0; i < elementos; i++) {

		do {
			aux = rand() % subconjuntos;

		} while (controloSubconjuntos[aux] >= numElementosSubconjuntos);

		solucao[i] = aux;
		controloSubconjuntos[aux]++;
	}
}

pchrom init_pop(int elementos, int subconjuntos) {
	int     i, j;
	pchrom  indiv;

	indiv = malloc(sizeof(chrom)*POPSIZE);
	if (indiv==NULL) {
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	for (i=0; i<POPSIZE; i++) {
		gera_solucao_inicial(indiv[i].solucao, elementos, subconjuntos);
	}
	return indiv;
}

chrom get_best(pchrom pop, chrom best) {
	int i;

	for (i=0; i<POPSIZE; i++) {
		if (best.fitness < pop[i].fitness)
			best=pop[i];
	}
	return best;
}

void write_best(chrom x, int elementos) {
	int i;

	printf("\nBest individual: %4.1f\n", x.fitness);
	for (i=0; i<elementos; i++)
		printf("%d", x.solucao[i]);
	putchar('\n');
}
