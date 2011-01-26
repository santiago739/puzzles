#include <stdio.h>

#include "bool.h"
#include "graph.h"
#include "queue.h"
#include "bfs.h"

bool processed[MAXV+1];		/* which vertices have been processed */
bool discovered[MAXV+1];  	/* which vertices have been found */
int parent[MAXV+1];			/* discovery relation */

bool finished = FALSE;		/* if true, cut off search immediately */

void initialize_search(graph *g)
{
	int i;                          /* counter */

	for (i=0; i<=g->nvertices; i++) {
		processed[i] = discovered[i] = FALSE;
		parent[i] = -1;
	}
}

void bfs(graph *g, int start)
{
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int y;				/* successor vertex */
	edgenode *p;		/* temporary pointer */

	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;

	while (empty_queue(&q) == FALSE) {
		v = dequeue(&q);
		processed[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
		    y = p->y;
		    if ((processed[y] == FALSE) || g->directed)
				process_edge(v,y);
		    if (discovered[y] == FALSE) {
				enqueue(&q,y);
				discovered[y] = TRUE;
				parent[y] = v;
		    }
		    p = p->next;
		}
	}
}
