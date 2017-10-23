/*
*问题描述：给出一个n, 请输出n的所有全排列
*输入：读入仅一个整数n   (1<=n<=10)
*输出：一共n!行，每行n个用空格隔开的数，表示n的一个全排列。并且按全排列的字典序输出。
*/


#include <cstdio>  
#include <cstring>  
using namespace std;
static int N;
static int mark[11];
static int parr[11];

void dfs(int cur)
{
	if (cur == N + 1)
	{
		for (int i = 1; i <= N; i++)
		{
			printf("%d ", parr[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 1; i <= N; i++)
	{
		if (mark[i])
			continue;
		parr[cur] = i;
		mark[i] = 1;
		dfs(cur + 1);
		mark[i] = 0;
	}
}

int main()
{
	memset(mark, 0, sizeof(mark));
	memset(parr, 0, sizeof(parr));
	scanf("%d", &N);
	dfs(1);
	return 0;
}
