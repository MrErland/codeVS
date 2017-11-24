/*
*问题描述：有n个砝码，现在要称一个质量为m的物体，最少需要挑出几个砝码，注意，一个砝码最多只能挑一次。
*输入说明：第一行两个整数n和m，接下来n行每行一个整数表示每个砝码的重量。
*输出：输出选择的砝码的总数k，使得k尽量的小。
*/



// 采用排序和dfs的思想求解，效率不稳定，出现超时，加入后缀和优化
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, cnt = 30;
int sto[32];
long aft[32];
bool book[32] = { 0 };

void work(int wt, int i, int cn)
{
	if (wt >= m)
	{
		if (wt == m && cn < cnt)				//记录最优解
		{
			cnt = cn;
		}
		return;
	}
	for (int j = i + 1; j < n; j++)
	{
		if (wt + aft[j] < m)
			return;
		if (sto[j] + wt <= m && !book[j])
		{
			book[j] = 1;
			work(sto[j] + wt, j, cn + 1);
			book[j] = 0;
		}
	}
}

int cmp(int a, int b){ return a > b; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", &sto[i]);
	sort(sto, sto + n, cmp);				//从大到小排序，优先搜索的思想
	for (int i = n - 1; i >= 0; i--)		//后缀和优化
		aft[i] = aft[i + 1] + sto[i];
	for (int i = 0; i < n; i++)
	{
		if (sto[i] <= m)
		{
			book[i] = 1;
			work(sto[i], i, 1);
			book[i] = 0;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
