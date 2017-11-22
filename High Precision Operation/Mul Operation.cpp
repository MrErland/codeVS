/*
* A * B
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string add(string &a, const string &b)
{
	string res = '0' + a;
	int f = 0;
	int t, i, j, sz = res.size();
	for (i = a.size() - 1, j = b.size() - 1; j >= 0; i--, j--)
	{
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

string onemul(const string &a, const char &b)
{
	string res;
	int  s = 0, t = b - '0';
	int f = 0, g = 0;
	for (int i = a.size() - 1; i >= 0; i--)
	{		
		res += ('0' + f);
		f = (a[i]-'0') * t / 10;
		g = (a[i]-'0') * t % 10;
		if (res[s] - '0' + g >= 10)
		{
			f++;
			res[s] = res[s] + g - 10;
		}
		else
		{
			res[s] += g;
		}
		s++;
	}
	if (f)
		res += ('0' + f);
	reverse(res.begin(), res.end());
	return res;
}

string& mul(const string &a, const string &b)
{
	static string res, temp;
	int j;
	for (j = b.size() - 1; j >= 0; j--)
	{
		string s(b.size() - 1 - j, '0');
		temp = onemul(a, b[j]);
		temp += s;
		if (temp.size() > res.size())
			res = add(temp, res);
		else
			res = add(res, temp);
	}
	return res;
}

int main()
{
	string a, b;
	cin >> a >> b;
	string res;
	if (a.size() > b.size() || (a.size() == b.size() && a > b))
		res = mul(a, b);
	else
		res = mul(b, a);
	cout << res;
	return 0;
}
