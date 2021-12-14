// Cho đồ thị đơn, vô hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (0 < w <= 100).

// Viết chương trình tìm đếm xem có bao nhiêu đường đi ngắn nhất từ đỉnh 1 đến n.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra (Output):

// In ra màn hình chiều dài của đường đi ngắn nhất từ 1 đến n và số đường đi có chiều dài bằng với chiều dài dường đi ngắn nhất. Nếu không có đường đi từ 1 đến n, in ra -1 0.

// Trong ví dụ đầu tiên có 2 đường đi từ 1 đến 3 là: 1 - 2 - 3 và 1 - 3. Cả hai đường đi này đều ngắn nhất và có chiều dài bằng 6.

// Xem thêm ví dụ bên dưới.

// Gợi ý:

// Ngoài pi[v], ta định nghĩa thêm cnt[v]: số đường đi ngắn nhất từ s đến v.

// Mỗi lần cập nhật pi[v] ta chú ý cập nhật lại cnt[v]. Nếu đường đi mới qua u tốt hơn thì cnt[v] = cnt[u]. Nếu bằng nhau thì cộng thêm: cnt[v] += cnt[u].
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
int cnt[MAXN];
int p[MAXN];
void Dijkstra(Graph* G, int s) {
    int i, j;
    for (i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
        mark[i] = 0;
    }
    pi[s] = 0;
    
    p[s] = -1; //trước đỉnh s không có đỉnh nào cả
    cnt[s] = 1; //so duong di ngan nhat
    // lặp n hoặc n-1 lần đều được
    for (i = 1; i < G->n; i++) {
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
                    cnt[j] = cnt[i];
            }else if(pi[i] + G->L[i][j] == pi[j])
                cnt[j] += 1;
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
        printf("-1 ");
    else printf("%d ",pi[n]);
    printf("%d",cnt[n]);
}