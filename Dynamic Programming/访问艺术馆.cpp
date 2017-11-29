/*
*问题描述：皮尔是一个盗画者，他打算到艺术馆盗画。艺术馆的结构，每条走廊要么分叉为二条走廊，要么通向一个展览室。
*皮尔知道每个展室里藏画的数量，并且他精确地测量了通过每条走廊的时间，他拿下一副画需要5秒的时间。
*你设计一个程序，计算在警察赶来之前(警察到达时皮尔回到了入口也算)，他最多能偷到多少幅画。
*输入说明：第1行是警察赶到得时间，以s为单位。第2行描述了艺术馆得结构，是一串非负整数，成对地出现：
*每一对得第一个数是走过一条走廊得时间，第2个数是它末端得藏画数量；如果第2个数是0，那么说明这条走廊分叉为两条另外得走廊。数据按照深度优先得次序给出。
*输出：输出偷到得画得数量。
*/


//参考博客： http://blog.csdn.net/re_cover/article/details/9388071

#include<cstdio>  
#include<cstring>  
using namespace std;
#define N 605
#define T 605
struct node{ int lson, rson, val, cost; }tree[N];		// 左孩子、 右孩子、 画数量、 花费时间
struct data{ int t, v; } buf[N];
int dp[N][T];
int n, m;

int max(int x, int y){ return x > y ? x : y; }

void build(int &x)						//按照深度优先顺序（前序遍历）建树   
{
	int root = x;
	tree[root].cost = 2 * buf[root].t;	//减去经过走廊的来回时间花费  
	tree[root].val = buf[root].v;
	if (buf[x].v)						//判断是否是叶子节点   
	{
		tree[root].lson = tree[root].rson = -1;    //没有左右孩子   
		return;
	}
	tree[root].lson = x + 1;         //左孩子是下一个节点   
	build(++x);                      //以左孩子为根节点继续建树   
	tree[root].rson = x + 1;         //右孩子是下一个节点  
	build(++x);                      //以右孩子为根节点继续建树  
}

int dfs(int root, int time)             // dp[root][time]表示在root这个节点(岔口)，剩余time时能偷到的最大副画   
{
	if (dp[root][time] != -1)
		return dp[root][time];          //如果有答案，就结束返回   
	if (time <= 0)
		return dp[root][time] = 0;      //时间还剩0，则一副也偷不到   
	if (tree[root].lson == -1)          //是叶子   
	{
		int cnt;
		if (tree[root].val * 5 <= time - tree[root].cost)
			cnt = tree[root].val;		//如果经过走廊后的剩余时间可以全部偷完画，直接赋值   
		else
			cnt = (time - tree[root].cost) / 5;          //偷不完就尽可能多拿   
		return dp[root][time] = cnt;	//返回结果   
	}
	dp[root][time] = 0;                     //初始化   
	int remain = time - tree[root].cost;    //经过走廊后的剩余时间
	for (int i = 0; i <= remain; i++)       //枚举分配一部分时间给左孩子，剩余时间往右孩子那边去偷   
	{
		int s1 = dfs(tree[root].lson, i);              //往左孩子方向偷的最多的画   
		int s2 = dfs(tree[root].rson, remain - i);     //往右孩子那边偷的最多的画   
		dp[root][time] = max(dp[root][time], s1 + s2);   //遍历寻求最大值
	}
	return dp[root][time];
}

int main()
{
	int time;
	n = m = 0;
	scanf("%d", &time);
	while (scanf("%d %d", &buf[n].t, &buf[n].v) != EOF)
		n++;
	build(m);						//以0为根节点建树   
	memset(dp, -1, sizeof(dp));
	dfs(0, time);
	printf("%d", dp[0][time]);		//0节点，剩余time时间能偷到的最大画就是结果
	return 0;
}
