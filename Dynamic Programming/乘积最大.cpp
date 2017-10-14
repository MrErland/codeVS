/*
*问题描述：设有一个长度为N的数字串，要求选手使用K个乘号将它分成K+1个部分，找出一种分法，使得这K+1个部分的乘积能够为最大。
*输入说明： 第一行共有2个自然数N，K(6≤N≤40，1≤K≤6),第二行是一个长度为N的数字串。
*输出：输出所求得的最大乘积（一个自然数）
*/


#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 41;

int main()
{
	int n, k;
	cin >> n >> k;
	string a;
	cin >> a;
	int mul[N][N];
	int dp[N][N];			
	memset(mul, 0, sizeof(mul));
	memset(dp, 0, sizeof(dp));
	int i, j;
	for (i = 0; i < n; i++)				//初始化mul
	{
		for (j = i + 1; j <= n; j++)
		{
			mul[i + 1][j] = stoi(string(a, i, j - i), 0, 10);
		}
	}
	for (i = 1; i <= n; i++)		//初始化dp[][0]
	{
		dp[i][0] = mul[1][i];
	}
	int len;
	for (len = 1; len <= k; len++)		//乘号个数
	{
		for (i = len + 1; i <= n; i++)	//len个乘号时，前i个数字的最大值
		{
			for (j = len; j <= i; j++)
				dp[i][len] = max(dp[i][len], dp[j][len - 1] * mul[j + 1][i]);
		}
	}
	cout << dp[n][k];
	return 0;
}
