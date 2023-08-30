#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int n;
LL C(int a, int b)
{
	LL res = 1;;
	for (int i = a, j = 1; j <= b; ++j, i--)
	{
		res = res * i / j;
		if (res > n) return res;
	}
	return res;
}
bool check(int k)
{
	LL l = 2 * k, r = n;
	if (l > r) return false;
	while (l < r)
	{
		LL mid = l + r >> 1;
		if (C(mid, k) >= n) r = mid;
		else l = mid + 1;
	}
	if (C(r, k) != n) return false;
	cout << r * (r + 1) / 2 + k + 1;
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;

	for (int k = 16; ; k--)
	{
		if (check(k))break;
	}
	
	
	return 0;
}
