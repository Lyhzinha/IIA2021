#define MAX_ELEMENTS 250		

typedef struct individual chrom, *pchrom;

struct individual {
    int     solucao[MAX_ELEMENTS];
	float   fitness;
	int     valido;
};

void tournament_geral(pchrom, pchrom);

void genetic_operators(pchrom, pchrom, int elementos);

void crossover(pchrom, pchrom, int elementos);

void mutacao_por_troca(pchrom, int elementos);
