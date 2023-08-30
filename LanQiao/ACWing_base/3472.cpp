#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    //cin >> n;
    int total;
    int mi = 0, ma = 0;
    //while (n -- )
    //{
        cin >> total;
        mi = 0, ma = 0;
        for (int i = total; i >= 0; i --)
        {
            if (i % 2 == 0 && (total - i) % 4 == 0)
            {
                mi = i / 2;
                break;
            }
        }
        for (int j = total; j >= 0; j--)
        {
            if (j % 4 == 0 && (total - j) % 2 == 0)
            {
                ma = j / 4;
                cout << "j: " << j << " yu: " << total - j << endl;
                break;
            }
        }

        cout << ma << ' ' << mi << endl;

    //}

    return 0;
}
