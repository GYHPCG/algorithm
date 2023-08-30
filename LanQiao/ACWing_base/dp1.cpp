#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
int n, m;
const int N = 2010;
int f[N];
struct good{
    int v, w;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<good> vec;

    cin >> n >> m;

    for (int i = 0; i < n; i ++ )
    {
        int v, w, s;
        cin >> v >> w >> s;
        for(int k = 1; k <= s; k *= 2)
        {
            s -= k;
            vec.push_back({k * v, k * w});

        }
        if (s > 0)
        {
            vec.push_back({s * v, s * w});
        }

    }

    for (auto t: vec)
    {
        for (int j = m; j >= t.v; --j)
        {
            f[j] = max(f[j], f[j - t.v] + t.w);
        }


    }
    cout << f[m] << endl;

    return 0;
}
