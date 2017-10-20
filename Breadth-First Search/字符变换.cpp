/*问题描述：已知有两个字串 A$, B$ 及一组字串变换的规则（至多6个规则）:A1$ -> B1$、A2$ -> B2$
*规则的含义为：在 A＄中的子串 A1$ 可以变换为 B1$、A2$ 可以变换为 B2$ …。
*例如：A$＝'abcd'　B$＝'xyz' 变换规则为：‘abc’->‘xu’　‘ud’->‘y’　‘y’->‘yz’
*则此时，A$ 可以经过一系列的变换变为 B$，其变换的过程为：‘abcd’->‘xud’->‘xy’->‘xyz’ 共进行了三次变换，使得 A$ 变换为B$。
*输入说明：输入格式如下：所有字符串长度的上限为 20。
*      A$ B$
*      A1$ B1$ \
*      A2$ B2$  |-> 变换规则
*　　　... ... /
*输出：若在 10 步（包含 10步）以内能将 A$ 变换为 B$ ，则输出最少的变换步数；否则输出"NO ANSWER!"
*/


#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
using namespace std;
static string A, B;
static int i = 0;
static string rule[6][2];
set <string> S1, S2;

void over(int t)
{
	cout << t;
	exit(0);
}

bool isgoal(string s)
{
	if (s == B)
		return true;
	return false;
}

void bfs(set <string> &S1, set <string> &S2, int times)
{
	int st;
	string tmp, t, in;
	S2.clear();
	for (set<string>::iterator a = S1.begin(); a != S1.end(); a++)
	{
		t = *a;
		for (int j = 0; j < i; j++)
		{
			tmp = t;
			st = 0;
			while ((st = tmp.find(rule[j][0], st)) != string::npos)
			{
				in = tmp;
				in.replace(in.begin() + st, in.begin() + st + rule[j][0].size(), rule[j][1]);
				if (isgoal(in))
					over(times);
				S2.insert(in);
				st += rule[j][1].size();			//在找到第一个匹配后的，下一次查找的开始点。
			}
		}
	}
}

int main()
{
	cin >> A >> B;
	while (cin >> rule[i][0] >> rule[i][1])
		i++;
	if (A == B)
		over(0);
	S1.insert(A);
	for (int times = 1; times <= 10; times++)		//记录步数
	{
		if (times % 2 != 0)
			bfs(S1, S2, times);
		else
			bfs(S2, S1, times);
	}
	cout << "NO ANSWER!";
	return 0;
}
