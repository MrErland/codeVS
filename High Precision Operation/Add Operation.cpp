/*
* A + B (500length)
*/


#include <iostream>
#include <string>
using namespace std;

string add(string &a, const string &b)
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

int main()
{
	string a, b;
	cin >> a >> b;
	string res;
	if (a.size() >= b.size())
		res = add(a, b);
	else
		res = add(b, a);
	cout << res;
	return 0;
}
