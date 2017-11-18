/*
*问题描述:在一个果园里，多多已经将所有的果子打了下来，而且按果子的不同种类分成了不同的堆。
*多多决定把所有的果子合成一堆。每一次合并，多多可以把两堆果子合并到一起，消耗的体力等于两堆果子的重量之和。
*可以看出，所有的果子经过n-1次合并之后，就只剩下一堆了。多多在合并果子时总共消耗的体力等于每次合并所耗体力之和。
*假定每个果子重量都为1，并且已知果子的种类数和每种果子的数目，你的任务是设计出合并的次序方案，使多多耗费的体力最少，并输出这个最小的体力耗费值。
*输入说明: 输入包括两行，第一行是一个整数n(1<＝n<=10000)，表示果子的种类数。第二行包含n个整数，用空格分隔，第i个整数ai(1<＝ai<=20000)是第i种果子的数目。
*输出:输出包括一行，这一行只包含一个整数，也就是最小的体力耗费值。输入数据保证这个值小于231。
*/



#include <cstdio>
#include <queue>
using namespace std;
int n, res = 0;

struct cmp{ bool operator()(const int a, const int b){ return a > b; } };

int main()
{
	scanf("%d", &n);
	priority_queue<int, vector<int>, cmp> fruit;
	int a, b;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a);
		fruit.push(a);
	}
	while (fruit.size() > 1)
	{
		a = fruit.top();
		fruit.pop();
		b = fruit.top();
		fruit.pop();
		res += (a + b);
		fruit.push(a + b);
	}
	printf("%d\n", res);
	return 0;
}
