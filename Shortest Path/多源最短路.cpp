
/*
*问题描述：已知n个点(n<=100)，给你n*n的方阵，a[i,j]表示从第i个点到第j个点的直接距离。
*现在有Q个询问，每个询问两个正整数，a和b，让你求a到b之间的最短路程。满足a[i,j]=a[j,i];
*输入说明：第一行一个正整数n，接下来n行每行n个正整数，满足a[i,i]=0,再一行一个Q，接下来Q行，每行两个正整数a和b。
*输出：一共Q行，每行一个整数。
*/

#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 99999999;
int graph[100][100];
int goal[5000][2];
int N;
int Q;


void input()
{
	memset(graph, INF, sizeof(graph));		// INF 表示不连通
	memset(goal, 0, sizeof(goal));
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &graph[i][j]);
		}
	}
	scanf("%d", &Q);
	int m, n;
	for (int i = 0; i < Q; i++)
	{
		scanf("%d %d", &m, &n);
		goal[i][0] = m - 1;
		goal[i][1] = n - 1;
	}
}

void flyod()
{
	int i, j, k;
	for (k = 0; k < N; k++)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (graph[i][j] > graph[i][k] + graph[k][j] && graph[i][k] != INF && graph[k][j] != INF)
				{
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
	}
}

void output()
{
	for (int i = 0; i < Q; i++)
	{
		printf("%d\n", graph[goal[i][0]][goal[i][1]]);
	}
}

int main()
{
	input();
	flyod();
	output();
	return 0;
}
