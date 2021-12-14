// David là huấn luyện viên của một đội bóng gồm N thành viên. David muốn chia đội bóng thành hai nhóm. Để tăng tính đa dạng của các thành viên trong nhóm, David quyết định không xếp hai thành viên đã từng thi đấu với nhau vào chung một nhóm. Bạn hãy lập trình giúp David phân chia đội bóng.

// Đầu vào (Input):
// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// Dòng đầu tiên chứa 2 số nguyên N và M, tương ứng là số thành viên và số cặp thành viên đã từng thi đấu với nhau.
// M dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng 2 thành viên u và v đã từng thi đấu chung với nhau.
// Đầu ra (Output):

// Nếu phân chia được, hãy in ra các thành viên của mỗi nhóm. Nhóm của thành viên 1 sẽ được in trước, nhóm còn lại in ra sau. Các thành viên trong nhóm được in ra theo thứ tự tăng dần và in trên 1 dòng. Hai thành viên cách nhau 1 khoảng trắng.
// Nếu không thể phân chia, in ra IMPOSSIBLE
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
/* Một số biến hỗ trợ */
int color[MAX_VERTEXES];
int fail;

void colorize(Graph* G, int x, int c) {
    if (color[x] == -1) {
        color[x] = c;
        List list = neighbors(G, x);
        int j;
        for (j = 1; j <= list.size; j++) {
            int y = element_at(&list, j);
            colorize(G, y, !c);
        }
    }else if (color[x] != c) 
            fail = 1; 
}


int is_bigraph(Graph* G) {
    int j;
    for (j = 1; j <= G->n; j++)
        color[j] = -1;
    fail = 0;
    colorize(G, 1, 0); 
    return !fail;
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
	if(is_bigraph(&G) == 1){
	    for(e = 1; e <= G.n; e++){
	        if(color[e] == white)
	            printf("%d ", e);
	    }
	    printf("\n");
	    for(e = 1; e <= G.n; e++){
	        if(color[e] != white)
	            printf("%d ", e);
	    }
	}else printf("IMPOSSIBLE");
}
