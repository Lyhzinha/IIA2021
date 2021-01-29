#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

void tournament_geral(pchrom pop, pchrom parents) {
	int i, j, k, sair, best, *pos;

	pos = malloc(TSIZE*sizeof(int));
	
	for(i=0; i<POPSIZE;i++) {
	   
		for(j=0; j<TSIZE; j++) {
            do {
                pos[j] = random_l_h(0, POPSIZE-1);
                sair = 0;
                for (k=0; k<j; k++) {
                    if (pos[k]==pos[j])
                        sair = 1;
                }
            } while (sair);
           
            if (j==0 || pop[pos[j]].fitness > pop[pos[best]].fitness)		
                best = j;
        }
        parents[i] = pop[pos[best]];
	}

	free(pos);
}

void recombinacao_uniforme(pchrom parents, pchrom offspring, int elementos) {
	int i, j;

	for (i = 0; i < POPSIZE; i += 2) {
		if (rand_01() < PR) {
			for (j = 0; j < elementos; j++) {
				if (flip() == 1) {
					offspring[i].solucao[j] = parents[i].solucao[j];
					offspring[i + 1].solucao[j] = parents[i + 1].solucao[j];
				}
				else {
					offspring[i].solucao[j] = parents[i + 1].solucao[j];
					offspring[i + 1].solucao[j] = parents[i].solucao[j];
				}
			}
		}
		else {
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}


void recombinacao_dois_pontos_corte(pchrom parents, pchrom offspring, int elementos) {
	int i, j, point1, point2;

	for (i = 0; i < POPSIZE; i += 2) {
		if (rand_01() < PR) {
			point1 = random_l_h(0, elementos - 2);
			point2 = random_l_h(point1 + 1, elementos - 1);
			for (j = 0; j < point1; j++) {
				offspring[i].solucao[j] = parents[i].solucao[j];
				offspring[i + 1].solucao[j] = parents[i + 1].solucao[j];
			}
			for (j = point1; j < point2; j++) {
				offspring[i].solucao[j] = parents[i + 1].solucao[j];
				offspring[i + 1].solucao[j] = parents[i].solucao[j];
			}
			for (j = point2; j < elementos; j++) {
				offspring[i].solucao[j] = parents[i].solucao[j];
				offspring[i + 1].solucao[j] = parents[i + 1].solucao[j];
			}
		}
		else {
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}

void genetic_operators(pchrom parents, pchrom offspring, int elementos)
{
    
	//crossover(parents, offspring, elementos);
	
	//recombinacao_dois_pontos_corte(parents, offspring, elementos);
	
	recombinacao_uniforme(parents, offspring, elementos);
	
	mutacao_por_troca(offspring, elementos);
}

void crossover(pchrom parents, pchrom offspring, int elementos) {
	int i, j, point;

	for (i=0; i<POPSIZE; i+=2) {
		if (rand_01() < PR) {
			point = random_l_h(0, elementos-1);
			for (j=0; j<point; j++) {
				offspring[i].solucao[j] = parents[i].solucao[j];
				offspring[i+1].solucao[j] = parents[i+1].solucao[j];
			}
			for (j=point; j<elementos; j++) {
				offspring[i].solucao[j]= parents[i+1].solucao[j];
				offspring[i+1].solucao[j] = parents[i].solucao[j];
			}
		}
		else {
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}


void mutacao_por_troca(pchrom offspring, int elementos) {
	int i, pos1, pos2, aux;

	for (i=0; i<POPSIZE; i++)
        if (rand_01() < PM) {
					pos1 = random_l_h(0, elementos-1);

            do {
                pos2 = random_l_h(0, elementos-1);
			} while (offspring[i].solucao[pos2] == offspring[i].solucao[pos1]);
            aux = offspring[i].solucao[pos1];
            offspring[i].solucao[pos1] = offspring[i].solucao[pos2];
            offspring[i].solucao[pos2] = aux;
        }
}
