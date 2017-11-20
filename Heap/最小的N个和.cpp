/*
*问题描述：有两个长度为 N 的序列 A 和 B，在 A 和 B 中各任取一个数可以得到 N^2 个和，求这N^2 个和中最小的 N个。
*输入说明：第一行输入一个正整数N；第二行N个整数Ai 且Ai≤10^9；第三行N个整数Bi，且Bi≤10^9
*输出：输出仅一行，包含 n 个整数，从小到大输出这 N个最小的和，相邻数字之间用空格隔开。
*/



#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 100000 + 5;

int main()
{
	int n, da[N], db[N];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &da[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &db[i]);
	sort(da, da + n);           //先排序，优化速度
	sort(db, db + n);           //如上
	priority_queue<int> q;      //建立最大堆，考虑堆顶元素
	for (int i = 1; i <= n; i++)
		q.push(da[1] + db[i]);
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (da[i] + db[j] < q.top())
			{
				q.pop();
				q.push(da[i] + db[j]);
			}
			else
				break;
		}
	}
	int res[N];
	for (int i = 1; i <= n; i++)
	{
		res[i] = q.top();
		q.pop();
	}
	for (int i = n; i >= 1; i--)
		printf("%d ", res[i]);

	return 0;
}
