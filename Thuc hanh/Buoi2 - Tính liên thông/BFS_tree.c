#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_VERTICES 100
#define MAX_VERTEXES 100
typedef struct {
    int data[MAX_ELEMENTS];
    int front, rear;
} Queue;

typedef int ElementType;
typedef struct {
	ElementType data[MAX_ELEMENTS];
	int size;
} List;

typedef struct {
	int n; /* n: so dinh */
	/* ma tran dinh � dinh */
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
/* Tao danh sach rong */
void make_null(List* L) {
	L->size = 0;
}

/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}

/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1
*/
ElementType element_at(List* L, int i) {
	return L->data[i-1];
}

/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
	return L->size;
}

int adjacent(Graph* G, int x, int y){
	return (G->A[x][y] != 0);
}

/* Tim cac dinh ke cua dinh x */
List neighbors(Graph *G, int x) {
	int i;
	List list;
	make_null(&list);
	for (i = 1; i <= G->n; i++)
		if (adjacent(G, x, i))
			push_back(&list, i);
	return list;
}

void make_null_queue(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}

void push(Queue* Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}

int top(Queue* Q) {
	return Q->data[Q->front];
}

void pop(Queue* Q) {
	Q->front++;
}

int empty(Queue* Q) {
	return Q->front > Q->rear;
}

/* Duyet do thi theo chieu rong */
List breath_first_search(Graph* G, int x, int parent[]) {
	Queue Q;
	make_null_queue(&Q);
	push(&Q, x);
	parent[x] = 0;
	int mark[MAX_VERTEXES], i;
	for (i = 1; i <= G->n; i++)
		mark[i] = 0;
	List L_bfs;
	make_null(&L_bfs);
	while (!empty(&Q)) {
		int u = top(&Q); 
		pop(&Q);
		if(mark[u] == 1)
			continue;
		push_back(&L_bfs, u);
		mark[u] = 1;
		List L = neighbors(G, u);
		int v;
		for (i = 1; i <= L.size; i++) {
			v = element_at(&L, i);
			if (mark[v] == 0){
				push(&Q, v);
				if(parent[v] == -1)
				    parent[v] = u;
			}
				
		} 
	}
	return L_bfs;
}
int main() {
	Graph G;
	int n, m, e, u, i, v;
	scanf("%d %d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
	    scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	int mark_dfs[MAX_VERTEXES], parent[MAX_VERTEXES];
	for(u = 1; u <= G.n; u++) {
		mark_dfs[u] = 0;
		parent[u] = -1;
	}
    
	for(u = 1; u <= G.n; u++) {
		if(mark_dfs[u] == 0) {
			List L = breath_first_search(&G, u, parent);
			for(i = 1; i <= L.size; i++) {
				v = element_at(&L, i);
				//printf("%d %d\n", v, parent[v]);
				mark_dfs[v] = 1;
			}
		}
	}
	
	for(u = 1; u <= G.n; u++) {
	    printf("%d %d\n",u, parent[u]);
	}
	return 0;
	
	
}
