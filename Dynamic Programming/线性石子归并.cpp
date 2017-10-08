/*
*问题描述：有n堆石子排成一列，每堆石子有一个重量w[i], 每次合并可以合并相邻的两堆石子，一次合并的代价为两堆石子的重量和w[i]+w[i+1]。
*问安排怎样的合并顺序，能够使得总合并代价达到最小。
*输入描述：第一行一个整数n（n<=100）第二行n个整数w1,w2...wn  (wi <= 100)
*输出：一个整数表示最小合并代价。
*/

/***自底向上递推法***/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 0xffffff;
const int N = 200;
static int dp[N][N];

int main()
{
	int n, i;
	cin >> n;
	vector<int> arr(n + 1);
	vector<int> sum(n + 1, 0);
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
		sum[i] = sum[i - 1] + arr[i];
	}
	int j, len, k, res;
	for (len = 1; len <= n; len++)         		 //递推一次合并的长度
	{
		for (i = 1; i <= n - len; i++)        	 //起点
		{
			res = INF;
			j = i + len;         		//终点
			for (k = i; k < j; k++)
				res = min(res, dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
			dp[i][j] = res;           	//保存起点到终点最短的权值
		}
	}
	cout << dp[1][n];
	return 0;
}


/***自顶向下搜索法***/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0xffffff;
const int N = 200;
static int dp[N][N];

int solve(int l, int r, vector<int> &sum)
{
	if (dp[l][r] != -1)
		return dp[l][r];
	int res = INF;
	for (int i = l; i < r; i++)
		res = min(res, solve(l, i, sum) + solve(i + 1, r, sum) + sum[r] - sum[l - 1]);
	return dp[l][r] = res;
}

int main()
{
	int n, i;
	cin >> n;
	vector<int> arr(n + 1);
	vector<int> sum(n + 1, 0);
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
		sum[i] = sum[i - 1] + arr[i];
	}
	memset(dp, -1, sizeof(dp));
	for (i = 0; i <= n; i++)
		dp[i][i] = 0;
	cout << solve(1, n, sum);
	return 0;
}
