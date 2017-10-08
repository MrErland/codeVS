/*
*问题描述：有n堆石子排成一列，每堆石子有一个重量w[i], 每次合并可以合并相邻的两堆石子，一次合并的代价为两堆石子的重量和w[i]+w[i+1]。
*问安排怎样的合并顺序，能够使得总合并代价达到最小。
*输入描述：第一行一个整数n（n<=100）第二行n个整数w1,w2...wn  (wi <= 100)
*输出：一个整数表示最小合并代价。
*/

/***递推法***/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 0xffffff;
static int dp[100][100];

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


/***记忆化搜索***/
