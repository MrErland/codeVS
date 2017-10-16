/*
*问题描述：将整数n分成k份，且每份不能为空，任意两种划分方案不能相同(不考虑顺序)。
*例如：n=7，k=3，下面三种划分方案被认为是相同的。1 1 5、1 5 1、5 1 1
*输入说明：n，k (6<n<=200，2<=k<=6)
*输出：一个整数，即不同的分法
*/


#include <iostream>
using namespace std;
static int dp[201][10];

int main()
{
	int n, k;
	cin >> n >> k;
	dp[0][0] = 1;
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= k; j++)
		{
			if (i >= j) 
        dp[i][j] = dp[i - j][j] + dp[i - 1][j - 1];
		}
	}
	cout << dp[n][k];
	return 0;
}
