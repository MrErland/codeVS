/*
*问题描述： Ural大学有N个职员，编号为1~N。他们有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。
*每个职员有一个快乐指数。现在有个周年庆宴会，要求与会职员的快乐指数最大。但是，没有职员愿和直接上司一起与会。
*输入说明：第一行一个整数N。(1<=N<=6000)
*接下来N行，第i+1行表示i号职员的快乐指数Ri。(-128<=Ri<=127)
*接下来N-1行，每行输入一对整数L,K。表示K是L的直接上司。
*最后一行输入0,0。
*输出：输出最大的快乐指数。
*/


#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define SZ 6005
int N, happy[SZ];
int root;
vector <int> emp[SZ];	// 保存其直接下属
int dp[SZ][2];		//dp[i][0] 表示i没参加舞会的最大欢乐度  dp[i][1]表示参加舞会的最大欢乐度

void dfs(int root)
{
	if (!emp[root].size())		//没有直接下属
	{
		dp[root][0] = 0;
		dp[root][1] = happy[root];
		return;
	}
	for (unsigned i = 0; i < emp[root].size(); i++)
		dfs(emp[root][i]);

	int n = 0, m = 0;
	for (unsigned i = 0; i < emp[root].size(); i++)
	{
		n += max(dp[emp[root][i]][1], dp[emp[root][i]][0]);		//root不参加
		m += dp[emp[root][i]][0];					//root参加
	}
	dp[root][0] = n;
	dp[root][1] = m + happy[root];
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &happy[i]);
	int t[SZ] = { 0 };
	for (int i = 1; i < N; i++)		//保存每个boss的直接下属
	{
		int a, b;
		scanf("%d%d", &a, &b);
		emp[b].push_back(a);
		t[a] = 1;
	}
	for (int i = 1; i <= N; i++)		//找到根节点
	{
		if (!t[i])
		{
			root = i; break;
		}
	}
	dfs(root);
	printf("%d\n", max(dp[root][0], dp[root][1]));
	return 0;
}
