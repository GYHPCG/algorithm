#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 101;

using PII = pair<int,int>;

int n, m;

int matrix[N][N], d[N][N];

int bfs()
{
    queue<PII> q;
    memset(d, -1, sizeof(d));
    q.push({0, 0});
    d[0][0] = 0;

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int x = t.first + dx[i], y = t.second + dy[i];

            if (x >= 0 && y >= 0 && x < n && y < m && matrix[x][y] == 0 && d[x][y] == -1)
            {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({x, y});
            }

        }

    }
    return d[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; ++j)
        {
            cin >> matrix[i][j];
        }

    cout << bfs() << endl;

    return 0;
}

