/*
*给一个数组a1,a2 ... an,找到最长的上升降子序列ab1<ab2< .. <abk,其中b1<b2<..bk.
*输出长度即可.
*第一行,一个整数N.
*第二行,N个整数(N < = 5000)
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector <int> arr(n);
	vector <int> dp(n, 1);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i] < arr[j])
				dp[i] = max(dp[i], dp[j] + 1);
		}
	}
	sort(dp.begin(), dp.end());
	cout << dp[n - 1];
	return 0;
}
