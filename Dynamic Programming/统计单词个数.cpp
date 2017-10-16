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



#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int getmatch(const string &s, vector <string> &v)
{
	int ret = 0;
	size_t i, j, k, t;
	for (i = 0; i < s.size(); i++)
	{
		for (j = 1; j < v.size(); j++)
		{
			t = i;
			for (k = 0; s[t] == v[j][k] && k <= v[j].size() - 1; k++, t++)
				;
			if (k == v[j].size())
			{
				ret++;
				break;
			}
		}
	}
	return ret;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		size_t p, k;
		cin >> p >> k;
		string ins, ts;
		for (size_t j = 1; j <= p; j++)
		{
			cin >> ts;
			ins += ts;
		}
		int s;
		cin >> s;
		vector <string> word(s + 1);
		for (int j = 1; j <= s; j++)
			cin >> word[j];
		int dp[201][41];								//前i个字符，分成k段
		int a[201][201];
		memset(dp, 0, sizeof(dp));
		memset(a, 0, sizeof(a));
		if (k == 1)
		{
			for (size_t j = 0; j < ins.size(); j++)
				dp[j + 1][1] = getmatch(string(ins, 0, j + 1), word);	
			cout << dp[ins.size()][k] << endl;
			continue;
		}
		for (size_t j = 0; j < ins.size(); j++)
		{
			for (size_t k = j; k < ins.size(); k++)
			{
				a[j + 1][k + 1] = getmatch(string(ins, j, k - j + 1), word);	//初始化
			}
		}

		for (size_t j = 0; j < ins.size(); j++)
		{
			for (size_t sz = 2; sz <= k && sz <= j; sz++)
			{
				for (size_t st = 0; st < j; st++)
				{
					dp[j + 1][sz] = max(dp[j + 1][sz], dp[st + 1][sz - 1] + a[st + 1][j + 1]);
				}
			}
		}
		cout << dp[ins.size()][k] << endl;
	}
	return 0;
}
