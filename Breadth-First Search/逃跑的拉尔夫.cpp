/*
*问题描述：小镇的地图是矩形的，上面的符号用来标明哪儿可以行车哪儿不行。“.”表示小镇上那块地方是可以行车的，而符号“X”表示此处不能行车。
*拉尔夫所开小车的初始位置用字符的“*”表示，且汽车能从初始位置通过。汽车能向四个方向移动：向北(向上)，向南(向下)，向西(向左)，向东(向右)。
*拉尔夫所开小车的行动路线是通过一组给定的方向来描述的。在每个给定的方向，拉尔夫驾驶小车通过小镇上一个或更多的可行车地点。
*输入说明：输入文件的第一行包含两个用空格隔开的自然数R和C，1≤R≤50，1≤C≤50，分别表示小镇地图中的行数和列数。
*以下的R行中每行都包含一组C个符号(“.”或“X”或“*”)用来描述地图上相应的部位。接下来的第R+2行包含一个自然数N，1≤N≤1000，表示一组方向的长度。
*接下来的N行幅行包含下述单词中的任一个：NORTH(北)、SOUTH(南)、WEST(西)和EAST(东)，表示汽车移动的方向，任何两个连续的方向都不相同。
*输出：输出应包含用R行表示的小镇的地图(象输入文件中一样)，字符“*”应该仅用来表示汽车最终可能出现的位置。
*/
//最初没有考虑去重，占用空间超出。在每一遍BFS中有可能存在大量重复的点，因此使用set代替queue。

#include <iostream>
#include <set>
#include <iterator>
#include <string>
using namespace std;
static int R, C, N;
static char map[50][50];
static string f[1000];
struct Point{ int x; int y; }start;

bool isforbid(int x, int y)
{
	if (x < 0 || x > R - 1 || y < 0 || y > C - 1)
		return true;
	if (map[x][y] == 'X')
		return true;
	return false;
}

void solve(set<pair<int, int> > &fir, set<pair<int, int> > &sec, int i)
{
	string s = f[i];
	sec.clear();
	int nx, ny;
	if (s == "NORTH")
		nx = -1, ny = 0;
	else if (s == "SOUTH")
		nx = 1, ny = 0;
	else if (s == "WEST")
		nx = 0, ny = -1;
	else if (s == "EAST")
		nx = 0, ny = 1;
	int tx, ty;
	for (set<pair<int, int> >::iterator it = fir.begin(); it != fir.end(); it++)
	{
		tx = it->first + nx;
		ty = it->second + ny;
		while (!isforbid(tx, ty))
		{
			if (i == N - 1)
				map[tx][ty] = '*';
			sec.insert(make_pair(tx, ty));
			tx += nx;
			ty += ny;
		}
	}
}

int main()
{
	cin >> R >> C;
	char c;
	int i, j;
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			cin >> c;
			map[i][j] = c;
			if (c == '*')
			{
				start.x = i;
				start.y = j;
			}
		}
	}
	cin >> N;
	for (i = 0; i < N; i++)
		cin >> f[i];
	set <pair<int, int> > fir, sec;
	fir.insert(make_pair(start.x, start.y));
	map[start.x][start.y] = '.';
	for (i = 0; i < N; i++)
	{
		if (i % 2 == 0)
			solve(fir, sec, i);
		else
			solve(sec, fir, i);
	}
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
			cout << map[i][j];
		cout << endl;
	}
	return 0;
}
