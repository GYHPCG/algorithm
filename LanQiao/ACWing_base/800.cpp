#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, x;
int a[N], b[N];

int main()
{
	 ios::sync_with_stdio(false);
	 cin.tie(0);
	 
	 cin >> n >> m >> x;
	 
	 for (int i = 0; i < n; ++i) cin >> a[i];
	 
	 for (int i = 0; i < m; ++i) cin >> b[i];
	 
	 for (int i = 0, j = m - 1; i < n;)
	 {
		  while(b[j] > x - a[i]) --j;
		  while (b[j] < x - a[i]) ++i;
		  if (a[i] == x - b[j])
		  {
		  	//cout << a[i] << ' ' << b[j] << endl;
		  	cout << i << ' ' << j << endl;
		  	break;
		  }
		  
	 }
	 
	 return 0;
}
