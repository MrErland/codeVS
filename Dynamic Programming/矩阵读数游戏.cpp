/*
*问题描述:帅帅经常跟同学玩一个矩阵取数游戏：对于一个给定的n*m的矩阵，矩阵中的每个元素aij均为非负整数。游戏规则如下：
*1. 每次取数时须从每行各取走一个元素，共n个。m次后取完矩阵所有元素；
*2. 每次取走的各个元素只能是该元素所在行的行首或行尾；
*3. 每次取数都有一个得分值，为每行取数的得分之和，每行取数的得分=被取走的元素值*2^i，其中i表示第i次取数(从1开始编号)
*4. 游戏结束总得分为m次取数得分之和。
*请你帮忙写一个程序，对于任意矩阵，可以求出取数后的最大得分。
*输入说明:第1行为两个用空格隔开的整数n和m。第2~n+1行为n*m矩阵，其中每行有m个用单个空格隔开的非负整数。
*/


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 85;
const int maxm = 85;
const int maxl = 30;		    	  //结果最大位数 5 * 29
int a[maxm];		
int dp[maxn][maxm][maxl];
int pw[maxn][maxl];
int ans[maxl];
int t[maxl];

void Multi(int *x, int *y, int z)		//高精度乘法 y*z保存到x
{
	memset(t, 0, sizeof(t));
	t[0] = y[0];
	for (int i = 1; i <= t[0]; i++)
	{
		t[i] = y[i] * z;
	}
	for (int i = 1; i <= t[0]; i++)
	{
		t[i + 1] += t[i] / 100000;
		t[i] %= 100000;
	}
	while (t[t[0] + 1])
	{
		t[0]++;
		t[t[0] + 1] += t[t[0]] / 100000;
		t[t[0]] %= 100000;
	}
	for (int i = 0; i < maxl; i++)
		x[i] = t[i];
	return;
}
void Add(int *x, int *y, int *z)		  //高精度加法 y+z保存到 x
{
	int i;
	memset(t, 0, sizeof(t));
	if (y[0] > z[0])
		t[0] = y[0];
	else 
		t[0] = z[0];
	for (i = 1; i <= t[0]; i++)
	{
		t[i] = y[i] + z[i];
	}
	for (i = 1; i <= t[0]; i++)
	{
		t[i + 1] += t[i] / 100000;
		t[i] %= 100000;
	}
	if (t[t[0] + 1])	  //进位
		t[0]++;
	for (i = 0; i < maxl; i++)
		x[i] = t[i];
	return;
}
bool Max(int *x, int *y)	  	// x > y ?
{
	if (x[0] > y[0])
		return 1;
	else if (y[0] > x[0])
		return 0;
	else
	{
		for (int i = x[0]; i >= 1; i--)
		{
			if (x[i] > y[i])
				return 1;
			else if (x[i] < y[i])
				return 0;
		}
	}
	return 1;
}

int main()
{
	int N, M;
	int i, j, len, x, y;
	cin >> N >> M;
	pw[0][0] = 1;	//保存2的幂
	pw[0][1] = 1;
	for (int i = 1; i <= M; i++)
		Multi(pw[i], pw[i - 1], 2);
	ans[0] = 1;		//初始化结果,长度是1,初始为0
	ans[1] = 0;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)		//处理一行 -> a[]
		{
			cin >> a[j];							
			Multi(dp[j][j], pw[M], a[j]);
		}
		for (len = 1; len < M; len++)			
		{
			for (x = 1; x <= M - len; x++)		//起點
			{
				y = x + len;				//終點
				int xm[maxl], ym[maxl], cm[maxl];
				Multi(cm, pw[M - len], a[x]);
				Add(xm, cm, dp[x + 1][y]);
				Multi(cm, pw[M - len], a[y]);
				Add(ym, cm, dp[x][y - 1]);
				if (Max(xm, ym))			
					memcpy(dp[x][y], xm, sizeof(int)* maxl);
				else
					memcpy(dp[x][y], ym, sizeof(int)* maxl);
			}
		}
		Add(ans, ans, dp[1][M]);
	}
	cout << ans[ans[0]];					//首位 不用補0
	for (i = ans[0] - 1; i >= 1; i--)			//逆序輸出結果 空位補0
		cout << setfill('0') << setw(5) << ans[i];
	return 0;
}
