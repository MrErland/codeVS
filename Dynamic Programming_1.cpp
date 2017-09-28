/*
*装箱问题的递归解法和动态规划解法。
*问题描述：有一个箱子容量为V（正整数，0<=V<=20000），同时有n个物品（0<n<=30），每个物品有一个体积（正整数）。
*要求n个物品中，任取若干个装入箱内，使箱子的剩余空间为最小。
*输入说明：一个整数v，表示箱子容量，一个整数n，表示有n个物品，接下来n个整数，分别表示这n 个物品的各自体积。
*/

//1.递归解法

#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static int cap = 0;
static int n = 0;
vector <int> res;

void solu(int leftcap,vector<int> &bag, vector<bool> &mark)
{
	if (leftcap < bag[0] || count(mark.begin(), mark.end(), false) == 0)
	{
		if (leftcap == 0)
		{
			cout << "0";
			exit(1);
		}
		res.push_back(leftcap);
		return;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (leftcap - bag[i] >= 0 && !mark[i])
		{
			mark[i] = true;
			solu(leftcap - bag[i], bag, mark);
		}
	}
}

int main()
{
	cin >> cap;
	cin >> n;
	vector<int> bag(n);
	vector<bool> mark(n);
	for (int i = 0; i < n; i++)
	{
		cin >> bag[i];
	}
	sort(bag.begin(), bag.end());	
	solu(cap, bag, mark);
	sort(res.begin(), res.end());
	cout << res[0];
	return 0;
}


//2.动态规划解法

#include <iostream>
#include <algorithm>
using namespace std;

const int V = 0xffff;
int f[V], w, v, j;

int main()
{
	cin >> v >> w;			    	//不需要读入n，对于下面那句来说没有必要	        		
	while (cin >> w)          //滚动数组 w既表示体积，又表示价值
	for (j = v; j >= w; j--)	//依次判断是否将物体放入容量为j的背包中
		f[j] = max(f[j], f[j - w] + w);
	cout << v - f[v];
	return 0;
}

