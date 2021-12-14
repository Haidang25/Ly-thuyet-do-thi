// Cho đồ thị có hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (-100 < w <= 100).

// Viết chương trình tìm đường đi ngắn nhất từ đỉnh 1 đến các đỉnh còn lại.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// Dòng đầu tiên chứa 2 số nguyên n và m.
// m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.
// Dữ liệu được đảm bảo không tồn tại chu trình âm.

// Đầu ra (Output):

// In ra màn hình các giá trị pi và p của các đỉnh theo thứ tự 1, 2, ..., n.

// Xem thêm ví dụ bên dưới.
#include <stdio.h>
#define INFINITY 999999
#define MAXN 1000
#define NO_EDGE 0
typedef struct {
    int u, v; // đỉnh đầu v, đỉnh cuối v
    int w; // trọng số w
} Edge;
typedef struct {
    int n, m; // n: đỉnh, m: cung
    Edge edges[1000]; // lưu các cung của đồ thị
} Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    G->m = 0;
}
void add_edge(Graph* G, int u, int v, int w) {
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}
int pi[MAXN];
int p[MAXN];
void BellmanFord(Graph* G, int s) {
    int i, it, k;
    for (i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
    }
    pi[s] = 0;
    p[s] = -1; //trước đỉnh s không có đỉnh nào cả
    // lặp n hoặc n-1 lần đều được
    for (it = 1; it < G->n; it++) {
    // Duyệt qua các cung và cập nhật (nếu thoả)
        for (k = 0; k < G->m; k++) {
            int u = G->edges[k].u;
            int v = G->edges[k].v;
            int w = G->edges[k].w;
            if (pi[u] + w < pi[v]) {
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }
}
int main() {
    //freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e, i;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e <= m; e++) {
	        scanf("%d%d%d", &u, &v, &w);
		    add_edge(&G, u, v, w);
	}
	BellmanFord(&G, 1);
	for (i = 1; i <= G.n; i++)
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
}