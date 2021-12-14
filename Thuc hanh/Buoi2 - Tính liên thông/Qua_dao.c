// Có n hòn đảo và m cây cầu. Mỗi cây cầu bắt qua 2 hòn đảo. Một hôm chúa đảo tự hỏi là với các cây cầu hiện tại thì đứng ở một hòn đảo bất kỳ có thể nào đi đến được tất cả các hòn đảo khác hay không.

// Hãy giúp chúa đảo viết chương trình kiểm tra.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đảo và số cây cầu.

// - m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng có 1 cây cầu bắt qua hai hòn đảo u và v.

// Đầu ra (Output):

// Nếu có thể đi được in ra màn hình YES, ngược lại in ra NO.
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

int num[MAX_VERTEXES], k = 1;
void traversal(Graph* G, int x) {
	if (num[x] > 0)
		return;
	num[x] = 1, k++;
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int v = element_at(&list, j);
		traversal(G, v);
	}
}

int main() {
	Graph G;
	int n, m, e, u, v, i;
	scanf("%d %d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= n; i++) {
		num[i] = -1;
	}
    traversal(&G, 1);
	int check = 1;
    for(i = 1; i <= G.n; i++){
       if(num[i] < 0){
           check = 0;
           break;
       }else check = 1;

    }
    if(check == 1)
        printf("YES");
    else printf("NO");
	

}
