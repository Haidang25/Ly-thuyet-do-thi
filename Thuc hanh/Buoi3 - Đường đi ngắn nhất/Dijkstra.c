// Cho đồ thị có hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

// Viết chương trình tìm đường đi ngắn nhất từ đỉnh 1 đến n.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra (Output):

// In ra màn hình chiều dài của đường đi ngắn nhất từ 1 đến n. Nếu không có đường đi từ 1 đến n, in ra -1.

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
// 		scanf("%d%d%d", &u, &v, &c);
// 		add_edge(&G, u, v, w);
// 	}

#include <stdio.h>
#define INFINITY 999999
#define MAXN 1000
#define NO_EDGE 0
typedef struct {
    int n;
    int L[MAXN][MAXN];
} Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    int i, j;   
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->L[i][j] = NO_EDGE;
}
void add_edge(Graph *G, int u, int v, int w ) {
    G->L[u][v] = w;
}
int mark[MAXN];
int pi[MAXN];
int p[MAXN];
void Dijkstra(Graph* G, int s) {
    int i, j, it;
    for (i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
        mark[i] = 0;
    }
    pi[s] = 0;
    p[s] = -1; //trước đỉnh s không có đỉnh nào cả
    // lặp n hoặc n-1 lần đều được
    for (it = 1; it < G->n; it++) {
        //1. Tìm i có mark[i] == 0 va có pi[i] nhỏ nhất
        int min_pi = INFINITY;
        for (j = 1; j <= G->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi) {
                min_pi = pi[j];
                i = j;
            }
        //Đánh dấu i đã xét
        mark[i] = 1;
        //2. Cập nhật pi và p của các đỉnh kề của i (nếu thoả)
        for (j = 1; j <= G->n; j++)
            if (G->L[i][j] != NO_EDGE && mark[j] == 0) {
                if (pi[i] + G->L[i][j] < pi[j]) {
                    pi[j] = pi[i] + G->L[i][j];
                    p[j] = i;

            }
        }
    }
}

int main() {
    //freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	Dijkstra(&G, 1);
	if(pi[n] == INFINITY)
	    printf("-1");
	else printf("%d", pi[n]);
}