#include <bits/stdc++.h>

using namespace std;
const int N = 110;

int m[N][N], dis[N][N];
using PII = pair<int, int>;
int n, m1;


void bfs()
{
	  queue<PII> q;
	  q.push({0,0});
	  memset(dis, -1, sizeof dis);

	  dis[0][0] = 0;
	  
	  int dx[4] = {-1, 0 ,1, 0}, dy[4] = {0, -1, 0, 1};
	  
	  while(q.size())
	  {
			auto t = q.front();
			q.pop();
			
			for (int i = 0; i < 4; ++i)
			{
				int x = t.first + dx[i], y = t.second + dy[i];
				
				if (x >= 0 && x < n && y >= 0 && y < m1 && m[x][y] == 0 && dis[x][y] == -1)
				{
					dis[x][y] = dis[t.first][t.second] + 1;
					q.push({x, y});
				}
			}
	  }
	  //cout << q.size() << endl;
	  cout << dis[n - 1][m1 - 1] << endl;
	
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> m1;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m1; ++j)
		{
			cin >> m[i][j];
		}
		
	bfs();
	
	return 0;
}

