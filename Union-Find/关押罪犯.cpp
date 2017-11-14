/*
*问题描述：S 城现有两座监狱，一共关押着N 名罪犯，编号分别为1~N。我们用“怨气值”（一个正整数值）来表示某两名罪犯之间的仇恨程度，怨气值越大，则这两名罪犯之间的积怨越多。
*如果两名怨气值为c 的罪犯被关押在同一监狱，他们俩之间会发生摩擦，造成影响力为c的冲突事件。
*每年警察局会将本年内监狱中的所有冲突事件按影响力从大到小排成一个列表，公务繁忙的Z市长只会去看列表中的第一个事件的影响力，如果影响很坏，他就会考虑撤换警察局长。
*在详细考察了N 名罪犯间的矛盾关系后，警察局长觉得压力巨大。他准备将罪犯们在监狱内重新分配，以求产生的冲突事件影响力都较小，从而保住自己的乌纱帽。
*假设只要处于同一监狱内的某两个罪犯间有仇恨，那么他们一定会在每年的某个时候发生摩擦。那么，应如何分配罪犯，才能使Z 市长看到的那个冲突事件的影响力最小？这个最小值是少？
*输入说明：第一行为两个正整数N 和M，分别表示罪犯的数目以及存在仇恨的罪犯对数。
*接下来的M 行每行为三个正整数aj，bj，cj，表示aj 号和bj 号罪犯之间存在仇恨，其怨气值为cj。数据保证，且每对罪犯组合只出现一次。
*输出：共1 行，为Z 市长看到的那个冲突事件的影响力。如果本年内监狱中未发生任何冲突事件，请输出0。
*/


#include <cstdio>
#include <algorithm>
using namespace std;
const int N_S = 20005;
const int M_S = 100005;
struct Connect{ int a; int b; int v; }con[M_S];
int N, M, per[N_S * 2] = { 0 };

int cmp(struct Connect a, struct Connect b)
{
	return a.v >= b.v;
}

int father(int x)
{
	while (per[x] != x)
		x = per[x];
	return per[x];
}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++)
		scanf("%d%d%d", &con[i].a, &con[i].b, &con[i].v);
	sort(con, con + M, cmp);
	for (int i = 0; i < 2 * N_S; i++)
		per[i] = i;
	for (int i = 0; i < M; i++)
	{
		int a, b;
		a = father(con[i].a);
		b = father(con[i].b);
		if (a != b)
		{
			per[a] = father(con[i].b + N);
			per[b] = father(con[i].a + N);
		}
		else{
			printf("%d\n", con[i].v);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
