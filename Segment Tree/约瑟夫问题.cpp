/*
*问题描述：有编号从1到N的N个小朋友在玩一种出圈的游戏。开始时N个小朋友围成一圈，编号为I+1的小朋友站在编号为I小朋友左边。
*编号为1的小朋友站在编号为N的小朋友左边。首先编号为1的小朋友开始报数，接着站在左边的小朋友顺序报数，直到数到某个数字M时就出圈。
*直到只剩下1个小朋友，则游戏完毕。现在给定N,M，求N个小朋友的出圈顺序。
*输入说明：唯一的一行包含两个整数N,M。（1<=N, M<=30000）
*输出：唯一的一行包含N个整数，每两个整数中间用空格隔开，第I个整数表示第I个出圈的小朋友的编号。
*/


//循环链表解法  复杂度 N*M

#include <cstdio>
using namespace std;
const int SZ = 30000;
int N, M;
struct person{ int value; int next; }circle[SZ];

void build(int n)
{
	int i, j;
	for (i = 0, j = 1; i < n - 1; i++, j++)
	{
		circle[i].value = j;
		circle[i].next = i + 1;
	}
	circle[i].value = j;
	circle[i].next = 0;
}

void work()
{
	int i = 0, j = 0, pre;
	while (circle[i].next != i)
	{
		for (j = 0; j < M - 1; j++)
		{
			pre = i;
			i = circle[i].next;
		}
		circle[pre].next = circle[i].next;
		printf("%d ", circle[i].value);
		i = circle[pre].next;
	}
	printf("%d", circle[i].value);
}

int main()
{
	scanf("%d %d", &N, &M);
	build(N);
	work();
	return 0;
}


//数学法  最后胜利的人  复杂度 N

#include<cstdio>
int main()
{
	int n, m, s = 1;
	scanf("%d %d", &n, &m);
	for (int i = 2; i <= n; i += 1)
	{
		s = (s + m) % i;
		if (s == 0)
			s = i;
	}
	printf("%d", s);
	return 0;
}


//数学法  复杂度 N*M

#include <cstdio>
int main()
{
	int n, i = 0, m, p;
	scanf("%d %d", &n, &m);
	while (++i < n)
	{
		p = i * m;
		while (p > n)
			p = p - n + (p - n - 1) / (m - 1);
		printf("%d ", p);
	}
	return 0;
}


//线段树解法  复杂度 NlogN

#include <cstdio>
using namespace std;
#define Lson l, m, root << 1
#define Rson m + 1, r, root << 1 | 1
#define Mid (l + r) >> 1
const int N = 30000 + 10;
int n, m, seg[N << 2];

void build(int l, int r, int root) 
{
	if (l == r) 
	{
		seg[root] = 1;
		return;
	}
	int m = Mid;
	build(Lson);
	build(Rson);
	seg[root] = seg[root << 1] + seg[root << 1 | 1];
}

//名次树是以名次为区间，通过对区间内的人数加减，再用相对位置与人数相比可得到他的编号所属区间，坐后递归直到得到了编号。

void update(int p, int l, int r, int root) 
{
	seg[root]--;
	if (l == r)
	{
		printf("%d ", l);
		return;
	}
	int m = Mid;
	if (p <= seg[root << 1])			//相对位置小于左边人数说明这个人的编号在左边
		update(p, Lson);		
	else								          //反之在右边，并且人数要减去左边人数
		update(p - seg[root << 1], Rson);
	seg[root] = seg[root << 1] + seg[root << 1 | 1];
}

int main()
{
	scanf("%d %d", &n, &m);
	build(1, n, 1);
	int seq = 1;						//从1开始报数
	for (int i = 1; i <= n; ++i) 
	{
		seq = (seq + m - 1) % seg[1]; 
		if (!seq)
			seq = seg[1];
		update(seq, 1, n, 1);
	}
	return 0;
}
