/*
function:输入两个字符串，第二个字符串在第一个中第一次出现的位置
by:Erland
date:2017.6.22
*/

#include <iostream>
#define N 1000
using namespace std;

int main()
{
	int i, j = 0, t = NULL;
	char a[N];
	char b[N];
	cin >> a >> b;
	
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == b[j])
		{
			for (j = 1; b[j] != '\0';j++)
				if (a[i + j] != b[j])			
					break;			
		}
		if (b[j] == '\0') break;
	}
	if (a[i] != '\0')
		cout << i + 1 << endl;
	else
		cout << "No Answers." << endl;

	return 0;
}
