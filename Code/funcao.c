#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATIONS_TC  1000

float eval_individual(int *solucao, int** matriz, int* valido, int elementos, int subconjuntos) {
    int qualidade = 0;
    int numElementosSubconjuntos = elementos / subconjuntos;
    int controloSubconjuntos[SUB];
    
    for (int i = 0; i < elementos; i++) {
        controloSubconjuntos[i]=0;
    }

    for (int i = 0; i < elementos; i++) {
        for (int j = i + 1; j < elementos; j++) {
            if (solucao[i] == solucao[j]) {
                qualidade = qualidade + matriz[i][j];
            }
        }
    }

    for (int i = 0; i < elementos; i++) {
        controloSubconjuntos[solucao[i]]++;    
    }

    for (int i = 0; i < subconjuntos; i++) {
        if (controloSubconjuntos[i] != numElementosSubconjuntos) {

            *valido = 0;
            return 0;
        }
    }
    return qualidade;
}

void evaluate(pchrom pop, int** matriz, int elementos, int subconjuntos) {
	int i;

	for (i=0; i<POPSIZE; i++)
		pop[i].fitness = eval_individual(pop[i].solucao, matriz, &pop[i].valido, elementos, subconjuntos);
}

void gera_vizinho(int sol[], int solViz[], int** matriz, int nGenes, int subconjuntos) {
    
    int i, j, aux, menorCustoIn, maiorCustoOut;
    int p1 = 0;
    int p2 = 0;


    for (i = 0; i < nGenes; i++)
        solViz[i] = sol[i];
  
        
    do {
        i = random_l_h(0, nGenes - 1);
        j = random_l_h(0, nGenes - 1);

    } while (i == j);
    aux = solViz[i];
    solViz[i] = solViz[j];
    solViz[j] = aux;
        
    menorCustoIn = POPSIZE;
    maiorCustoOut = 0;
    int a = random_l_h(0, subconjuntos - 1);
    int b = random_l_h(0, subconjuntos - 1);
    for (i = 0; i < nGenes; i++) {
        for (j = 0; j < nGenes; j++) {
            if (sol[i] == a && menorCustoIn > matriz[i][j])
            {
                menorCustoIn = matriz[i][j];
                p1 = i;
            }
            if (sol[i] == b && maiorCustoOut < matriz[i][j])
            {
                maiorCustoOut = matriz[i][j];
                p2 = i;
            }
        }
    }
    solViz[p1] = a;
    solViz[p2] = b;
   
}


void trepa_colinas(pchrom pop, int** matriz, int elementos, int subconjuntos) {
    int     i, j;
    chrom   vizinho;

    for (i=0; i<POPSIZE; i++) {

        for (j=0; j<DEFAULT_ITERATIONS; j++) {
           
            gera_vizinho(pop[i].solucao, vizinho.solucao, matriz, elementos, subconjuntos);
            vizinho.fitness = eval_individual(vizinho.solucao, matriz, &vizinho.valido, elementos, subconjuntos);
            if (vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
        }
    }
}

//int trepa_colinas_4_vizinhancas(int* solucao, int** matriz, int elementos, int iterations) {
//
//    int* nova_solucao, qualidade, qualidade_vizinhanca, i;
//    int* nova_solucao2, * nova_solucao3;
//    int qualidade_vizinhanca2, qualidade_vizinhanca3;
//
//
//    nova_solucao = malloc(sizeof(int) * elementos);
//    nova_solucao2 = malloc(sizeof(int) * elementos);
//    nova_solucao3 = malloc(sizeof(int) * elementos);
//
//
//    if (nova_solucao == NULL || nova_solucao2 == NULL || nova_solucao3 == NULL) {
//        printf("Erro na alocacao de memoria");
//        exit(1);
//    }
//
//    qualidade = calcula_fit(matriz, solucao, elementos);
//    for (i = 0; i < iterations; i++) {
//
//
//
//        gera_vizinho(solucao, nova_solucao, elementos);
//        gera_vizinho(solucao, nova_solucao2, elementos);
//        gera_vizinho(solucao, nova_solucao3, elementos);
//        qualidade_vizinhanca = calcula_fit(matriz, nova_solucao, elementos);
//        qualidade_vizinhanca2 = calcula_fit(matriz, nova_solucao2, elementos);
//        qualidade_vizinhanca3 = calcula_fit(matriz, nova_solucao3, elementos);
//
//
//        if (qualidade_vizinhanca > qualidade_vizinhanca2) {
//            if (qualidade_vizinhanca > qualidade_vizinhanca3) {
//                if (qualidade_vizinhanca >= qualidade) {
//                    substitui(solucao, nova_solucao, elementos);
//                    qualidade = qualidade_vizinhanca;
//                }
//            }
//            else {
//                if (qualidade_vizinhanca3 >= qualidade) {
//                    substitui(solucao, nova_solucao3, elementos);
//                    qualidade = qualidade_vizinhanca3;
//                }
//            }
//        }
//        else {
//            if (qualidade_vizinhanca2 > qualidade_vizinhanca3) {
//                if (qualidade_vizinhanca2 >= qualidade) {
//                    substitui(solucao, nova_solucao2, elementos);
//                    qualidade = qualidade_vizinhanca2;
//                }
//            }
//            else {
//
//                if (qualidade_vizinhanca3 >= qualidade) {
//                    substitui(solucao, nova_solucao3, elementos);
//                    qualidade = qualidade_vizinhanca3;
//                }
//
//            }
//        }
//    }
//
//
//    free(nova_solucao);
//    free(nova_solucao2);
//    free(nova_solucao3);
//
//    return qualidade;
//}

//int calcula_fit(int** matriz, int* conjunto, int elementos)
//{
//    int qualidade = 0;
//
//    for (int i = 0; i < elementos; i++) {
//        for (int j = i + 1; j < elementos; j++) {
//            if (conjunto[i] == conjunto[j]) {
//                qualidade = qualidade + matriz[i][j];
//            }
//        }
//    }
//
//    return qualidade;
//}

//void substitui(int a[], int b[], int n) {
//    for (int i = 0; i < n; i++) {
//        a[i] = b[i];
//    }
//}