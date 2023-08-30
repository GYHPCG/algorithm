#include <iostream>
#include <algorithm>
using namespace std;


const int N = 1e7 + 8;
int n, m;
int a[N];
void arr_right()
{
	 m = m % n;
	 reverse(a, a + n);
	 reverse(a, a + m);
	 reverse(a + m, a + n);
}
int main()
{
	cin >> n >> m;
	
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	arr_right();
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << ' ';
	}
	return 0;
}
