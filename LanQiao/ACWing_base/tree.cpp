#include <bits/stdc++.h>

using namespace std;

const int N = 10;
vector<int> e[N];

void dfs(int u, int fa)
{
	cout << "��: " << u << endl;
	for (auto v: e[u])
	{
		if (v == fa) continue;
		cout << "�£�" << u << endl;
		//cout << v << endl;
		dfs(v, u);
		
		cout << "�룺" << u << endl;
	}
	cout << "�أ�" << u << endl;
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
