#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

int a[N];
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    int res = a[1];
    while(1)
    {
        int t = res;
        for (int i = 1; i <= n; i ++ )
        {
            t = 2 * t - a[i];
            if (t < 0) break;
        }
        if (t >= 0) break;
        else ++res;
    }
    cout << res << endl;
    return 0;
}
