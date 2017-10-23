/*
*问题描述：给定N（小于等于8）个点的地图，以及地图上各点的相邻关系请输出用4种颜色将地图涂色的所有方案数
*（要求相邻两点不能涂成相同的颜色）数据中0代表不相邻，1代表相邻
*输入说明:第一行一个整数n，代表地图上有n个点
*接下来n行，每行n个整数，每个整数是0或者1。第i行第j列的值代表了第i个点和第j个点之间是相邻的还是不相邻，相邻就是1，不相邻就是0.
*保证a[i][j] = a[j][i] （a[i,j] = a[j,i]）
*输出：染色的方案数
*/


#include <iostream>
#include <vector>
using namespace std;
static int N;
static int ans = 0;
static int tmp = 0;
static int map[10][10];
vector <int> lastp;

void input()
{
	cin >> N;
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			cin >> map[i][j];
	}
}

bool iscolor(int s, int i, vector <int> &color)		//是否可以把s顶点染i色
{
	for (int k = 0; k < N; k++)
	{
		if (map[s][k] == 1)
		{
			if (color[k] == i)
				return 0;
		}
	}
	return 1;
}

bool isend(vector<int>::iterator s, vector<int> &color)
{
	for (size_t i = 0; i < lastp.size(); i++)
	{
		if (color[lastp[i]] == 0)
			return 0;
	}
	if (s == lastp.end())
		return 1;
	else
		return 0;
}

void dfs(int s, vector <int> &mark)		//s连通分支的所有点
{
	lastp.push_back(s);
	mark[s] = 1;
	for (int i = 0; i < N; i++)
	{
		if (map[s][i] == 1 && mark[i] == 0)
		{
			dfs(i, mark);
		}
	}
}

void solve(vector<int>::iterator a, vector <int> &color)
{
	if (isend(a, color))
	{
		tmp++;
		return;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (iscolor(*a, i, color))
		{
			color[*a] = i;
			solve(a + 1, color);
			color[*a] = 0;
		}
	}
}

int main()
{
	input();
	vector <int> color(N, 0);		// 0 没经过  1, 2, 3, 4 染色
	vector <int> mark(N, 0);		//标记每个连通分支的点
	for (int i = 0; i < N; i++)
	{
		if (mark[i] == 0)
		{
			dfs(i, mark);				//求连通分支的点
			solve(lastp.begin(), color);
			if (ans == 0)
				ans = tmp;
			else
				ans *= tmp;
			tmp = 0;
			lastp.clear();
		}
	}
	cout << ans;
	return 0;
}
