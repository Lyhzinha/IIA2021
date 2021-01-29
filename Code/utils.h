#define MAXCHARSIZE 100
#define DEFAULT_RUNS	30
#define DEFAULT_ITERATIONS 50

#define POPSIZE 100
#define PM 0.05
#define PR 0.5
#define TSIZE 2
#define MAX_GEN 2500
#define SUB 250

int** init_dados(char* nome, int* elementos, int* subconjuntos);

pchrom init_pop(int elementos, int subconjuntos);

void gera_solucao_inicial(int* solucao, int elementos, int subconjuntos);

chrom get_best(pchrom, chrom);

void write_best(chrom, int elementos);

void init_rand();

int random_l_h(int, int);

float rand_01();

int flip();
