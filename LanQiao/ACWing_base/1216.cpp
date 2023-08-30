#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int res = 0;
    while (n >= 3 )
    {

       n -= 3;
       res += 3;
       n++;
    }
    res += n;
    cout << res << endl;
    return 0;
}
