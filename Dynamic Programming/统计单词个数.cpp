/*
*问题描述：给出一个长度不超过200的由小写英文字母组成的字母串(约定;该字串以每行20个字母的方式输入，且保证每行一定为20个)。
*要求将此字母串分成k份(1<=k<=40)，且每份中包含的单词个数加起来总数最大(每份中包含的单词可以部分重叠。当选用一个单词之后，其第一个字母不能再用。
*例如字符串this中可包含this和is，选用this之后就不能包含th)（管理员注：这里的不能再用指的是位置，不是字母本身。比如thisis可以算做包含2个is）。
*单词在给出的一个不超过6个单词的字典中。要求输出最大的个数。
*输入说明：第一行为一个正整数(0<n<=5)表示有n组测试数据
*每组的第一行有二个正整数(p，k),p表示字串的行数;k表示分为k个部分。
*接下来的p行，每行均有20个字符。
*再接下来有一个正整数s，表示字典中单词个数。(1<=s<=6)
*接下来的s行，每行均有一个单词。
*输出：每行一个整数，分别对应每组测试数据的相应结果。
*/


#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int check[201][201], dp[201][41];

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int p, k, d;
		memset(check, 0, sizeof(check));
		memset(dp, 0, sizeof(dp));
		cin >> p >> k;
		string s, t, word[7];
		s = "";
		while (p--)
		{
			cin >> t;
			s += t;
		}
		cin >> d;
		for (int i = 1; i <= d; i++)
			cin >> word[i];
		int i, j;
		for (j = s.size() - 1; j >= 0; j--)
		{
			for (i = j; i >= 0; i--)
			{
				bool f = false;
				for (int k = 1; k <= d; k++)
				{
					if (s.find(word[k], i) == i && word[k].size() <= j - i + 1)
					{
						f = true;
						break;
					}
				}
				if (f)
					check[i][j] = check[i + 1][j] + 1;
				else
					check[i][j] = check[i + 1][j];
			}
		}
		for ( i = 0; i < s.size(); i++)
			dp[i][1] = check[0][i];
		for (j = 2; j <= k; j++)
		{
			for (i = j - 1; i < s.size(); i++)
			{
				for (int t = i - 1; t >= j - 1; t--)
					dp[i][j] = max(dp[i][j], dp[t][j - 1] + check[t + 1][i]);
			}
		}
		cout << dp[s.size() - 1][k] << endl;
	}
	return 0;
}
