/*
*问题描述：设有一个n*m的棋盘（2≤n≤50，2≤m≤50），如下图，在棋盘上有一个中国象棋马。规定：
*1)马只能走日字  2)马只能向右跳
*问给定起点x1,y1和终点x2,y2，求出马从x1,y1出发到x2,y2的合法路径条数。
*输入说明：第一行2个整数n和m  第二行4个整数x1,y1,x2,y2
*输出：合法路径条数
*/

/*
*No.1考虑先使用深度优先搜索，从起始点搜索到目的点的左侧边缘为止。
*错误：当距离较远时，超时。
*/

#include <iostream>
using namespace std;
static int n, m;
static int x, y, x2, y2;
static int ans = 0;

void dfs(int x, int y)
{
	if (x > x2)			                //越过目标点
		return;
	if (x > n || x < 1 || y > m || y < 1)		//越界
		return;
	if (x == x2 && y == y2)
	{
		ans++;
		return;
	}
	if (x + 1 <= x2 && y + 2 <= m)
		dfs(x + 1, y + 2);
	if (x + 1 <= x2 && y - 2 >= 1)
		dfs(x + 1, y - 2);
	if (x + 2 <= x2 && y + 1 <= m)
		dfs(x + 2, y + 1);
	if (x + 2 <= x2 && y - 1 >= 1)
		dfs(x + 2, y - 1);
}

int main()
{
	cin >> n >> m;
	cin >> x >> y;
	cin >> x2 >> y2;
	dfs(x, y);
	cout << ans;
	return 0;
}


/*
*No.2使用动态规划，从起始点横坐标到目的点横坐标为止。
*AC
*/

#include <iostream>
using namespace std;
const int N = 51;
static long long int dp[N][N];

int main()
{
	int n, m;
	cin >> n >> m;
	int x, y, x2, y2;
	cin >> x >> y >> x2 >> y2;
	dp[x][y] = 1;
	for (int i = x + 1; i <= x2; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (j - 2 >= 1)
				dp[i][j] += dp[i - 1][j - 2];
			if (j + 2 <= m)
				dp[i][j] += dp[i - 1][j + 2];
			if (j - 1 >= 1)
				dp[i][j] += dp[i - 2][j - 1];
			if (j + 1 <= m)
				dp[i][j] += dp[i - 2][j + 1];
		}
	}
	cout << dp[x2][y2];
	return 0;
}
