#include <stdio.h>
#include <stdlib.h>

typedef unsigned int bool;

typedef struct {
	int start;
	int finish;
	int weight;
} gene;

#define TRUE  1
#define FALSE 0

bool read_input(const char *fname, gene **g, int *gsize)
{
    FILE *fp;
    int r, i; 
    int dna_len = 0, gcount;
    char dna_line[80];
    gene *g_tmp;
    
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return FALSE;
    }
    
    r = fscanf(fp, "%d", &dna_len);
#ifdef DEBUG
    printf("dna_len: %d\n", dna_len);
#endif
    
    while (dna_len > 0 && !feof(fp)) {
        r = fscanf(fp, "%s", dna_line);
        dna_len -= 80;
#ifdef DEBUG
		printf("dna_line: %s\n", dna_line);
#endif
    }
    
    r = fscanf(fp, "%d", gsize);
    
#ifdef DEBUG
    printf("gsize: %d\n", *gsize);
#endif
	
	g_tmp = (gene *)malloc((*gsize) * sizeof(gene));
	if (!g_tmp) {
		return FALSE;
	}

	i = 0;
	gcount = *gsize;
    while (gcount > 0 && !feof(fp)) {
        r = fscanf(fp, "%d %d %d", &g_tmp[i].start, &g_tmp[i].finish, &g_tmp[i].weight);
        --gcount;
        ++i;
    }
    *g = g_tmp;
    
    return TRUE;
}

int compare_genes(const void *pa, const void *pb) {
	gene *a = (gene *)pa;
	gene *b = (gene *)pb;
	
	return (a->finish - b->finish);
}

int profit(gene *g, int gsize)
{
	int i, j;
	int comp[gsize], profit[gsize+1];
	int start, finish, incl, excl;
	
	for (i = 0; i < gsize; ++i) {
		comp[i] = -1;
	}
	
	for (i = 0; i < gsize; ++i) {
		start = g[i].start;
		
		for (j = i - 1; j >= 0; --j) {
			finish = g[j].finish;
			if (finish < start) {
                comp[i] = j;
                break;
            }
		}
	}
	
	profit[0] = 0;
	for (i = 1; i < gsize + 1; ++i) {
		incl = g[i-1].weight + profit[comp[i-1]+1];
		excl = profit[i-1];
		profit[i] = (incl > excl) ? incl : excl;
	}
	
	return profit[gsize];
}

int main(int argc, char *argv[])
{
	gene *g;
	int gsize, i;
	
	i = 0;
	
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (!read_input(argv[1], &g, &gsize)) {
        fprintf(stderr, "Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
	printf("Genes (unsorted):\n");
    for (i = 0; i < gsize; i++) {
		printf("%d %d %d\n", g[i].start, g[i].finish, g[i].weight);
	}
#endif

	qsort(g, gsize, sizeof(gene), compare_genes);

#ifdef DEBUG
	printf("Genes (sorted):\n");
    for (i = 0; i < gsize; i++) {
		printf("%d %d %d\n", g[i].start, g[i].finish, g[i].weight);
	}
#endif

    printf("%d\n", profit(g, gsize));
    
    free(g);
        
    return 0;
}
