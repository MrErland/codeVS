/*
*A - B (500length)
*/

#include <iostream>
#include <string>
using namespace std;

string sub(string &a, const string &b, const unsigned int sza, const unsigned int szb)
{
	string res = a;
	bool f = false, g = false;			      //借位
	int t, i, j;
	for (i = sza - 1, j = szb - 1; j >= 0; i--, j--)
	{
		if (f)
		{
			if (a[i] >= '1' && a[i] <= '9')
			{
				a[i]--;
				f = false;
			}
			else if (a[i] == '0')
			{
				a[i] = '9';
				f = true;
			}
		}
		t = a[i] - b[j];
		if (t < 0)
		{
			t += 10;
			res[i] = ('0' + t);
			f = true;
		}
		else
		{
			res[i] = ('0' + t);
		}
	}
	if (f)
		res[i]--;
	return res;
}

int main()
{
	string a, b;
	cin >> a >> b;
	string res;
	if (a.size() > b.size() || (a.size() == b.size() && a > b))
	{
		res = sub(a, b, a.size(), b.size());
		for (int i = 0; res[i] == '0'; i = 0)
			res.erase(res.begin(), res.begin() + 1);
	}
	else if (b.size() > a.size() || (a.size() == b.size() && b > a))
	{
		res = sub(b, a, b.size(), a.size());
		for (int i = 0; res[i] == '0'; i = 0)
			res.erase(res.begin(), res.begin() + 1);
		string tem = "-";               //负号
		tem += res;
		res = tem;
	}
	cout << res;
	return 0;
}
