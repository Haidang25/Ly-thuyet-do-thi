#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
int n, m; 
typedef int Vertices;

typedef struct
{
    int matrix[maxv][maxv];
    Vertices n; 
} Graph;

typedef struct
{
    int data[idx];
    int size;
} List;




void makenullList(List *L)
{
    L->size = 0;
}

// Kiểm tra danh sách có rỗng hay không
bool emptyList(List *L)
{
    return (L->size == 0);
}

// Thêm một phần tử vào danh sách
void pushList(List *L, int element)
{
    L->data[L->size] = element;
    L->size++;
}

// Truy cập một phần tử trong danh sách bắt đầu từ vị trí thứ 1
int getList(List *L, int index)
{
    return L->data[index - 1];
}

/*Các hàm thao tác trên đồ thị*/
void initGraph(Graph *G)
{
    G->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G->matrix[i][j] = 0;
}

void addEdge(Graph *g, int x, int y)
{
    g->matrix[y][x] = 1;
}

bool adjacent(Graph *g, int x, int y)
{
    return g->matrix[x][y] == 1;
}

// Tính số bậc vào của 1 đỉnh trong đồ thị 
int degreeInput(Graph *g, int x)
{
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (adjacent(g, i, x))
        {
            count++;
        }
    }
    return count;
}


List neighbors(Graph *G, int x)
{
    List L;
    makenullList(&L);
    for (int i = 1; i <= n; i++)
    {
        if (adjacent(G, x, i))
        {
            pushList(&L, i);
        }
    }
    return L;
}

// Sao chép phần tử của danh sách này sang danh sách khác
void copyList(List *L1, List *L2)
{
    makenullList(L1);
    for (int i = 1; i <= L2->size; i++)
    {
        int value = getList(L2, i);
        pushList(L1, value);
    }
}

// Các biến toàn cục để phục vụ cho giải thuật xếp hạng đồ thị
int rank[maxv]; // Mảng rank[] để lưu hạng của tất cả các đỉnh trong đồ thị
int d[maxv];    // Mảng d-Degree  để lưu số bậc vào của tất cả các đỉnh trong đồ thị
List L1, L2;    // Danh sách L1 lưu những đỉnh có bậc vào bằng 0(gốc cũ), danh sách L2 lưu những đỉnh kề v của u có bậc vào bằng 0(gốc mới)
int k = 1;      // Bước lặp của giải thuật sở dĩ bắt đầu bằng 1 vì đề bài có nói là các em được đánh số từ 1 đến n

// Giải thuật xếp hạng đồ thị
void ranking(Graph *G)
{
    int u;
    for (u = 1; u <= n; u++)
        d[u] = 0; // Khởi tạo các đỉnh có bậc vào điều bằng 0
    for (u = 1; u <= n; u++)
        d[u] = degreeInput(G, u); // Tính bậc vào cho các đỉnh rồi lưu vào mảng d[]
    makenullList(&L1);            // Khởi tạo danh sách L1 lưu những đỉnh gốc(đỉnh có bậc vào bằng 0)
    for (u = 1; u <= n; u++)
        if (d[u] == 0)
            pushList(&L1, u); // Những đỉnh nào là đỉnh gốc sẽ được cho vào danh sách L1(Gốc cũ)
    while (!emptyList(&L1))
    {                      // Duyệt trong khi L1 chưa rỗng
        makenullList(&L2); // Khởi tạo danh sách L2 để chứa các đỉnh kề v của u có bậc vào bằng 0(Gốc mới)
        for (int i = 1; i <= L1.size; i++)
        {                             // Duyệt các đỉnh gốc vừa được thêm trong danh sách L1
            int u = getList(&L1, i);  // Lấy đỉnh gốc ra
            rank[u] = k;              // Xếp hạng cho đỉnh gốc bằng bước lặp k
            List L = neighbors(G, u); // Tìm đỉnh kề của đỉnh vừa được xếp hạng
            for (int j = 1; j <= L.size; j++)
            {                           // Duyệt các đỉnh kề
                int v = getList(&L, j); // Lấy đỉnh kề
                d[v]--;                 // Giảm bậc đỉnh kề đi 1 tương đương với việc xóa đỉnh gốc u(gốc mới) ra khỏi đồ thị
                if (d[v] == 0)
                {                     // Nếu đỉnh kề v là đỉnh gốc(gốc mới)
                    pushList(&L2, v); //Đưa đỉnh gốc mới vào danh sách L2
                }
            }
        }
        copyList(&L1, &L2); // Sao chép các đỉnh gốc mới trong L2 sang L1
        k++;                // Tăng bước lặp lên để xếp hạng cho các đỉnh tiếp theo trong danh sách L1
        // Khi nào danh sách L2 rỗng tức đỉnh gốc cũ không có đỉnh kề thì hiển nhiên -> Giải thuật kết thúc -> vì lúc này L1 đã rỗng
    }
}
int main()
{
    Graph G;
    int u, v;
    scanf("%d%d", &n, &m);
    initGraph(&G);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addEdge(&G, u, v);
    }
    ranking(&G);
    int sum = 0;
    for (int u = 1; u <= n; u++)
    {
        printf("%d\n", rank[u]);
        sum += rank[u];
    }
    printf("%d", sum);
    return 0;
}