/*
*问题描述：学校需要将n台计算机连接起来，不同的2台计算机之间的连接费用可能是不同的。
*为了节省费用，我们考虑采用间接数据传输结束，就是一台计算机可以间接地通过其他计算机实现和另外一台计算机连接。
*为了使得任意两台计算机之间都是连通的（不管是直接还是间接的），现在想使得总的连接费用最省，让你编程计算这个最小的费用。
*输入说明：输入第一行为两个整数n,m（2<=n<=100000，2<=m<=100000），表示计算机总数，和可以互相建立连接的连接个数。
*接下来m行，每行三个整数a,b,c 表示在机器a和机器b之间建立连接的话费是c。
*(题目保证一定存在可行的连通方案, 数据中可能存在权值不一样的重边，但是保证没有自环)
*输出：输出只有一行一个整数，表示最省的总连接费用。
*/


// No.1 Prim

#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

long long ans = 0;
typedef struct node *link;
typedef struct graph *Graph;
struct node{ int v; int wt; link next; };
struct graph{ int V; int E; link* adj; };		//邻接表表示法

Graph graphInit(int v)							// 建图
{
	Graph G = new graph;
	G->V = v;
	G->E = 0;
	G->adj = new link[v + 1];
	for (int i = 1; i <= v; i++)	// 1--n
		G->adj[i] = NULL;
	return G;
}

link NEW(int v, int w, link next)
{
	link x = new node;
	x->v = v;
	x->wt = w;
	x->next = next;
	return x;
}

void graphInsertE(Graph G, int u, int v, int w)		// 无向图添加边, 可能存在权值不一样的重边，选择较短边
{
	bool b = false;
	for (link t = G->adj[u]; t != NULL; t = t->next)
	{
		if (t->v == v)
		{
			if (t->wt > w)
				t->wt = w, b = true;
			break;
		}
	}
	if (b)
	{
		for (link t = G->adj[v]; t != NULL; t = t->next)
		{
			if (t->v == u)
			{
				t->wt = w; break;
			}
		}
	}
	G->adj[u] = NEW(v, w, G->adj[u]);
	G->adj[v] = NEW(u, w, G->adj[v]);
	G->E++;
}

// prim算法 超时 TLE
void MSTprim(Graph g)
{
	vector <int> in;		// 表示在MST中的顶点
	in.push_back(1);		// 从顶点1开始
	for (int i = 1; i < g->V; i++)
	{
		int minlen = INT_MAX;
		int nt;
		for (vector<int>::iterator j = in.begin(); j != in.end(); j++)
		{
			int x = *j;
			for (link t = g->adj[x]; t != NULL; t = t->next)
			{
				if (t->wt < minlen && find(in.begin(), in.end(), t->v) == in.end())
					minlen = t->wt, nt = t->v;
			}
		}
		in.push_back(nt);
		ans += minlen;
	}
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	Graph g = graphInit(n);
	for (int i = 1; i <= m; i++)		// 在VS平台下，建图 56ms。
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		graphInsertE(g, a, b, c);
	}
	MSTprim(g);
	printf("%lld\n", ans);
	return 0;
}


// No.2 Kruskal

#include <cstdio>
#include <algorithm>
using namespace std;
#define SZ 100005
int n, m;
int f[SZ];
long long ans = 0;
struct edge{ int u; int v; int w; }eg[SZ];
int cmp(struct edge a, struct edge b){ return a.w < b.w; }

int fin(int x)
{
	while (f[x] != x)
		x = f[x];
	return f[x];
}

void uni(int a, int b)
{
	int x = fin(a);
	int y = fin(b);
	if (x != y)
		f[x] = y;
}

void MSTkruskal()
{
	int cnt = 0;
	for (int i = 0; i <= n; i++)
		f[i] = i;
	sort(eg + 1, eg + m + 1, cmp);
	for (int i = 1; i <= m; i++)
	{
		if (fin(eg[i].u) == fin(eg[i].v))		// 查找确定是否形成环， 如果形成环，则舍弃这条边
			continue;	
		uni(eg[i].u, eg[i].v);		//合并
		cnt++;
		ans += eg[i].w;
		if (cnt == n - 1)			// 找到 n - 1 条边，即MST
			break;
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &eg[i].u, &eg[i].v, &eg[i].w);	// 不需要考虑重边，因为排序后优先短边，且长边被舍弃
	MSTkruskal();
	printf("%lld\n", ans);
	return 0;
}
