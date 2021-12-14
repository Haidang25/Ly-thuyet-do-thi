// Viết chương trình đếm số bộ phận liên thông mạnh (BPLTM) của một đồ thị có hướng.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

// Chú ý: đồ thị không chứa đa cung.

// Đầu ra (Output):

// In ra màn hình một con số nguyên duy nhất chỉ số BPTLM của đồ thị.

// Xem thêm ví dụ bên dưới.
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
	//G->A[y][x] += 1; //x ke voi y	Da cung
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

int num[MAX_VERTEXES], min_num[MAX_VERTEXES], on_stack[MAX_VERTEXES];
int k = 1;


int min(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}
int count = 0;
void strong_connect(Graph* G, int x) {
    num[x] = min_num[x] = k;
    k++;
    Stack S;
    make_null_stack(&S);
    push(&S, x);
    on_stack[x] = 1;
    List list = neighbors(G, x);
    int j;
    
    for (j = 1; j <= list.size; j++) {
        int y = element_at(&list, j);
        if (num[y] < 0) {
            strong_connect(G, y);
            min_num[x] = min(min_num[x], min_num[y]);
        } else if (on_stack[y] == 1){
            min_num[x] = min(min_num[x], num[y]);
            
        }
    }
    if (num[x] == min_num[x]) {
        count+= 1;
        int w;
        do {
            w = top(&S);
            pop(&S);
            on_stack[w] = 0;
        } while (w != x);
    }

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
	for (v = 1; v <= n; v++) {
        num[v] = -1;
        on_stack[v] = 0;
    }
    strong_connect(&G, 1);
	printf("%d",count);
	
}
