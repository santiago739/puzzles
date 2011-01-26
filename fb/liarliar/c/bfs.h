#ifndef BFS_H_
#define BFS_H_

void initialize_search(graph *g);
void bfs(graph *g, int start);
void process_edge(int x, int y);

#endif
