#include <bits/stdc++.h>

using namespace std;

using i64 =  long long;

void solve()
{
	i64 n;
    cin >> n;
    cout << ((n + 1) * n) + n + 2 << "\n";
}
int main() {
    i64 q;
    cin >> q;
    while (q--) {
		solve();
    }
    return 0;
}
