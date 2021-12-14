#include<stdio.h>
/* Khai bao Stack*/
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

int mark[MAX_VERTEXES];
int parent[MAX_VERTEXES];
void traversal(Graph* G, int x, int p) {
	if (mark[x] == 1)
		return;
	//printf("Duyet %d\n", x);
	parent[x] = p;
	mark[x] = 1;
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int v = element_at(&list, j);
		traversal(G, v, x);
	}
}

int main() {
	Graph G;
	int n, m, e, u, v, i;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	for(i = 1; i <= n; i++) {
		mark[i] = 0;
		parent[i]= -1;
	}
	for(i = 1; i <= n; i++) {
		if(mark[i] == 0)
		traversal(&G, i, 0);

	}

	for(i = 1; i <= n; i++) {
		printf("%d %d\n", i, parent[i]);
	}
}
