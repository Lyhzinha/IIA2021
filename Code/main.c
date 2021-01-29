#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	
	pchrom      pop = NULL, parents = NULL;
	chrom       best_run, best_ever;
	int         gen_actual, r, runs, i, inv;
	float       mbf = 0.0;

	char nome_ficheiro[100];
	int elementos, subconjuntos, k, iterations, qualidade, best_qualidade;
	int* solucao, * best;
	int** matriz;

	if (argc == 4) {
		runs = atoi(argv[2]);
		iterations = atoi(argv[3]);
		strcpy(nome_ficheiro, argv[1]);
	}
	else if (argc == 2) {
		runs = DEFAULT_RUNS;
		iterations = DEFAULT_ITERATIONS;
		strcpy(nome_ficheiro, argv[1]);
	}
	else {
		runs = DEFAULT_RUNS;
		iterations = DEFAULT_ITERATIONS;
		printf("Nome do Ficheiro: ");
		gets(nome_ficheiro);
	}


	if (runs <= 0 || iterations <= 0) return 0;

	init_rand();
    
	matriz = init_dados(nome_ficheiro, &elementos, &subconjuntos);

	for (r=0; r<runs; r++) {
		printf("Repeticao %d\n",r+1);
        
		pop = init_pop(elementos, subconjuntos);
       
		evaluate(pop, matriz, elementos, subconjuntos);
        
		//trepa_colinas(pop, matriz, elementos, subconjuntos);
		best_run = pop[0];
		best_run = get_best(pop, best_run);
		
		parents = malloc(sizeof(chrom)*POPSIZE);
		if (parents==NULL) {
			printf("Erro na alocacao de memoria\n");
			exit(1);
		}
		
		gen_actual = 1;
		while (gen_actual <= MAX_GEN) {
			tournament_geral(pop, parents);
           
			genetic_operators(parents, pop, elementos);
            
			evaluate(pop, matriz, elementos, subconjuntos);
           
		//	trepa_colinas(pop, matriz, elementos, subconjuntos);
			
			best_run = get_best(pop, best_run);
			gen_actual++;
		}
        
        trepa_colinas(pop, matriz, elementos, subconjuntos);	
		
		mbf += best_run.fitness;
		if (r==0 || best_run.fitness > best_ever.fitness)
			best_ever = best_run;
   
		free(parents);
		free(pop);
	}

	printf("\n\nMBF: %f\n", mbf/r);
	printf("\nMelhor solucao encontrada");
	write_best(best_ever, elementos);
	return 0;
}
