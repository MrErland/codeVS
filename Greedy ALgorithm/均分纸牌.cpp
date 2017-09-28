/*
*问题描述：有N堆纸牌，编号分别为 1，2，…, N。每堆上有若干张，但纸牌总数必为 N 的倍数。可以在任一堆上取若于张纸牌，然后移动。
*移牌规则为：在编号为1堆上取的纸牌，只能移到编号为2的堆上；在编号为N的堆上取的纸牌，只能移到编号为N-1的堆上；其他堆上取的纸牌，可以移到相邻左边或右边的堆上。
*现在要求找出一种移动方法，用最少的移动次数使每堆上纸牌数都一样多。
*输入描述：第一行N（N 堆纸牌，1 <= N <= 100）第二行A1 A2 … An（N堆纸牌，每堆纸牌初始数，l<= Ai <=10000）
*/

#include <iostream>
#include <vector>
using namespace std;

static vector<int> data;
static int avg = 0;
static int res = 0;

void divide(int l, int r)
{
	if (l == r)
		return ;
	if (data[l] < avg)
	{
		data[l + 1] -= (avg - data[l]);
		data[l] = avg;
		++res;
	}
	else if (data[l] > avg)
	{
		data[l + 1] += (data[l] - avg);
		data[l] = avg;
		++res;
	}
	return divide(l + 1, r);
}

int main()
{
	int n;
	cin >> n;
	int temp;
	long int sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		data.push_back(temp);
		sum += temp;
	}
	unsigned int sz = data.size();
	avg = sum / n;
	divide(0, sz - 1);
	cout << res;
	return 0;
}
