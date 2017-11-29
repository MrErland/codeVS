/*
*问题描述：农民约翰被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。
*约翰已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了使花费最少，他想铺设最短的光纤去连接所有的农场。
*你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过100000。
*输入说明：第一行： 农场的个数，N（3<=N<=100）。
*接下来的行包含了一个N*N的矩阵,表示每个农场之间的距离。对角线将会是0，因为线路从第i个农场到它本身的距离在本题中没有意义。
*输出：只有一个输出，是连接到每个农场的光纤的最小长度和。
*/



#include <cstdio>
using namespace std;
#define SZ 105
#define MAX 100005
int N;
int ans = 0;
int farm[SZ][SZ];
int book[SZ] = { 0 };	//标记 MST 中的顶点

void prim()
{
	int s = 0;				// s 为MST中的结点
	int t = 0;				// 最近的非MST结点
	book[1] = 1;
	for (int p = 1; p <= N - 1; p++)	// N-1 次
	{
		int minlen = MAX;
		for (int k = 1; k <= N; k++)
		{
			if (!book[k])
				continue;
			s = k;
			for (int i = 1; i <= N; i++)
			{
				if (farm[s][i] < minlen && !book[i])
				{
					minlen = farm[s][i];
					t = i;
				}
			}
		}
		book[t] = 1;	// t 加入 MST
		ans += minlen;	// 更新权值
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			scanf("%d", &farm[i][j]);
	}
	prim();
	printf("%d\n", ans);
	return 0;
}
