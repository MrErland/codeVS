/*
*问题描述：如图所示的数字三角形，从顶部出发，在每一结点可以选择向左走或得向右走，一直走到底层，要求找出一条路径，使路径上的值最大。
*输入说明：第一行是数塔层数N(1<=N<=100)。第二行起，按数塔图形，有一个或多个的整数，表示该层节点的值，共有N行。
*输出：输出最大值
*/



#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100;
static int dp[N];
static int a[N];
static int b[N];

int main()
{
	int n;
	cin >> n;
	int i, j;
	cin >> a[0];
	dp[0] = a[0];
	for (i = 2; i <= n; i++)
	{
		for (j = 0; j < i; j++)             //分行从上到下处理
			cin >> b[j];
		for (j = 0; j < i; j++)
		{
			if (j > 0 && j < i - 1)
				dp[j] = max(a[j - 1], a[j]) + b[j];
			else if (j == 0)
				dp[j] = a[j] + b[j];
			else
				dp[j] = a[j - 1] + b[j];
		}
		for (j = 0; j < i; j++)
			a[j] = dp[j];
	}
	int ans = -0xffffff;
	for (i = 0; i < n; i++)
	{
		if (dp[i] > ans)
			ans = dp[i];
	}
	cout << ans;
	return 0;
}
