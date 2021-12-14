// viết chương trình kiểm tra một đồ thị có hướng (không có khuyên, không có đa cung) xem có chứa chu trình âm hay không.

// Chu trình âm là chu trình có tổng trọng số các cung trong chu trình nhỏ hơn 0.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra (Output):

// In ra màn hình negative cycle nếu đồ thị có chứa chu trình âm, ngược lại in ra ok

// Xem thêm ví dụ bên dưới.

// Chú ý:

// Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
// Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
// Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
// 	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
// 	Graph G;
// 	int n, m, u, v, w, e;
// 	scanf("%d%d", &n, &m);
// 	init_graph(&G, n);
	
// 	for (e = 0; e < m; e++) {
// 		scanf("%d%d%d", &u, &v, &w);
// 		add_edge(&G, u, v, w);
// 	}
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
int flag = 0;
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
    // Duyệt qua các cung một lần nữa
    for (k = 0; k < G->m; k++) {
        int u = G->edges[k].u;
        int v = G->edges[k].v;
        int w = G->edges[k].w;
        if (pi[u] + w < pi[v]) {
            flag = 1;   //có chu trình âm
        }
    }
}
int main() {
    //freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e,s;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e <= m; e++) {
	        if(e != m){
	            scanf("%d%d%d", &u, &v, &w);
		        add_edge(&G, u, v, w);
	        }else{
	            scanf("%d", &s);
	        }
	            
	}
	BellmanFord(&G, s);
	if(flag == 1)
	    printf("negative cycle");
	else 
        printf("ok");
}
