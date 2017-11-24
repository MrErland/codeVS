/*
*问题描述：一个集合中的元素个数由给定的N决定，集合的元素为N个不同的正整数，一旦集合中的两个数x,y满足y = P*x，那么就认为x,y这两个数是互斥的
*现在想知道给定的一个集合的最大子集满足两两之间不互斥。
*输入说明：输入有多组数据，每组第一行给定两个数N和P（1<=N<=10^5, 1<=P<=10^9）。接下来一行包含N个不同正整数ai（1<=ai<=10^9）。
*输出：输出一行表示最大的满足要求的子集的元素个数。
*/


#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
	int n, p;
	while (scanf("%d%d", &n, &p) == 2)
	{
		set<int> s;
		int tmp[100000];
		int t;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &tmp[i]);	
		}
		sort(tmp, tmp + n);           //先排序，使元素从小到大排列
		for (int i = 0; i < n; i++)   //再把排序好的元素依次加入到hashset里
			s.insert(tmp[i]);
		for (set<int>::iterator i = s.begin(); i != s.end(); i++)
		{
			if (s.find((*i)*p) != s.end())      //采用删除x*p的数（较大的数）的原则
				s.erase((*i)*p);                  //因为采用元素从小到大，较大元素可能导致两个重复，而当前只会有一个重复
		}
		printf("%d\n", s.size());
	}
	return 0;
}
