/*
*问题描述：给你N个数，有两种操作：1：给区间[a,b]的所有数都增加X；2：询问第i个数是什么？
*输入说明：第一行一个正整数n，接下来n行n个整数，再接下来一个正整数Q，表示操作的个数. 接下来Q行每行若干个整数。
*如果第一个数是1，后接3个正整数a,b,X，表示在区间[a,b]内每个数增加X,如果是2，后面跟1个整数i, 表示询问第i个位置的数是多少。
*输出：对于每个询问输出一行一个答案。
*/


//暴力解法

#include <cstdio>
using namespace std;
const int SZ = 100000;
int N, M;
int data[SZ];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &data[i]);
	scanf("%d", &M);
	int mode, a, b, c;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &mode);
		if (mode == 1)
		{
			scanf("%d %d %d", &a, &b, &c);
			for (int j = a - 1; j <= b - 1; j++)
				data[j] += c;
		}
		else if (mode == 2){
			scanf("%d", &a);
			printf("%d\n", data[a - 1]);
		}
	}
	return 0;
}


//线段树解法

#include <cstdio>
using namespace std;
#define min(a, b) (a < b ? a : b)
const int SZ = 100000;
struct SegTree{ int value; }seg[3 * SZ];
int N, M, data[SZ];

void build(int root, int left, int right)
{
	if (left == right)
		seg[root].value = data[left];
	else{
		int mid = (left + right) / 2;
		build(root * 2 + 1, left, mid);
		build(root * 2 + 2, mid + 1, right);
		seg[root].value = seg[root * 2 + 1].value + seg[root * 2 + 2].value;	//保存为左右结点的和
	}
}

void update(int root, int left, int right, int index, int add)
{
	if (left == right)
	{
		if (index == left)
			seg[root].value += add;
		return;
	}
	int mid = (left + right) / 2;
	if (index <= mid)
		update(root * 2 + 1, left, mid, index, add);
	else
		update(root * 2 + 2, mid + 1, right, index, add);
	seg[root].value = seg[root * 2 + 1].value + seg[root * 2 + 2].value;
}

int search(int root, int left, int right,int index)
{
	if (left == right)
	{
		if (index == left)
			return seg[root].value;
	}
	int mid = (left + right) / 2;
	if (index <= mid)
		search(root * 2 + 1, left, mid, index);
	else
		search(root * 2 + 2, mid + 1, right, index);
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &data[i]);
	build(0, 0, N - 1);					//创建线段树,求和树
	scanf("%d", &M);
	int mode, a, b, c;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &mode);
		if (mode == 1)					//更新模式
		{
			scanf("%d %d %d", &a, &b, &c);
			for (int j = a - 1; j <= b - 1; j++)
				update(0, 0, N - 1, j, c);
		}
		else if (mode == 2)				//查询模式
		{
			scanf("%d", &a);
			printf("%d\n", search(0, 0, N - 1, a - 1));
		}
	}
	return 0;
}
