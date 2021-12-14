// Viết chương trình tìm cây khung có trọng số nhỏ nhất bằng giải thuật Kruskal.

// Đầu vào:

// Dữ liệu đầu vào được nhập từ bàn phím với định dạng

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

// Đầu ra:

// In ra màn hình trọng số của cây khung tìm được và danh sách các cung theo thứ tự tăng dần của trọng số.

// Quy ước: các cung được in ra theo định dạng:

// u v w

// với (u < v), mỗi cung trên 1 dòng. Nếu hai cung có trọng số bằng nhau thì cung nào có u nhỏ hơn sẽ được in trước. Nếu có trọng số bằng nhau và u giống nhau thì cung nào có v nhỏ hơn sẽ in trước.
#include <stdio.h>
#define MAX 100
// Do Thi G ma tran Ke
typedef struct {
 int x,y,z;
}Edge;
typedef struct {
int n,m;
Edge Data[MAX];
}dothi;
void khoitao(dothi *G,int n){
G->n = n;
G->m = 0;
}
void themcung(dothi *G,int x,int y, int W){
G->Data[G->m].x = x;
G->Data[G->m].y = y;
G->Data[G->m].z = W;
G->m++;
}
int parent[100];
int findRoot (int u){
if (parent[u] == u)
return u;
return findRoot(parent[u]);
}
int Kruskal (dothi *G, dothi *T){
int i,j,e,u;
Edge temp;
for (i=0;i< G->m;i++)
for(j=i+1;j< G->m; j++){
if(G->Data[i].z > G->Data[j].z){
temp = G->Data[i];
G->Data[i] = G->Data[j];
G->Data[j] = temp;
}
}
khoitao(T,G->n);
for (u=1;u <= G->n; u++)
parent[u] = u;
int sum_w = 0;
for(e=0;e < G->m ; e++){
int u = G->Data[e].x;
int v = G->Data[e].y;
int w = G->Data[e].z;
int root_u = findRoot(u);
int root_v = findRoot(v);
if(root_u != root_v){
if (u<v) 
themcung(T,u,v,w);
else themcung(T,v,u,w);
parent[root_v] = root_u;
sum_w += w;
}
}
return sum_w;
}
int main(){
//freopen("dt.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
dothi G,T;
int n, m, u, v, w, e;
scanf("%d%d", &n, &m);
khoitao(&G, n);
//khoitao(&T, n);
for (e = 0; e < m; e++) {
scanf("%d%d%d", &u, &v, &w);
themcung(&G, u, v, w);
}
int sum_w = Kruskal(&G,&T);
printf("%d \n",sum_w);
for (e=0;e <T.m ; e++)
printf("%d %d %d \n",T.Data[e].x,T.Data[e].y,T.Data[e].z);
}