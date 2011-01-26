#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "graph.h"
#include "bfs.h"


#define UNCOLORED	0		/* vertex not yet colored */
#define WHITE		1		/* white vertex */
#define BLACK		2		/* black vertex */

int color[MAXV+1];			/* assigned color of v */
bool bipartite;				/* is the graph bipartite? */
extern bool discovered[];	/* which vertices have been found */

int complement(int color)
{
	if (color == WHITE) return(BLACK);
	if (color == BLACK) return(WHITE);
	
	return(UNCOLORED);
}

void process_edge(int x, int y)
{
	if (color[x] == color[y]) {
		bipartite = FALSE;
#ifdef DEBUG		
		printf("Warning: graph not bipartite, due to (%d,%d)\n",x,y);
#endif
	}	

	color[y] = complement(color[x]);
}

void twocolor(graph *g)
{
	int i;				/* counter */

	for (i=1; i<=(g->nvertices); i++) 
		color[i] = UNCOLORED;

	bipartite = TRUE;
 
	initialize_search(g);

	for (i=1; i<=(g->nvertices); i++) {
		if (discovered[i] == FALSE) {
			//printf("i: %d\n", i);
			color[i] = WHITE;
			bfs(g,i);
		}
    }
}

int main(int argc, char *argv[])
{
	FILE *fp;
	graph g;
	int i;
	int total_colors[] = {0, 0, 0};
	int max, min;
	
	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}
	
	fp = fopen(argv[1], "r");

	if (fp == NULL) {
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		exit(1);
	}

	read_graph(fp, &g, TRUE);
	//print_graph(&g);
	twocolor(&g);

	for (i=1; i<=(g.nvertices); i++) {
		//printf(" %d",color[i]);
		switch (color[i]) {
		case UNCOLORED:
			total_colors[0]++;
			break;
		
		case WHITE:
			total_colors[1]++;
			break;
			
		case BLACK:
			total_colors[2]++;
			break;
			
		}
	}
#ifdef DEBUG
	printf("TOTAL: %d\n", g.nvertices);
	printf("WHITE: %d\n", total_colors[1]);
	printf("BLACK: %d\n", total_colors[2]);
	printf("UNCOLORED: %d\n", total_colors[0]);
#endif

	max = (total_colors[1] > total_colors[2]) ? total_colors[1] : total_colors[2];
	min = (total_colors[1] > total_colors[2]) ? total_colors[2] : total_colors[1];
	
	printf("%d %d\n", max, min);
        
    return 0;
}
