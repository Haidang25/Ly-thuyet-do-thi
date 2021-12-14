#include<stdio.h>
#define white 0
#define black 1
#define gray 2
#define MAX_ELEMENTS 100
#define MAX_VERTICES 100
#define MAX_VERTEXES 100
typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} Stack;

typedef int ElementType;
typedef struct {
	ElementType data[MAX_ELEMENTS];
	int size;
} List;

typedef struct {
	int n; 
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			G->A[i][j] = 0;
}

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] += 1; 
	G->A[y][x] += 1; 
}

void make_null(List* L) {
	L->size = 0;
}


void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}


ElementType element_at(List* L, int i) {
	return L->data[i-1];
}


int count_list(List* L) {
	return L->size;
}

int adjacent(Graph* G, int x, int y){
	return (G->A[x][y] != 0);
}

List neighbors(Graph *G, int x) {
	int i;
	List list;
	make_null(&list);
	for (i = 1; i <= G->n; i++)
		if (adjacent(G, x, i))
			push_back(&list, i);
	return list;
}

void make_null_stack(Stack* S) {
	S->size = 0;
}

void push(Stack* S, int x) {
	S->data[S->size] = x;
	S->size++;
}

int top(Stack* S) {
	return S->data[S->size - 1];
}

void pop(Stack* S) {
	S->size--;
}

int empty(Stack* S) {
	return S->size == 0;
}
int color[MAX_VERTICES];
int cycle;
void dfs(Graph* G, int x, int parent) {
    color[x] = gray;
    int j;
    List list = neighbors(G, x);
    for (j = 1; j <= list.size; j++) {
        int y = element_at(&list, j);
        if (y == parent) continue;
        if (color[y] == gray) {
            cycle = 1; /* Tồn tại chu trình */
            return;
        }
        if (color[y] == white)
            dfs(G, y, x);
    }
    color[x] = black;
}

int contains_cycle(Graph* G) {
    int j;
    for (j = 1; j <= G->n; j++) {
        color[j] = white;
    }
    cycle = 0;
    for (j = 1; j <= G->n; j++) {
        if (color[j] == white)
            dfs(G, j, 0);
    }
    return cycle;
}

int main() {
	Graph G;
	int n, m, e, u, v;
	scanf("%d %d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	
	if(contains_cycle(&G) == 1){
	    printf("YES");
	}else printf("NO");
	

}
