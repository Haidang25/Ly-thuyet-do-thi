#include<stdio.h>
#define max 50
typedef struct {
    int n;
    int A[max][max];
} Graph;
void add_edge(Graph *G, int x, int y){
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int main(){
    Graph G;
	int n, m, u, v, e;
	FILE* file = fopen("dt1.txt", "r");
	fscanf(file, "%d%d", &n, &m);
	for (e = 1; e <= n; e++) {
		fscanf(file, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(e = 1; e <= n; e++) {
	    for(v = 1; v <= n; v++){
	        printf("%d ", G.A[e][v]);
	    }
	    printf("\n");
	}
}