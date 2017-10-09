/*
*问题描述：A 点有一个过河卒，需要走到目标 B 点。卒行走规则：可以向下、或者向右。
*同时在棋盘上的任一点有一个对方的马（如上图的C点），该马所在的点和所有跳跃一步可达的点称为对方马的控制点。
*例如上图 C 点上的马可以控制 9 个点（图中的P1，P2 … P8 和 C）。卒不能通过对方马的控制点。
*棋盘用坐标表示，A 点（0，0）、B 点（n,m）(n,m 为不超过 20 的整数，并由键盘输入)，同样马的位置坐标是需要给出的（约定: C不等于A，同时C不等于B）。
*现在要求你计算出卒从 A 点能够到达 B 点的路径的条数。1<=n,m<=15
*输入描述：B点的坐标（n,m）以及对方马的坐标（X,Y）{不用判错}
*输出：一个整数（路径的条数）
*/


#include <iostream>
using namespace std;
static const int N = 20;
static int mark[N][N];
static int dp[N][N];
static int bx, by;
static int cx, cy;

void subC()					                    //标记无法经过的点
{
	mark[cx][cy] = 1;
	if (cx + 2 <= bx)
	{
		if (cx - 2 >= 0)
		{
			if (cy + 2 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx + 1][cy - 2] = 1;
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 1][cy + 2] = 1;
					mark[cx - 1][cy - 2] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 1][cy + 2] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}

			}
			else if (cy + 1 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy - 2] = 1;
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 1][cy - 2] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
			}
		}
		else if (cx - 1 >= 0)
		{
			if (cy + 2 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx + 1][cy - 2] = 1;
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 1][cy + 2] = 1;
					mark[cx - 1][cy - 2] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 1][cy + 2] = 1;
				}

			}
			else if (cy + 1 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy - 2] = 1;
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
					mark[cx - 1][cy - 2] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx + 2][cy + 1] = 1;
					mark[cx + 2][cy - 1] = 1;
				}
			}
		}

	}
	else if (cx + 1 <= bx)
	{
		if (cx - 2 >= 0)
		{
			if (cy + 2 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx + 1][cy - 2] = 1;
					mark[cx - 1][cy + 2] = 1;
					mark[cx - 1][cy - 2] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx - 1][cy + 2] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
			}
			else if (cy + 1 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy - 2] = 1;
					mark[cx - 1][cy - 2] = 1;
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx - 2][cy - 1] = 1;
					mark[cx - 2][cy + 1] = 1;
				}
			}
		}
		else if (cx - 1 >= 0)
		{
			if (cy + 2 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx + 1][cy - 2] = 1;
					mark[cx - 1][cy + 2] = 1;
					mark[cx - 1][cy - 2] = 1;
				}
				else if (cy - 1 >= 0)
				{
					mark[cx + 1][cy + 2] = 1;
					mark[cx - 1][cy + 2] = 1;
				}

			}
			else if (cy + 1 <= by)
			{
				if (cy - 2 >= 0)
				{
					mark[cx + 1][cy - 2] = 1;
					mark[cx - 1][cy - 2] = 1;
				}
			}
		}
	}
}

int main()
{
	cin >> bx >> by;
	cin >> cx >> cy;
	subC();
	int i, j;
	dp[0][0] = 1;
	for (i = 0; i <= bx; i++)
	{
		for (j = 0; j <= by; j++)
		{
			if (!mark[i][j])
			{
				if (i - 1 >= 0)
					dp[i][j] += dp[i - 1][j];
				if (j - 1 >= 0)
					dp[i][j] += dp[i][j - 1];
			}
		}
	}
	cout << dp[bx][by];
	return 0;
}
