// Thuyền trưởng Haddock (truyện Tintin) là một người luôn say xỉn. Vì thế đôi khi Tintin không biết ông ta đang say hay tỉnh. Một ngày nọ, Tintin hỏi ông ta về cách uống. Haddock nói như thế này: Có nhiều loại thức uống (soda, wine, water, …), tuy nhiên Haddock lại tuân theo quy tắc “để uống một loại thức uống nào đó cần phải uống tất cả các loại thức uống tiên quyết của nó”. Ví dụ: để uống rượu (wine), Haddock cần phải uống soda và nước (water) trước. Vì thế muốn say cũng không phải dễ !

// Cho danh sách các thức uống và các thức uống tiên quyết của nó. Hãy xét xem Haddock có thể nào say không ? Để làm cho Haddock say, ông ta phải uống hết tất cả các thức uống.

// Ví dụ 1:

// soda wine
// water wine
// Thức uống tiên quyết được cho dưới dạng a b, có nghĩa là để uống b bạn phải uống a trước. Trong ví dụ trên để uống wine, Haddock phải uống soda và water trước. Soda và water không có thức uống tiên quyết nên Haddock sẽ SAY.

// Ví dụ 2:

// soda wine
// water wine
// wine water
// Để uống wine, cần uống water. Tuy nhiên để uống water lại cần wine. Vì thế Haddock không thể uống hết được các thức uống nên ông ta KHÔNG SAY.

// Để đơn giản ta có thể giả sử các thức uống được mã hoá thành các số nguyên từ 1, 2, … và dữ liệu đầu vào được cho có dạng như sau (ví dụ 1):

// 3 2
// 1 2
// 3 2
// Có loại thức uống (soda: 1, wine: 2 và water: 3) và có 2 điều kiện tiên quyết

// 1 -> 2 và 3 -> 2.

// Với ví dụ 2, ta có dữ liệu:

// 3 3
// 1 2
// 3 2
// 2 3
// Viết chương trình đọc dữ liệu các thức uống và kiểm tra xem Haddock có thể say không. Nếu có in ra “YES”, ngược lại in ra “NO”.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

// Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số thức uống và số điều kiện tiên quyết .
// m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng thức uống u là tiên quyết của thức uống v.
// Đầu ra (Output):

// Nếu Haddock có thể say in ra YES, ngược lại in ra NO.
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
	//G->A[y][x] += 1; 
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
void dfs(Graph* G, int x) {
    color[x] = gray;
    int j;
    List list = neighbors(G, x);
    for (j = 1; j <= list.size; j++) {
        int y = element_at(&list, j);
        if (color[y] == gray) {
            cycle = 1; /* Tồn tại chu trình */
            return;
        }
        if (color[y] == white)
            dfs(G, y);
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
            dfs(G, j);
    }
    return cycle;
}

int main() {
	Graph G;
//	freopen("Dothi2.txt", "r", stdin);
	int n, m, e, u, v;
	scanf("%d %d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	
	if(contains_cycle(&G) == 1){
	    printf("NO");
	}else printf("YES");
	

}
