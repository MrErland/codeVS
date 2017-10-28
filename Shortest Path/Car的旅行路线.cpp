/*
*问题描述：又到暑假了，住在城市A的Car想和朋友一起去城市B旅游。她知道每个城市都有四个飞机场，分别位于一个矩形的四个顶点上
*同一个城市中两个机场之间有一条笔直的高速铁路，第I个城市中高速铁路了的单位里程价格为Ti，任意两个不同城市的机场之间均有航线，所有航线单位里程的价格均为t。
*找出一条从城市A到B的旅游路线，出发和到达城市中的机场可以任意选取，要求总的花费最少。
*输入说明：第一行为一个正整数n(0<=n<=10)，表示有n组测试数据。每组的第一行有四个正整数s，t，A，B。
*S(0<S<=100)表示城市的个数，t表示飞机单位里程的价格，A，B分别为城市A，B的序号，(1<=A，B<=S)。
*接下来有S行，其中第I行均有7个正整数xi1，yi1，xi2，yi2，xi3，yi3，Ti
*这当中的(xi1，yi1)，(xi2，yi2)，(xi3，yi3)分别是第I个城市中任意三个机场的坐标，T I为第I个城市高速铁路单位里程的价格。
*输出：共有n行，每行一个数据对应测试数据。
*/


#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int S, T, A, B;
int plane[100][4][2];
double graph[400][400] = { 0 };
const int INF = 99999999;

void input()
{
	cin >> S >> T >> A >> B;
	int x1, y1, x2, y2, x3, y3, t, x4, y4;
	double a, b, c;
	for (int i = 0; i < S; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> t;
		a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		b = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
		c = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
		graph[i * 4][i * 4 + 1] = a*t;
		graph[i * 4 + 1][i * 4] = a*t;
		graph[i * 4 + 1][i * 4 + 2] = b*t;
		graph[i * 4 + 2][i * 4 + 1] = b*t;
		graph[i * 4 + 2][i * 4] = c*t;
		graph[i * 4][i * 4 + 2] = c*t;
		double m = max(a > b ? a : b, c);
		if (m == a)
		{
			x4 = x1 + x2 - x3;
			y4 = y1 + y2 - y3;
		}
		else if (m == b)
		{
			x4 = x2 + x3 - x1;
			y4 = y2 + y3 - y1;
		}
		else{
			x4 = x1 + x3 - x2;
			y4 = y1 + y3 - y2;
		}
		a = sqrt(pow(x4 - x1, 2) + pow(y4 - y1, 2));
		b = sqrt(pow(x4 - x2, 2) + pow(y4 - y2, 2));
		c = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
		graph[i * 4][i * 4 + 3] = a*t;
		graph[i * 4 + 3][i * 4] = a*t;
		graph[i * 4 + 1][i * 4 + 3] = b*t;
		graph[i * 4 + 3][i * 4 + 1] = b*t;
		graph[i * 4 + 2][i * 4 + 3] = c*t;
		graph[i * 4 + 3][i * 4 + 2] = c*t;

		plane[i][0][0] = x1;
		plane[i][0][1] = y1;
		plane[i][1][0] = x2;
		plane[i][1][1] = y2;
		plane[i][2][0] = x3;
		plane[i][2][1] = y3;
		plane[i][3][0] = x4;
		plane[i][3][1] = y4;
	}
}

void createGraph()			//各机场之间距离
{
	double d;
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = i + 1; k < S; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					d = sqrt(pow(plane[i][j][0] - plane[k][l][0], 2) +
						pow(plane[i][j][1] - plane[k][l][1], 2)) * T;
					graph[4 * i + j][4 * k + l] = d;
					graph[4 * k + l][4 * i + j] = d;
				}		
			}
		}
	}
}

double dijkstra(int start)
{
	double dis[400] = { INF };
	bool book[400] = { false };

	for (int i = 0; i < 4*S; i++)
	{
		dis[i] = graph[start][i];	//初始化源点到各个顶点的距离
	}
	book[start] = true;				//标记源点
	for (int i = 0; i < 4*S; i++)
	{
		int minPoint = start;
		int min = INF;
		for (int j = 0; j < 4*S; j++)
		{
			if (book[j] == false && dis[j] < min)
			{
				min = dis[j];
				minPoint = j;
			}
		}
		book[minPoint] = true;			//每循环一次重新找到离源点最近的点
		for (int k = 0; k < 4*S; k++)	//松弛操作
		{
			if (graph[minPoint][k] < INF)	//防止走不存在的路径
			{
				if (dis[k] > dis[minPoint] + graph[minPoint][k])		//松弛成功
				{
					dis[k] = dis[minPoint] + graph[minPoint][k];
				}
			}
		}
	}
	return min(min(dis[4 * B], dis[4 * B + 1]), min(dis[4 * B + 2], dis[4 * B + 3]));
}

double solve()
{
	A--;		//从0开始
	B--;
	double ans[4];
	for (int i = 0; i < 4; i++)
	{
		ans[i] = dijkstra(4 * A + i);
	}
	return min(min(ans[0], ans[1]), min(ans[2], ans[3]));
}

int main()
{
	int n;
	cin >> n;
	while (n-- > 0)
	{
		input();
		createGraph();
		printf("%.1f", solve());
	}
	return 0;
}
