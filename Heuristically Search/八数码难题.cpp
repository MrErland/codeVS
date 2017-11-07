/*
*问题描述：在3×3的棋盘上，摆有八个棋子，每个棋子上标有1至8的某一数字。棋盘中留有一个空格，空格用0来表示。
*空格周围的棋子可以移到空格中。要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为123804765）
*找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。
*输入说明：输入初试状态，一行九个数字，空格用0表示
*输出：只有一行，该行只有一个数字，表示从初始状态到目标状态需要的最少移动次数(测试数据中无特殊无法到达目标状态数据)
*/

// BFS + Hash

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
#define N 500000
struct node{int mp[4][4];}a[N];
int g[4][4] = {						//目标数组
	{ 0, 0, 0, 0 },
	{ 0, 1, 2, 3 },
	{ 0, 8, 0, 4 },
	{ 0, 7, 6, 5 }
};
int xx[4] = { 0, 0, 1, -1 };				//四个方向移动
int yy[4] = { 1, -1, 0, 0 };
int hashArr[3733800] = {0};
int step[N] = {0};
int h = 0;						//当前状态
int t = 1;						//总数
bool flag = 0;						//结束标志


int check()						//是否到达目标
{
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			if (a[t].mp[i][j] != g[i][j])
				return 0;
		}
	}
	return 1;
}

int Hash()						//去重
{
	int s = 0, k = 1;
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
			s += a[t].mp[i][j] * k, k *= 7;
	}
	s %= 3733799;
	if (!hashArr[s])				//第一次出现
	{
		hashArr[s] = 1;
		return 1; 
	}
	return 0;
}

int isOut(int x, int y)					//是否越界
{
	if (x >= 1 && x <= 3 && y >= 1 && y <= 3) 
		return 1;
	return 0;
}

void move(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int p = x + xx[i], q = y + yy[i];
		if (isOut(p, q))
		{
			for (int j = 1; j <= 3; j++)			
			{
				for (int k = 1; k <= 3; k++)
					a[t].mp[j][k] = a[h].mp[j][k];
			}
			swap(a[t].mp[x][y], a[t].mp[p][q]);		//新的状态
			step[t] = step[h] + 1;				//新的步数
			if (check())    
			{
				cout << step[t];
				flag = 1; 
				return; 
			}
			if (Hash())
				t++;
		}
	}
}

void search()
{
	while (h < t)
	{
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				if (a[h].mp[i][j] == 0)
					move(i, j);
				if (flag)
					return;
			}
		}
		h++;
	}
}

void input()
{
	string str;
	cin >> str;
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
			a[0].mp[i][j] = str[(i - 1) * 3 + j - 1] - '0';		//初始状态
	}
}

int main()
{
	input();
	search();
	return 0;
}
