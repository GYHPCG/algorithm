#include <bits/stdc++.h>

using namespace std;

const int N = 10;
vector<int> e[N];

void dfs(int u, int fa)
{
	cout << "Èë: " << u << endl;
	for (auto v: e[u])
	{
		if (v == fa) continue;
		cout << "ÏÂ£º" << u << endl;
		//cout << v << endl;
		dfs(v, u);
		
		cout << "Àë£º" << u << endl;
	}
	cout << "»Ø£º" << u << endl;
}
int main()
{
	int n, m;
	
	cin >> n >> m;
	int a, b;
	for (int i = 1; i <= m; ++i)
	{
		 cin >> a >> b;
		 e[a].emplace_back(b);
		 e[b].emplace_back(a);
	}
	dfs(1, 0);
	
}
