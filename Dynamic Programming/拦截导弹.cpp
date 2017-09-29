/*
*某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。
*但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度，但是以后每一发炮弹都不能高于前一发的高度。
*某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。
*输入:导弹依次飞来的高度(雷达给出的高度数据是不大于30000的正整数)
*输出:这套系统最多能拦截多少导弹，如果要拦截所有导弹最少要配备多少套这种导弹拦截系统。
*/


#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int max(vector<int>::iterator a, vector<int>::iterator b)
{
	if (a == b)
		return *a;
	int max = -0xffff;
	while (a != b)
	{
		if (*a > max)
			max = *a;
		++a;
	}
	return max;
}

int main()
{
	int temp;
	size_t a = 0;
	vector <int> height;
	int maxNum = 0;			//一次最大数目
	int times = 0;			//系统使用次数
	while (cin >> temp)
	{
		height.push_back(temp);
		a++;
	}
	while (a)
	{
		times++;
		vector <int> dp(a, 1);
		vector <int> path(a);
		vector <bool> mark(a);
		for (int i = 0; i < a; i++)
			path[i] = i;						//初始
		for (int i = a - 2; i >= 0; i--)
		{
			for (int j = i + 1; j < a; j++)
			{
				if (height[i] > height[j])
				{
					temp = dp[i];
					dp[i] = max(dp[j] + 1, dp[i]);		//找到小于当前高度的后续最大高度
					if (dp[i] != temp)
						path[i] = j;			//保存可以拦截的炮弹
				}
			}
		}
		int nowNum = max(dp.begin(), dp.end());
		maxNum = maxNum > nowNum ? maxNum : nowNum;
		vector<int>::iterator now = find(dp.begin(), dp.end(), nowNum);
		int site = now - dp.begin();
		while (path[site] != site)					 //找到这次拦截的炮弹
		{
			mark[site] = 1;
			site = path[site];
		}
		if (site < a)
			mark[site] = 1;
		for (int i = a - 1; i >= 0; i--)				//删除这次拦截的导弹
		{
			if (mark[i])
				height.erase(height.begin() + i, height.begin() + i + 1);
		}
		a = height.size();						//重新初始化a
	}
	cout << maxNum << endl;							//找到一次拦截导弹的最大数量--第一次
	cout << times;
	return 0;
}
