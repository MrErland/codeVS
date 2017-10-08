/*
*问题描述:帅帅经常跟同学玩一个矩阵取数游戏：对于一个给定的n*m 的矩阵，矩阵中的每个元素aij均为非负整数。游戏规则如下：
*1. 每次取数时须从每行各取走一个元素，共n个。m次后取完矩阵所有元素；
*2. 每次取走的各个元素只能是该元素所在行的行首或行尾；
*3. 每次取数都有一个得分值，为每行取数的得分之和，每行取数的得分= 被取走的元素值*2i，其中i 表示第i 次取数（从1 开始编号）；
*4. 游戏结束总得分为m次取数得分之和。
*请你帮忙写一个程序，对于任意矩阵，可以求出取数后的最大得分。
*输入说明:第1行为两个用空格隔开的整数n和m。第2~n+1 行为n*m矩阵，其中每行有m个用单个空格隔开的非负整数。
*/


#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

int getless(vector<int> &a)
{
	int x;
	if (!a.empty())
	{
		if (a[0] < a[a.size() - 1])
		{
			x = a[0];
			a.erase(a.begin(), a.begin() + 1);
		}
		else{
			x = a[a.size() - 1];
			a.erase(a.end() - 1, a.end());
		}
		return x;
	}
	else
		exit(-1);
}

int main()
{
	int n, m;
	cin >> n >> m;
	int temp;
	vector<vector<int> > arr(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> temp;
			arr[i].push_back(temp);
		}
	}
	unsigned long int res = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j < n; j++)
			res += getless(arr[j])*pow(2, i);
	}
	cout << res;
	return 0;
}
