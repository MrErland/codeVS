/*
*问题描述：给出两个正整数A和B，计算A/B整数部分的值。保证A和B的位数不超过500位。
*输入说明：读入两个用空格隔开的正整数
*输出：输出A/B整数部分的值
*/


#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string add(const string &a, const string &b)
{
	string res = '0' + a;
	int f = 0;
	int s, t, i, j, sz = res.size();
	for (i = a.size() - 1, j = b.size() - 1; j >= 0; i--, j--)
	{
		s = a[i] - '0';
		t = b[j] - '0';
		sz--;
		if (f)
		{
			if (res[sz] == '9')
			{
				res[sz] = '0';
				f = 1;
			}
			else
			{
				res[sz]++;
				f = 0;
			}
		}
		if (res[sz] - '0' + t >= 10)
		{
			res[sz] = (res[sz] - '0' + t) % 10 + '0';
			f = 1;
		}
		else
		{
			res[sz] = res[sz] + t;
		}
	}
	while (f)
	{
		sz--;
		if (res[sz] == '9')
		{
			res[sz] = '0';
			f = 1;
		}
		else
		{
			res[sz]++;
			f = 0;
		}
	}
	if (res[0] == '0')
		res.erase(res.begin(), res.begin() + 1);
	return res;
}

string sub(string a, string b)
{
	int la = a.length();
	int lb = b.length();
	if (la < lb || (la == lb && a < b))			//没考虑负数
		return "";
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int carry = 0;
	string c;
	int i;
	for (i = 0; i < la && i < lb; i++)
	{
		int ai = a[i] - '0';
		int bi = b[i] - '0';
		int ci = ai - bi - carry;
		if (ci < 0)
		{
			ci += 10;
			carry = 1;
		}
		else
			carry = 0;
		c += (ci % 10) + '0';
	}
	for (; i < la; i++)
	{
		int ai = a[i] - '0';
		int ci = ai - carry;
		if (ci < 0)
		{
			ci += 10;
			carry = 1;
		}
		else
			carry = 0;
		c += (ci % 10) + '0';
	}
	int lc = c.length();
	for (i = c.length() - 1; i >= 0; i--)
	{
		if (c[i] == '0') lc--;
		else break;
	}
	if (lc == 0) return "";
	c = c.substr(0, lc);
	reverse(c.begin(), c.end());
	return c;
}


string div(string &a, string &b)
{
	int la = a.length();
	int lb = b.length();
	if (la < lb || (la == lb && a < b))
		return "0";

	string bt[11];
	bt[0] = "";
	bt[1] = b;
	for (int i = 2; i <= 10; i++)
		bt[i] = add(bt[i - 1], bt[1]);
	
	int i = lb - 1;
	string c;
	string now = a.substr(0, lb);
	if (now < b)
	{
		now += a[++i];
	}
	for (; i < la; i++)
	{
		int ci;
		int lnow = now.length();
		for (ci = 1; ci <= 10; ci++)
		{
			int lbn = bt[ci].length();
			if (lbn > lnow || (lbn == lnow && bt[ci] > now))
				break;
		}
		ci--;
		c += ci + '0';
		now = sub(now, bt[ci]);
		if (i < la - 1)
		{
			if (now.size() == 0 && a[i + 1] == '0')
				continue;
			now += a[i + 1];
		}
	}
	return c;
}

int main()
{
	string a, b;
	cin >> a >> b;
	cout << div(a, b) << endl;
	return 0;
}
