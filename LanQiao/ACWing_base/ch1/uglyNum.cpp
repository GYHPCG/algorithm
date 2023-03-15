/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2023-01-16 21:06:02
 * @LastEditors: CGPan
 * @LastEditTime: 2023-01-16 21:12:40
 */
#include <iostream>
#include <vector>
using namespace std;
vector<int> ugly;
bool get(int x) {
    while ( x != 1) {
        if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0) {
            if (x % 2 == 0) x /= 2;
            else if ( x % 3 == 0) x /= 3;
            else x /= 5;
        } else {
            return false;
        }
    }
    return true;
}
void getUgly(vector<int>& ugly) {
    ugly.emplace_back(1);
    for (int i = 2; i <= 10000; ++i)
    {
        if (get(i))
            ugly.emplace_back(i);
        else
            continue;
    }
}
int nthUglyNumber(int n) {
    //vector<int> ugly;
    getUgly(ugly);
    return ugly[n - 1];
}
int main()
{

    int n;
    cin >> n;
    ugly.clear();
    cout << nthUglyNumber(n);
    return 0;
}
