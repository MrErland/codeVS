/*
*数轴上有n条线段，线段的两端都是整数坐标，坐标范围在0~1000000，每条线段有一个价值
*从n条线段中挑出若干条线段，使得这些线段两两不覆盖（端点可以重合）且线段价值之和最大。n<=1000
*输入:第一行一个整数n，表示有多少条线段。
*接下来n行每行三个整数, ai bi ci，分别代表第i条线段的左端点ai，右端点bi（左端点<右端点）和价值ci。
*输出:能够获得的最大价值
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct lines {int l; int r; int w; };

int cmp(const void *a, const void *b)
{
	if ((*(struct lines *)a).l == (*(struct lines *)b).l)
		return (*(struct lines *)a).r - (*(struct lines *)b).r;
	return (*(struct lines *)a).l - (*(struct lines *)b).l;
}

int main()
{
	int n;
	cin >> n;
	vector<struct lines> lin(n);
	for (int i = 0; i < n; i++)
		cin >> lin[i].l >> lin[i].r >> lin[i].w;
	qsort(&lin[0], n, sizeof(lin[0]), cmp);			//优先左端点从小到大排序，再排右端点从小到大
	vector<int> dpw(n);					//表示选中线段的最大权值
	vector<int> dpl(n);					//选中线段不重复的右边界
	for (int i = 0; i < n; i++)				//初始化
	{
		dpl[i] = lin[i].r;
		dpw[i] = lin[i].w;
	}
	int temp;
	for (int i = 0; i < n; i++)
	{
		temp = dpw[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (lin[i].l >= dpl[j])
			{
				dpw[i] = max(dpw[i], dpw[j] + lin[i].w);
			}
		}
		if (temp != dpw[i])
			dpl[i] = lin[i].r;
	}
	sort(dpw.begin(), dpw.end());
	cout << dpw[n - 1];
	return 0;
}
