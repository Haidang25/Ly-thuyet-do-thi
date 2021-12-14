#include<stdio.h>
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
	G->A[x][y] += 1; //y ke voi x	Da cung
	G->A[y][x] += 1; //x ke voi y	Da cung
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

List depth_first_search(Graph* G, int x) {
	List list_dfs;
	make_null(&list_dfs);
	Stack frontier;
	make_null_stack(&frontier);
	push(&frontier, x);
	int mark[MAX_VERTEXES];
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	while (!empty(&frontier)) {
		int u = top(&frontier);
		pop(&frontier);
		if(mark[u] == 1)
			continue;
		push_back(&list_dfs, u);
		mark[u] = 1;
		List list = neighbors(G, u);
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			if (mark[y] == 0) {
				push(&frontier, y);
				//mark[y] = 1;
			}
		}
	}
	return list_dfs;
}


int main() {
	Graph G;
	int n, m, e, u, v, i, j;
	scanf("%d %d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	int mark_dfs[MAX_VERTEXES];
	for(i = 1; i <= G.n; i++) {
		mark_dfs[i] = 0;
	}

	for(i = 1; i <= G.n; i++) {
		if(mark_dfs[i] == 0) {
			List dfs = depth_first_search(&G, i);
			for(j = 1; j <= dfs.size; j++) {
				int k = element_at(&dfs, j);
				printf("%d\n", k);
				mark_dfs[k] = 1;
			}
		}
	}
	return 0;
	
}
