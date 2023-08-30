#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20;
int n, l, r, x, a[N];
int dfs(int u, int cnt, int sum, int mn, int mx)
{
    if (u == n) return cnt >= 2 && sum >= l && sum <= r && mx - mn >= x;
    return dfs(u + 1, cnt + 1, sum + a[u], min(mn, a[u]), max(mx, a[u])) + dfs(u + 1, cnt, sum, mn, mx);
}
int main()
{
    cin >> n >> l >> r >> x;
    for (int i = 0; i < n; i ++ ) cin >> a[i];
    cout << dfs(0, 0, 0, 1e9, 0) << endl;
    return 0;
}
