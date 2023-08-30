#include <bits/stdc++.h>

using namespace std;

const int N = 510;
int s[N][N];
int n, m , k;
using LL = long long;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	//auto l = 1;
	cin >> n >> m >> k;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
		   cin >> s[i][j];
		   s[i][j] += s[i - 1][j];
		}

	LL res = 0;
	LL sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; ++j)
		{
			 sum = 0;
			for (int l = 1, r = 1; r <= m; ++r)
			{
				 sum += s[j][r] - s[i - 1][r];
				 while (sum > k)
				 {
				 	sum -= s[j][l] - s[i - 1][l];
				 	l++;
				 }
				 res += r - l + 1;
			}
			
		}
		//cout << endl;
	}

	cout << res << endl;
	
	return 0;
}
