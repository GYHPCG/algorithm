#include <bits/stdc++.h>

using namespace std;

char path[10][10];
bool used[10][10];
int n;

bool check(int i, int j)
{
	//在同一行
	for (int k = 0; k < n; ++k)
	{
		if (path[i][k] == 'Q') return false;
	}
	//同一列
	for (int k = 0; k < n; ++k)
	{
		if (path[k][j] == 'Q') return false;
	}
	
	//45
	for (int r = i, c = j; r >= 0; r--, ++c)
	{
		if (path[r][c] == 'Q') return false;
	}
	for (int r = i, c = j; c >= 0; r++, --c)
	{
		if (path[r][c] == 'Q') return false;
	}
	for (int r = i, c = j; r >= 0; r--, --c)
	{
		if (path[r][c] == 'Q') return false;
	}
	for (int r = i, c = j; c < n; r++, c++)
	{
		if (path[r][c] == 'Q') return false;
	}
	return true;
	
	
}
int size = 0;
void dfs(int u)
{
	if (u == n)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << path[i][j];
			}
			cout << endl;
		}
		//cout << endl;
		size++;
		cout << endl;
		return;
	}
	for (int i = 0; i < n; ++i)
	{

		 	if (check(u, i) && !used[u][i])
		 	{
				  used[u][i] = true;
				  path[u][i] = 'Q';
				  dfs(u + 1);
				  path[u][i] = '.';
				  used[u][i] = false;
			}
	}
	
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			path[i][j] = '.';
   dfs(0);
   cout << size << endl;
   return 0;
	
}
