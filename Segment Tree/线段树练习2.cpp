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


