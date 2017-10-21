/*
*问题描述：单词接龙是一个与成语接龙相类似的游戏，已知一组单词，且给定一个开头的字母，要求出以这个字母开头的最长的“龙”（每个单词都最多在“龙”中出现两次）
*在两个单词相连时，其重合部分合为一部分，例如beast和astonish，如果接成一条龙则变为beastonish，另外相邻的两部分不能存在包含关系，例如at和atide间不能相连。
*输入说明：输入的第一行为一个单独的整数n(n<=20)表示单词数，以下n行每行有一个单词，输入的最后一行为一个单个字符，表示“龙”开头的字母
*输出：输出以此字母开头的最长的“龙”的长度。
*/



#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
using namespace std;
static int n;
string start;
set <string> ans;
vector <string> word;

void input()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> start;
		word.push_back(start);
		word.push_back(start);
	}
	cin >> start;
}

void output()
{
	size_t st = 0;
	for (set<string>::iterator a = ans.begin(); a != ans.end(); a++)
	{
		if ((*a).size() > st)
			st = (*a).size();
	}
	cout << st;
}

string ismerge(string s, string t)
{
	string::iterator i = s.end();
	string::iterator j = t.begin();
	while (i != s.begin() && j != t.end() - 1)			//注意两个完成相同字符串相连没有意义
	{
		i--;
		j++;
		string m(i, s.end());
		string n(t.begin(), j);
		if (m == n)
		{
			s.erase(i, s.end());
			s += t;
			return s;
		}
	}
	return "0";
}

void dfs(string s, vector <string> word)
{
	if (word.empty())
	{
		ans.insert(s);    //一条“龙”
		return;
	}
	bool f = 0;
	string tmp;
	for (size_t a = 0; a < word.size(); a++)
	{
		if ((tmp = ismerge(s, word[a])) != "0")
		{
			f = 1;
			vector <string> tword(word);			//产生一个拷贝，不能用原数组向下传递
			tword.erase(tword.begin() + a);
			dfs(tmp, tword);
		}
	}
	if (!f)
		ans.insert(s);		//一条“龙”
}

int main()
{
	input();
	dfs(start, word);
	output();
	return 0;
}
