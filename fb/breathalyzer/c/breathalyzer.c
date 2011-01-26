#include <string.h>
#include <stdio.h>

#define MAXLEN          101     /* longest possible string */

#define MATCH           0       /* enumerated type symbol for match */
#define INSERT          1       /* enumerated type symbol for insert */
#define DELETE          2       /* enumerated type symbol for delete */

typedef struct {
        int cost;               /* cost of reaching this cell */
        int parent;             /* parent cell */
} cell;

#define TRUE    1
#define FALSE   0

typedef int bool;
typedef unsigned int uint;


//#include "editdistance.h"
//#include "bool.h"

cell m[MAXLEN+1][MAXLEN+1];	/* dynamic programming table */


/*	For normal edit distance computation  */

void goal_cell(char *s, char *t, uint *i, uint *j)
{
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}

int match(char c, char d)
{
    if (c == d) {
        return(0);
    }
        
    return 1;
}

int indel(char c)
{
    return 1;
}

void row_init(int i)		
{
    m[0][i].cost = i;
    if (i > 0) {
        m[0][i].parent = INSERT;
    } else {
        m[0][i].parent = -1;
    }
}

void column_init(int i)	
{
    m[i][0].cost = i;
    if (i > 0) {
        m[i][0].parent = DELETE;
    } else {
        m[0][i].parent = -1;
    }
}

void match_out(char *s, char *t, int i, int j)
{
    if (s[i] == t[j]) {
        printf("M");
    } else {
        printf("S");
    }
}

void insert_out(char *t, int j)
{
    printf("I");
}

void delete_out(char *s, int i)
{
    printf("D");
}

int string_compare(char *s, char *t)
{
    uint i, j, k;
    int opt[3];

    for (i = 0; i < MAXLEN; i++) {
        row_init(i);
        column_init(i);
    }
    //print_matrix(s, t, TRUE);

    for (i = 1; i < strlen(s); i++) {
        for (j = 1; j < strlen(t); j++) {
            opt[MATCH]  = m[i-1][j-1].cost + match(s[i], t[j]);
            opt[INSERT] = m[i][j-1].cost + indel(t[j]);
            opt[DELETE] = m[i-1][j].cost + indel(s[i]);

            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (k = INSERT; k <= DELETE; k++) {
                if (opt[k] < m[i][j].cost) {
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                }
            }
        }
    }

    goal_cell(s, t, &i, &j);
    
    return m[i][j].cost;
} 

void print_matrix(char *s, char *t, bool costQ)
{
	int i,j;			/* counters */
	int x,y;			/* string lengths */

	x = strlen(s);
	y = strlen(t);

	printf("   ");
	for (i = 0; i < y; i++) {
		printf("  %c", t[i]);
    }
	printf("\n");

	for (i = 0; i < x; i++) {
		printf("%c: ", s[i]);
		for (j = 0; j < y; j++) {
			if (costQ == TRUE) {
				printf(" %2d", m[i][j].cost);
			} else {
				printf(" %2d", m[i][j].parent);
            }
		}
		printf("\n");
	}
}

int main() {
	uint i, j, r;
	char s[MAXLEN], t[MAXLEN];		/* input strings */

	s[0] = t[0] = ' ';

	r = scanf("%s", &(s[1]));
	r = scanf("%s", &(t[1]));

	printf("matching cost = %d \n", string_compare(s, t));

    print_matrix(s, t, TRUE);
	printf("\n");

/*
	
	print_matrix(s,t,FALSE);

	goal_cell(s,t,&i,&j);

	printf("%d %d\n",i,j);

	reconstruct_path(s,t,i,j);
*/
	printf("\n");
    
    return 0;
}
