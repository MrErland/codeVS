/*
*问题描述：动物王国中有三类动物 A,B,C，这三类动物的食物链构成了有趣的环形。A吃B，B吃C，C吃A。 　　
*现有N个动物，以1－N编号。每个动物都是A,B,C中的一种，但是我们并不知道它到底是哪一种。 　　
*有人用两种说法对这N个动物所构成的食物链关系进行描述： 　　
*第一种说法是“1 X Y”，表示X和Y是同类。第二种说法是“2 X Y”，表示X吃Y。 　　
*此人对N个动物，用上述两种说法，一句接一句地说K句话，当一句话满足下列三条之一时，这句话就是假话，否则就是真话。 　　
*1） 当前的话与前面的某些真的话冲突，就是假话； 　　
*2） 当前的话中X或Y比N大，就是假话； 　　
*3） 当前的话表示X吃X，就是假话。 　　
*你的任务是根据给定的N（1<=N<=50,000）和K句话（0<=K<=100,000），输出假话的总数。
*输入说明：第一行是两个整数N和K，以一个空格分隔。以下K行每行是三个正整数D，X，Y，两数之间用一个空格隔开，其中 D 表示说法的种类。 　　
*若D=1，则表示X和Y是同类。 　　若D=2，则表示X吃Y。
*输出：只有一个整数，表示假话的数目
*/


//参考代码
//https://www.cnblogs.com/shenben/p/5622288.html

#include<cstdio>
using namespace std;
int n, m, ans, fa[150005];				// fa[i] i表示这只动物是A，i+N表示B，i+2*N表示这只动物是C

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline void merge(int x, int y)
{
	fa[find(x)] = find(y);
}

inline bool same(int x, int y)
{
	return find(x) == find(y);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n * 3; i++) 
		fa[i] = i;
	for (int i = 1, x, y, z; i <= m; i++)
	{
		scanf("%d%d%d", &z, &x, &y);
		if (x > n || y > n)
		{ 
			ans++; 
			continue; 
		}
		if (z == 1)		// x y 同类
		{
			if (same(x, y + n) || same(x, y + n * 2))	// 如果有捕食关系
				ans++;
			else
				merge(x, y), merge(x + n, y + n), merge(x + n * 2, y + n * 2);
		}	
		else if (z == 2)	// x 吃 y
		{
			if (same(x, y) || same(x, y + n * 2))		// 如果 x,y 是同类, 或者 y 吃 x
				ans++;
			else
				merge(x, y + n), merge(x + n, y + n * 2), merge(x + n * 2, y);
		}
	}
	printf("%d\n", ans);
	return 0;
}
