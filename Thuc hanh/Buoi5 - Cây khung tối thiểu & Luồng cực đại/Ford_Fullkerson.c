// Viết chương trình tìm luồng cực đại trên mạng bằng thuật toán Ford - Fullkerson (duyệt theo chiều rộng).

// Đầu vào (Input):

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra (Output):

// In ra màn hình theo định dạng sau:

// - Dòng đầu tiên in luồng cực đại theo dạng: Max flow: s

// - Dòng thứ hai in các đỉnh của X0 theo dạng: X0: x1 x2 ..., mỗi đỉnh cách nhau 1 khoảng trắng

// - Dòng thứ ba in các đỉnh của Y0 theo dạng: Y0: y1 y2 ..., mỗi đỉnh cách nhau 1 khoảng trắng
#include <stdio.h>
#define MAXN 100
#define NO_EDGE 0
#define INF 999999
typedef struct
{
    int C[MAXN][MAXN];
    int F[MAXN][MAXN];
    int n;
} Graph;
void init_graph(Graph *G, int n)
{
    G->n = n;
}
typedef struct
{
    int dir;
    int pre;
    int sigma;
} Label;
Label labels[MAXN];
void init_flow(Graph *G)
{
    int u, v;
    for (u = 1; u <= G->n; u++)
        for (v = 1; v <= G->n; v++)
            G->F[u][v] = 0;
}
typedef struct
{
    int data[MAXN];
    int front, rear;
} Queue;
void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}
void enqueue(Queue *Q, int x)
{
    Q->rear++;
    Q->data[Q->rear] = x;
}
int top(Queue *Q)
{
    return Q->data[Q->front];
}
void dequeue(Queue *Q)
{
    Q->front++;
}
int empty(Queue *Q)
{
    return Q->front > Q->rear;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
int FordFullkerson(Graph *G, int s, int t)
{
    init_flow(G);
    int u, v, sum_flow = 0;
    Queue Q;
    do
    {
        for (u = 1; u <= G->n; u++)
            labels[u].dir = 0;
        labels[s].dir = 1;
        labels[s].pre = s;
        labels[s].sigma = INF;
        make_null_queue(&Q);
        enqueue(&Q, s);
        int found = 0;
        while (!empty(&Q))
        {
            int u = top(&Q);
            dequeue(&Q);
            for (v = 1; v <= G->n; v++)
            {
                if (labels[v].dir == 0 && G->C[u][v] != NO_EDGE && G->F[u][v] < G->C[u][v])
                {
                    labels[v].dir = 1;
                    labels[v].pre = u;
                    labels[v].sigma = min(labels[u].sigma, G->C[u][v] - G->F[u][v]);
                    enqueue(&Q, v);
                }
                if (labels[v].dir == 0 && G->C[v][u] != NO_EDGE && G->F[v][u] > 0)
                {
                    labels[v].dir = -1;
                    labels[v].pre = u;
                    labels[v].sigma = min(labels[u].sigma, G->F[u][v]);
                    enqueue(&Q, v);
                }
            }
            if (labels[t].dir != 0)
            {
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            int x = t;
            int sigma = labels[t].sigma;
            sum_flow += sigma;
            while (x != s)
            {
                int u = labels[x].pre;
                if (labels[x].dir > 0)
                    G->F[u][x] += sigma;
                else
                    G->F[x][u] -= sigma;
                x = u;
            }
        }
        else
            break;
    } while (1);
    return sum_flow;
}
int main()
{
    // ffreopen("dt.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
    Graph G;
    int n, m, u, v, c, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (e = 0; e < m; e++)
    {
        scanf("%d%d%d", &u, &v, &c);
        G.C[u][v] = c;
    }
    int max_flow = FordFullkerson(&G, 1, n);
    printf("Max flow: %d \n", max_flow);
    printf("X0: ");
    for (e = 1; e <= G.n; e++)
    {
        if (labels[e].dir != 0)
            printf("%d ", e);
    }
    printf("\nY0: ");
    for (e = 1; e <= G.n; e++)
    {
        if (labels[e].dir == 0)
            printf("%d ", e);
    }
    return 0;
}