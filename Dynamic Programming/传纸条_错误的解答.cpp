/*
*问题描述：一次素质拓展活动中，班上同学安排做成一个m行n列的矩阵，而小渊和小轩被安排在矩阵对角线的两端，因此，他们就无法直接交谈了。幸运的是，他们可以通过传纸条来进行交流。
*纸条要经由许多同学传到对方手里，小渊坐在矩阵的左上角，坐标(1,1)，小轩坐在矩阵的右下角，坐标(m,n)。
*从小渊传到小轩的纸条只可以向下或者向右传递，从小轩传给小渊的纸条只可以向上或者向左传递。
*在活动进行中，小渊希望给小轩传递一张纸条，同时希望小轩给他回复。
*班里每个同学都可以帮他们传递，但只会帮他们一次，也就是说如果此人在小渊递给小轩纸条的时候帮忙，那么在小轩递给小渊的时候就不会再帮忙。反之亦然。
*还有一件事情需要注意，全班每个同学愿意帮忙的好感度有高有低（注意：小渊和小轩的好心程度没有定义，输入时用0表示），可以用一个0-100的自然数来表示，数越大表示越好心。
*小渊和小轩希望尽可能找好心程度高的同学来帮忙传纸条，即找到来回两条传递路径，使得这两条路径上同学的好心程度只和最大。现在，请你帮助小渊和小轩找到这样的两条路径。
*输入描述：输入的第一行有2个用空格隔开的整数m和n，表示班里有m行n列（1<=m,n<=50）。
*接下来的m行是一个m*n的矩阵，矩阵中第i行j列的整数表示坐在第i行j列的学生的好心程度。每行的n个整数之间用空格隔开。
*输出：输出一个整数，表示来回两条路上参与传递纸条的学生的好心程度之和的最大值。
*/


/*
采用贪心的策略，第一次先找最大的路，标记已经走过的点，第二次找剩下最大路。
错误：1、会产生封闭的情况，没有第二条路；2、结果未必最优。
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 51;
static int a[N][N];
static int dp[N][N];
struct road{ int x; int y; };
static struct road path[N][N];		//保存发出去的最优路径
static int mark[N][N];

int main()
{
	int m, n;
	cin >> m >> n;
	int i, j;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cin >> a[i][j];
		}
	}
	int t1, t2, ans = 0;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			t1 = t2 = 0;
			if (i - 1 >= 1)
				t1 = dp[i - 1][j];
			if (j - 1 >= 1)
				t2 = dp[i][j - 1];
			if (t1 > t2)
			{
				dp[i][j] = t1 + a[i][j];
				path[i][j].x = i - 1;		//（i，j）点前一个的最优点
				path[i][j].y = j;
			}
			else{
				dp[i][j] = t2 + a[i][j];
				path[i][j].x = i;
				path[i][j].y = j - 1;
			}
		}
	}
	ans += dp[m][n];					//发出去最大好感度
	memset(dp, 0, sizeof(dp));
	i = m;
	j = n;
	int s, t;
	while (path[i][j].x != 1 || path[i][j].y != 1)		//标记已经走过的点
	{
		s = i; t = j;
		i = path[s][t].x;
		j = path[s][t].y;
		mark[i][j] = 1;
	}
	for (i = m; i >= 1; i--)
	{
		for (j = n; j >= 1; j--)
		{
			if (mark[i][j])				//已经走过
				continue;
			t1 = t2 = 0;
			if (i + 1 <= m && !mark[i + 1][j])
				t1 = dp[i + 1][j];
			if (j + 1 <= n && !mark[i][j + 1])
				t2 = dp[i][j + 1];
			if (t1 > t2 && t1 > 0)
			{
				dp[i][j] = t1 + a[i][j];
			}
			else if(t1 > 0){
				dp[i][j] = t2 + a[i][j];
			}
		}
	}
	ans += dp[1][1];
	cout << ans;
	return 0;
}
