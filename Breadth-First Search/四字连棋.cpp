/*
*问题描述：在一个4*4的棋盘上摆放了14颗棋子，其中有7颗白色棋子，7颗黑色棋子，有两个空白地带。
*任何一颗黑白棋子都可以向上下左右四个方向移动到相邻的空格，这叫行棋一步，黑白双方交替走棋，任意一方可以先走。
*如果某个时刻使得任意一种颜色的棋子形成四个一线（包括斜线），这样的状态为目标棋局。
*输入说明：读入一个4*4的初始棋局，黑棋子用B表示，白棋子用W表示，空格地带用O表示
*输出：最少的步数移动到目标棋局的步数
*/


#include <iostream>
#include <queue>
#include <cstdlib>
#include <map>
using namespace std;
struct status { int map[4][4]; int step; int pre; int hash; }Map;
static int Next[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
queue <struct status> q;
map <int, bool> h[3];

bool isgoal(struct status &a)			//满足目标棋局
{
	int i, j;
	bool f = true;
	for (i = 0; i < 4; i++)
	{
		f = true;
		for (j = 0; j <= 2; j++)
		{
			if (a.map[j][i] != a.map[j + 1][i])
				f = false;
		}
		if (f) return true;
	}
	for (i = 0; i < 4; i++)
	{
		f = true;
		for (j = 0; j <= 2; j++)
		{
			if (a.map[i][j] != a.map[i][j + 1])
				f = false;
		}
		if (f) return true;
	}
	f = true;
	for (i = 0, j = 0; i <= 2; i++, j++)
	{
		if (a.map[i + 1][j + 1] != a.map[i][j])
			f = false;
	}
	if (f) return true;
	f = true;
	for (i = 3, j = 0; i >= 1; i--, j++)
	{
		if (a.map[i - 1][j + 1] != a.map[i][j])
			f = false;
	}
	if (f) return true;
	return false;
}

bool notout(int r, int c)
{
	return r >= 0 && r <= 3 && c >= 0 && c <= 3;
}

void over(int s)
{
	cout << s;
	exit(0);
}

int gethash(struct status &a)		//使用hash函数记录每种走法的hash值
{
	int res = 0;
	int k = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res += a.map[i][j] * k;
			k *= 3;
		}
	}
	return res;
}

void getspace(struct status &now, int &r1, int &c1, int &r2, int &c2)		//保存两个空格的坐标
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (now.map[i][j] == 0)
			{
				if (r1 == -1 && c1 == -1)
					r1 = i, c1 = j;
				else
					r2 = i, c2 = j;
			}
		}
	}
}

void move(struct status &now, int r, int c, int k)
{
	struct status t = now;
	int tx = r + Next[k][0];
	int ty = c + Next[k][1];
	if (!notout(tx, ty) || t.map[tx][ty] == t.pre)		//越界 || 上一个棋子颜色相同
		return;

	swap(t.map[tx][ty], t.map[r][c]);
	t.pre = 3 - t.pre;
	t.hash = gethash(t);
	t.step++;
	if (!h[t.pre][t.hash])		//判重
	{
		h[t.pre][t.hash] = true;
		q.push(t);
	}
	else
		return;
	if (isgoal(t))
		over(t.step);
}

void bfs()
{
	Map.hash = gethash(Map);
	Map.pre = 1;		//白色先行
	Map.step = 0;
	q.push(Map);
	Map.pre = 2;		//黑色先行
	q.push(Map);
	Map.step = 0;
	while (!q.empty())
	{
		struct status now = q.front();
		q.pop();
		int r1 = -1, r2 = -1, c1 = -1, c2 = -1;
		getspace(now, r1, c1, r2, c2);
		for (int i = 0; i < 4; i++)
		{
			move(now, r1, c1, i);
			move(now, r2, c2, i);
		}
	}
}

int main()
{
	int i, j;
	char t;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cin >> t;
			if (t == 'B')
				Map.map[i][j] = 1;		//黑色
			if (t == 'W')
				Map.map[i][j] = 2;		//白色
			if (t == 'O')
				Map.map[i][j] = 0;		//空格
		}
	}
	if (isgoal(Map))
		over(0);
	bfs();
	return 0;
}
