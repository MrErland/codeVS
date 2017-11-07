/*
*问题描述：靶形数独的方格同普通数独一样，在 9 格宽×9 格高的大九宫格中有9 个3 格宽×3 格高的小九宫格（用粗黑色线隔开的）。
*在这个大九宫格中，有一些数字是已知的，根据这些数字，利用逻辑推理，在其他的空格上填入1 到9 的数字。
*每个数字在每个小九宫格内不能重复出现，每个数字在每行、每列也不能重复出现。
*但靶形数独有一点和普通数独不同，即每一个方格都有一个分值，而且如同一个靶子一样，离中心越近则分值越高。
*输入说明：一共 9 行。每行9 个整数（每个数都在0—9 的范围内），表示一个尚未填满的数独方格，未填的空格用“0”表示。每两个数字之间用一个空格隔开。
*输出：输出可以得到的靶形数独的最高分数。如果这个数独无解，则输出整数-1。
*/


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MAX(a, b) (a > b ? a : b)
using namespace std;
int Map[10][10] = { 0 };
int Nine[10][10] = { 0 };
int Row[10][10] = { 0 };		
int Col[10][10] = { 0 };		
int Value[10][10] = { 0 };		
int QueR[81] = { 0 };    
int QueC[81] = { 0 };
int QLen = 0;
int Ans = -1;

void Swap(int *a, int *b)
{
	int o = *a;
	*a = *b;
	*b = o;
}

void Heu()  //启发函数
{
	int FQueL[10] = { 0 };
	int FQueR[10] = { 0 };
	for (int i = 1; i <= 9; ++i)
	{
		FQueL[i] = i;
		FQueR[i] = i;
	}
	for (int i = 1; i <= 8; ++i)		//冒泡排序
	{
		for (int j = 9; j >= i + 1; --j)
		{
			if (Row[FQueL[j]][0] > Row[FQueL[j - 1]][0])		//行使用过数字多的排到最前
				Swap(&FQueL[j], &FQueL[j - 1]);
			if (Col[FQueR[j]][0] > Col[FQueR[j - 1]][0])		//列使用过数字多的排到最前
				Swap(&FQueR[j], &FQueR[j - 1]);
		}
	}
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			if (Map[FQueL[i]][FQueR[j]] == 0)		//如果没填数字
			{
				QueR[QLen] = FQueL[i];				//行顺序
				QueC[QLen] = FQueR[j];				//列顺序
				QLen++;								//长度
			}
		}
	}
}

int belong(int i, int j)     //i，j属于哪一个九宫格
{
	int xt = 0, yt = 0;
	for (int k = 6; k >= 0; k -= 3)
	{
		if (i - k > 0)
		{
			xt = (k + 3) / 3;
			break;
		}
	}
	for (int k = 6; k >= 0; k -= 3)
	{
		if (j - k > 0)
		{
			yt = (k + 3) / 3;
			break;
		}
	}
	return yt + (xt - 1) * 3;
}

void Score()           //计算分数
{
	int Temp = 0;
	for (int i = 1; i <= 9; ++i)
	for (int j = 1; j <= 9; ++j)
		Temp += Map[i][j] * Value[i][j];
	Ans = MAX(Temp, Ans);
}

int Dfs(int step)      //深度优先搜索
{
	if (step == QLen)
	{
		Score();
		return 0;
	}
	if (!Map[QueR[step]][QueC[step]])
	{
		for (int k = 1; k <= 9; ++k)
		{
			if (!Nine[belong(QueR[step], QueC[step])][k])
			{
				if (!Row[QueR[step]][k] && !Col[QueC[step]][k])
				{
					Map[QueR[step]][QueC[step]] = k;
					Nine[belong(QueR[step], QueC[step])][k] = 1;
					Row[QueR[step]][k] = Col[QueC[step]][k] = 1;
					Row[QueR[step]][0]++; 
					Col[QueC[step]][0]++;
					Dfs(step + 1);
					Map[QueR[step]][QueC[step]] = 0;
					Nine[belong(QueR[step], QueC[step])][k] = 0;
					Row[QueR[step]][k] = Col[QueC[step]][k] = 0;
					Row[QueR[step]][0]--;
					Col[QueC[step]][0]--;
				}
			}
		}
	}
}

void input()
{
	for (int i = 1; i <= 5; ++i)		//系数矩阵初始化
	{
		for (int j = i; j <= 9 - (i - 1); ++j)
		{
			Value[i][j] = 6 + (i - 1);
			Value[9 - (i - 1)][j] = 6 + (i - 1);
			Value[j][9 - (i - 1)] = 6 + (i - 1);
			Value[j][i] = 6 + (i - 1);
		}
	}
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			scanf("%d", &Map[i][j]);
			if (Map[i][j] != 0)
			{
				Row[i][Map[i][j]] = 1;	//行上使用过的数字
				Row[i][0]++;			//行上使用过数字个数
				Col[j][Map[i][j]] = 1;
				Col[j][0]++;
				Nine[belong(i, j)][Map[i][j]] = 1;		//小九宫格包含的数字
			}
		}
	}
}

int main()
{
	input();
	Heu();
	Dfs(0);
	cout << Ans;
	return 0;
}
