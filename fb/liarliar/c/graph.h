#ifndef GRAPH_H_
#define GRAPH_H_

#define	MAXV		10000	/* maximum number of vertices */

typedef struct edgenode {
	int y;				    /* adjancency info */
	int weight;			    /* edge weight, if any */
	struct edgenode *next;	/* next edge in list */
} edgenode;

typedef struct {
	edgenode *edges[MAXV+1];/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			    /* number of edges in the graph */
	int directed;			/* is the graph directed? */
} graph;

void initialize_graph(graph *g, bool directed);
void read_graph(FILE *fp, graph *g, bool directed);
void insert_edge(graph *g, int x, int y, bool directed);
void print_graph(graph *g);

#endif
