/*
*问题描述： 给定x轴上的N（0<N<100）条线段，每个线段由它的二个端点a_I和b_I确定，I=1,2,……N.这些坐标都是区间(-999,999)的整数。
*有些线段之间会相互交叠或覆盖。编写一个程序，从给出的线段中去掉尽量少的线段，使得剩下的线段两两之间没有内部公共点。
*所谓的内部公共点是指一个点同时属于两条线段且至少在其中一条线段的内部（即除去端点的部分）。
*输入描述：输入第一行是一个整数N。接下来有N行，每行有二个空格隔开的整数，表示一条线段的二个端点的坐标。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct line
{
	int l;
	int r;
};

int cmp(const void *a, const void *b)			//先对左端点排序，如果相等对右端点排序，从小到大
{
	if (((struct line *)a)->l > ((struct line *)b)->l)
		return 1;
	else if (((struct line *)a)->l == ((struct line *)b)->l)
		return ((struct line *)a)->r > ((struct line *)b)->r;
	else
		return -1;
}

int main()
{
	int n = 0;
	cin >> n;
	int s, t;
	vector<struct line> lines(n);
	for (int i = 0; i < n; i++)
	{
		cin >> s >> t;
		if (s < t)
		{
			lines[i].l = s;
			lines[i].r = t;
		}else{
			lines[i].l = t;
			lines[i].r = s;
		}
	}
	qsort(&lines[0], n, sizeof(lines[0]), cmp);
	int res = 1; 
	int now = lines[0].r;
	for (int i = 1; i < n; i++)
	{
		if (lines[i].l >= now)
		{
			now = lines[i].r;
			++res;
		}
		else if (lines[i].r <= now)
		{
			now = lines[i].r;
		}
	}
	cout << res;
	return 0;
}
