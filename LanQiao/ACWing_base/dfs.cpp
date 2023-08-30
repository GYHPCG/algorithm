#include <bits/stdc++.h>

using namespace std;
int path[10];
bool used[10];
int n;
void dfs(int u)
{
	if (u == n)
	{
		for (int i = 0; i < n; ++i) cout << path[i] << " ";
		cout << endl;
		return;
	}

	for (int i = 1; i <= n; ++i)
	{
		if (!used[i])
		{
			used[i] = true;
			path[u] = i;
			u++;
			dfs(u);
			u--;
			used[i] = false;
			path[u] = 0;
		}
	}
}
int main()
{
	  ios::sync_with_stdio(false);
	  cin.tie(0);
	  
	  cin >> n;
	  
	  dfs(0);
	  
	  return 0;
	  
}
