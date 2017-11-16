/*
*问题描述:若某个家族人员过于庞大，要判断两个是否是亲戚，确实还很不容易，现在给出某个亲戚关系图，求任意给出的两个人是否具有亲戚关系。 
*规定：x和y是亲戚，y和z是亲戚，那么x和z也是亲戚。如果x,y是亲戚，那么x的亲戚都是y的亲戚，y的亲戚也都是x的亲戚。
*输入说明:第一行：三个整数n,m,p，（n<=5000,m<=5000,p<=5000），分别表示有n个人，m个亲戚关系，询问p对亲戚关系。 
*以下m行：每行两个数Mi，Mj，1<=Mi，Mj<=N，表示Ai和Bi具有亲戚关系。 接下来p行：每行两个数Pi，Pj，询问Pi和Pj是否具有亲戚关系。
*输出：P行，每行一个’Yes’或’No’。表示第i个询问的答案为“具有”或“不具有”亲戚关系。
*/


#include <cstdio>
using namespace std;
int N, M, P;
int f[5005];

int fatr(int a)
{
	while (f[a] != a)
		a = f[a];
	return f[a];
}

void merge(int a, int b)
{
	int fa, fb;
	fa = fatr(a);
	fb = fatr(b);
	if (fa == fb)
		return;
	f[fa] = fb;                       //注意这个f[fa]
	for (int i = 1; i <= N; i++)			//重新扫描所有点，f[a]为a根节点
	{
		int t = i;
		while (f[i] != i)
		{
			i = f[i];
		}
		f[t] = i;
		i = t;
	}
}

int main()
{
	scanf("%d%d%d", &N, &M, &P);
	for (int i = 0; i <= N; i++)
		f[i] = i;
	int a, b;
	for (int i = 1; i <= M; i++)
	{
		scanf("%d%d", &a, &b);
		if (f[a] == f[b])
			continue;
		merge(a, b);
	}
	for (int i = 0; i < P; i++)
	{
		scanf("%d%d", &a, &b);
		if (f[a] == f[b])
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
