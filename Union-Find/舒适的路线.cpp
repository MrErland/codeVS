/*
*问题描述：城市Z有N(1<N≤500)个景点（编号为1,2,3,…,N），这些景点被M（0<M≤5000）条道路连接着，所有道路都是双向的，两个景点之间可能有多条道路。
*Z小镇有个奇怪的规定，就是对于一条给定的公路Ri，任何在该公路上行驶的车辆速度必须为Vi。
*游客从一个景点前往另一个景点的时候，都希望选择行使过程中最大速度和最小速度的比尽可能小的路线，也就是所谓最舒适的路线。
*输入说明：第一行包含两个正整数，N和M。接下来的M行每行包含三个正整数：x，y和v
*（1≤x,y≤N，0 最后一行包含两个正整数s，t，表示想知道从景点s到景点t最大最小速度比最小的路径。s和t不可能相同。
*输出：如果景点s到景点t没有路径，输出“IMPOSSIBLE”。否则输出一个数，表示最小的速度比。如果需要，输出一个既约分数。
*/


/*
把边权按从大到小的顺序排好序枚举每一条边，接下来从这条边开始按顺序（从大到小）枚举每一条比它小的边，并且把这条边的两端点划分到一个联通块中，并且判断起点和终点是否在同一个联通块中，如果在同一个联通块中，根据当前枚举到的边的权值，更新最优解。
原理：枚举、贪心，因为我们要求ans_max与ans_min的最小比值，ans_max与ans_min越接近肯定是越好的。所以我们枚举ans_max，这样就可以把ans_max当成常数，那么ans_min的值一定是越大越好（当然，它不可能大过ans_max）
所以我们从当前枚举到的边开始，每次加一条略小的边进入，当S与T第一次联通时，ans_min的值是最大的，那么就能保证他们的比值是当前ans_max下最小的。
*/

#include<cstdio>
#include<algorithm>
using namespace std;
const int SZ = 5002;
const int INF = 1 << 30;
struct Road{ int s; int t; int v; }road[SZ];
int root[502];
int N, M;
int S, T;

int gcd(int a, int b)		
{
	int t;
	while (b != 0)
	{
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int cmp(struct Road a, struct Road b)			//降序排列
{
	if (a.v > b.v)
		return 1;
	return 0;
}

void input()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++)
		scanf("%d %d %d", &road[i].s, &road[i].t, &road[i].v);
	sort(&road[1], &road[1 + M], cmp);
	scanf("%d %d", &S, &T);
}

int find(int x)
{
	while (root[x] != x)
		x = root[x];
	return x;
}

void merg(int i, int j)
{
	int a = find(i);
	int b = find(j);
	if (a == b)
		return;
	root[i] = root[j];			//使用同一个父节点，减少树的高度，提高一点效率
}

void work()
{
	int i, j;
	int ma = INF;
	int mi = 1;
	for (i = 1; i <= M; i++)
	{
		for (j = 0; j <= M; j++)
			root[j] = j;
		for (j = i; j <= M; j++)
		{
			merg(road[j].s, road[j].t);
			if (find(S) == find(T))
			{
				if (ma * 1.0 / mi > road[i].v * 1.0 / road[j].v)
				{
					ma = road[i].v;
					mi = road[j].v;
				}
				break;
			}
		}
	}
	int r = gcd(ma, mi);
	ma /= r;
	mi /= r;
	if (ma == INF && mi == 1)
		printf("IMPOSSIBLE");
	else if (mi != 1)
		printf("%d/%d", ma, mi);
	else
		printf("%d", ma);
}

int main()
{
	input();
	work();
	return 0;
}
