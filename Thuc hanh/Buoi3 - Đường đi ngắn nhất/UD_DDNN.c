// Đất nước CyberGraph có n thành phố và m con đường. Mỗi con đường nối 2 thành phố lại với nhau. tất cả các con đường đều là đường 2 chiều, mỗi con đường có một chiều dài nào đó. giữa hai thành phố có nhiều nhất là 1 con đường.

// Tổng thổng của nước này dự định sẽ đi từ thành phố s đến thành phố t. Đương nhiên, ông ta sẽ chọn hành trình có tổng chiều dài các con đường đi qua ngắn nhất.

// Hãy giúp Ngài tổng thổng tìm hành trình ngắn nhất đi từ s đến t.

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số thành phố và số con đường.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u v d mô tả con đường nối hai thành phố u và v có chiều dài d.

// - Dòng cuối cùng chứa số nguyên s t là thành phố bắt đầu và kết thúc.

// Đầu ra (Output):

// In ra màn hình tổng chiều dài các con đường của hành trình ngắn nhất..
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
	int n, m, u, v, w, e, x, y;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e <= m; e++) {
	    if(e != m){
	        scanf("%d%d%d", &u, &v, &w);
		    add_edge(&G, u, v, w);
	    }else{
	        scanf("%d%d", &x, &y);
	    }
	       
		
	}
	Dijkstra(&G, 1);
	printf("%d", pi[x] + pi[y]);
}