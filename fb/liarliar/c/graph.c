#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "graph.h"

unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c 
	}

	return hash;
}

void initialize_graph(graph *g, bool directed)
{
	int i;				

	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
	for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

int check_item(unsigned long *items, int size, unsigned long item)
{
    int i;
    
    for (i = 0; (items[i] != 0) && (i < size); i++) {
        if (items[i] == item) {
            return i + 1;
        }
    }
    return 0;
}

int insert_item(unsigned long *items, int size, unsigned long item)
{
    int i;
    
    for (i = 0; i < size; i++) {
        if (items[i] == 0) {
            items[i] = item;
            return i + 1;
        }
    }
    return 0;
}

void read_graph(FILE *fp, graph *g, bool directed)
{
	int r, z;
    int i, j;		    /* counter */
	int x, y;			/* vertices in edge (x,y) */
	unsigned char name[255];
	unsigned long *items = NULL;
	unsigned long item;
        
	initialize_graph(g, directed);

	r = fscanf(fp, "%d", &(g->nvertices));
    
	items = malloc(sizeof(unsigned long) * g->nvertices);	
	for (i = 0; i < g->nvertices; i++) {
		items[i] = 0;
	}
    
	for (i = 1; !feof(fp) && i <= g->nvertices; i++) {
		r = fscanf(fp, "%s %d", name, &z);
		//printf("x: %d\tz: %d\n", x, z);
		
		item = hash(name);
        //printf("%s %lu\n", name, item);
        x = check_item(items, g->nvertices, item);
        if (!x) {
            x = insert_item(items, g->nvertices, item);
        }
        //printf("%s %d %d\n", name, z, x);
		
        for (j = 1; !feof(fp) && j <= z; j++) {
            r = fscanf(fp, "%s", name);
            
            item = hash(name);
            //printf("%s %lu\n", name, item);
            y = check_item(items, g->nvertices, item);
            if (!y) {
                y = insert_item(items, g->nvertices, item);
            }
            //printf("  %s %d\n", name, y);
            
			//printf("\tx: %d\ty: %d\n", x, y);
            insert_edge(g, x, y, directed);
        }

	}
#ifdef DEBUG	
	printf("Graph is built\n");
#endif
}

void insert_edge(graph *g, int x, int y, bool directed)
{
	edgenode *p;			        /* temporary pointer */

	p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	//p->weight = NULL;
	p->weight = 0;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;				/* insert at head of list */

	g->degree[x]++;

	if (directed == FALSE)
		insert_edge(g,y,x,TRUE);
	else
		g->nedges++;
}

void print_graph(graph *g)
{
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d",p->y);
			p = p->next;
		}
		printf("\n");
	}
}

