/*
*问题描述:地鼠游戏是一项需要反应速度和敏捷判断力的游戏。游戏开始时，会在地板上一下子冒出很多地鼠来，然后等你用榔头去敲击这些地鼠，每个地鼠被敲击后，将会增加相应的游戏分值。
*问题是这些地鼠总会在冒出一会时间后又钻到地板下面去（而且再也不上来），每个地鼠冒出后停留的时间可能是不同的，而且每个地鼠被敲击后增加的游戏分值也可能是不同。
*为了胜出，游戏参与者就必须根据每个地鼠的特性，有选择地尽快敲击一些地鼠，使得总的得分最大。
*输入说明: 输入包含3行，第一行包含一个整数n（1<=n<=100）表示有n个地鼠从地上冒出来，第二行n个用空格分隔的整数表示每个地鼠冒出后停留的时间
*第三行n个用空格分隔的整数表示每个地鼠被敲击后会增加的分值（<=100）。每行中第i个数都表示第i个地鼠的信息。
*输出:输出只有一行一个整数，表示王钢所能获得的最大游戏总分值。
*/


//采用贪心的思想，先按照地鼠的分值排序，依次将分值从大到小的地鼠填入其时间的site里
//如果site已经被填充，则填充依次填充前一个site，知道前方site全部被占据，则舍弃这个地鼠的分值

#include <cstdio>
#include <algorithm>
using namespace std;
int n, score = 0;
struct Rat{ int time; int value; }rat[102];
int site[102] = { 0 };				//site[i] 第i次出手是否打地鼠

int cmp(struct Rat a, struct Rat b){return a.value > b.value;}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &rat[i].time);
	for (int i = 0; i < n; i++)
		scanf("%d", &rat[i].value);
	sort(rat, rat + n, cmp);		//按照地鼠的分值排序
	int a;
	for (int i = 0; i < n; i++)
	{
		a = rat[i].time;
		while (site[a] && a >= 1)
			a--;
		if (a == 0)			//time之前的site都被占据，舍弃这个地鼠
			continue;
		site[a] = 1;			//找到site填充这个地鼠
		score += rat[i].value;
	}
	printf("%d\n", score);
	return 0;
}
