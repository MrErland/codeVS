/*
*问题描述：乌龟棋的棋盘是一行N个格子，每个格子上一个分数（非负整数）。
*棋盘第1格是唯一的起点，第N格是终点，游戏要求玩家控制一个乌龟棋子从起点出发走到终点。
*乌龟棋中M张爬行卡片，分成4种不同的类型（M张卡片中不一定包含所有4种类型），每种类型的卡片上分别标有1、2、3、4四个数字之一，表示使用这种卡片后，乌龟棋子将向前爬行相应的格子数。
*游戏中，玩家每次需要从所有的爬行卡片中选择一张之前没有使用过的爬行卡片，控制乌龟棋子前进相应的格子数，每张卡片只能使用一次。游戏中，乌龟棋子自动获得起点格子的分数，并且在后续的爬行中每到达一个格子，就得到该格子相应的分数。
*玩家最终游戏得分就是乌龟棋子从起点到终点过程中到过的所有格子的 分数总和。找到一种卡片使用顺序使得最终游戏得分最多。
*输入说明：第1行2个正整数N和M，分别表示棋盘格子数和爬行卡片数。 
*第2行N个非负整数，其中ai表示棋盘第i个格子上的分数。第3行M个整数，表示M张爬行卡片上的数字。
*/

#include <iostream>
#include <vector>
using namespace std;
const int SZ = 100;
static int dp[SZ][SZ][SZ][SZ];
static int b[5];
int max(int a, int b, int c, int d)
{
	int m = a;
	if (b > m) m = b;
	if (c > m) m = c;
	if (d > m) m = d;
	return m;
}
int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i<n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i<m; i++)
	{
		cin >> b[0];
		b[b[0]]++;
	}
	int maxScore = 0;
	for (int t = 0; t <= b[1]; t++)
	{
		for (int i = 0; i <= b[2]; i++)
		{
			for (int j = 0; j <= b[3]; j++)
			{
				for (int k = 0; k <= b[4]; k++)
				{
					maxScore = 0;
					if (t) maxScore = maxScore > dp[t - 1][i][j][k] ? maxScore : dp[t - 1][i][j][k];
					if (i) maxScore = maxScore > dp[t][i - 1][j][k] ? maxScore : dp[t][i - 1][j][k];
					if (j) maxScore = maxScore > dp[t][i][j - 1][k] ? maxScore : dp[t][i][j - 1][k];
					if (k) maxScore = maxScore > dp[t][i][j][k - 1] ? maxScore : dp[t][i][j][k - 1];
					dp[t][i][j][k] = maxScore + a[t + 2 * i + 3 * j + 4 * k];
				}
			}
		}
	}
	cout << dp[b[1]][b[2]][b[3]][b[4]];
	return 0;
}
