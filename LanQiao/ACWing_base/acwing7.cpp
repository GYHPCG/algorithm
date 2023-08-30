#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100010;

int n, m;
int w[N];
vector<int> g[N];
int ans;

int dfs(int u, int fa, int cnt)
{
    if (w[u]) cnt ++ ;
    else cnt = 0;

    if (cnt > m) return 0;

    int leaf = 1;
    for (auto v : g[u])
        if (v != fa)
        {
            leaf = 0;
            ans += dfs(v, u, cnt);
        }

    return leaf;
}

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i ++ ) cin >> w[i];

    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1, 0);

    cout << ans << endl;

    return 0;
}
