/*
*问题描述:一行N个方格，开始每个格子里都有一个整数。现在动态地提出一些问题和修改：
*提问的形式是求某一个特定的子区间[a,b]中所有元素的和；修改的规则是指定某一个格子x，加上或者减去一个特定的值A。
*现在要求你能对每个提问作出正确的回答。1≤N<100000,提问和修改的总数m<10000条。
*输入说明:输入文件第一行为一个整数N，接下来是n行n个整数，表示格子中原来的整数。接下一个正整数m，再接下来有m行，表示m个询问，第一个整数表示询问代号
*询问代号1表示增加，后面的两个数x和A表示给位置X上的数值增加A，询问代号2表示区间求和，后面两个整数表示a和b，表示要求[a,b]之间的区间和。
*输出：共m行，每个整数。
*/

//暴力解法

#include<cstdio>
using namespace std;
const int SZ = 100000;
int N;
int M;
int data[SZ];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &data[i]);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		int des = 0;
		int a, b;
		scanf("%d %d %d", &des, &a, &b);
		if (des == 1)
		{
			data[a - 1] += b;
		}
		else if (des == 2){
			int ans = 0;
			for (int i = a - 1; i < b; i++)
			{
				ans += data[i];
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}


//线段树，效率是暴力法的几十倍，空间使用较多

#include <cstdio>
using namespace std;
#define min(a, b) (a < b ? a : b)
const int SZ = 100000;
struct SegTree{ int value; }seg[3 * SZ];
int data[SZ];
int N;
int M;

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

void update(int root, int left,int right, int index, int add)
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

int sum(int root, int left, int right, int start, int end)
{
	if (start > right || end < left)
		return 0;
	if (start <= left && right <= end)
		return seg[root].value;
	int mid = (left + right) / 2;
	return sum(root * 2 + 1, left, mid, start, end) + sum(root * 2 + 2, mid + 1, right, start, end);
}

int main()
{
	scanf("%d", &N);	
	for (int i = 0; i < N; i++)	
		scanf("%d", &data[i]);	
	build(0, 0, N - 1);					//创建线段树
	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		int mode, a, b;
		scanf("%d %d %d", &mode, &a, &b);
		if (mode == 1)					//更新模式
			update(0, 0, N - 1, a - 1, b);
		else if (mode == 2)				//求和模式
			printf("%d\n", sum(0, 0, N - 1, a - 1, b - 1));
	}
	return 0;
}
