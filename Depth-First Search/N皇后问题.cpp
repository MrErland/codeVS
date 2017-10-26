
/*
*问题描述：在n×n格的棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
*n后问题等价于再n×n的棋盘上放置n个皇后，任何2个皇后不妨在同一行或同一列或同一斜线上。
*输入说明：给定棋盘的大小n (n ≤ 13)
*输出：输出整数表示有多少种放置方法
*/


#include <cstdio>
#include <cstring>
using namespace std;
static int n;
static int ans = 0;
static int mark[13];		//降维,表示每列放置皇后的行号

bool issafe(int r, int c)
{
	for (int j = 0; j < n; j++)
	{
		if (mark[j] != -1)
		{
			if (r - mark[j] == c - j || r - mark[j] == j - c || c == j)
				return 0;
		}
	}
	return 1;
}

void dfs(int r)
{
	if (r == n - 1)
	{
		ans++;
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (issafe(r + 1, i))
		{
			mark[i] = r + 1;
			dfs(r + 1);
			mark[i] = -1;
		}
	}
}

int main()
{
	memset(mark, -1, sizeof(mark));
	scanf("%d", &n);
	dfs(-1);
	printf("%d", ans);
	return 0;
}
