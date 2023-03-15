/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2023-01-03 22:19:51
 * @LastEditors: CGPan
 * @LastEditTime: 2023-01-03 22:19:56
 */
#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>

using namespace std;

const int N = 1000010;
int q[N];

int get(int x) {
    int sum = 0;
    while(x) {
        sum += x % 10;
        x = x / 10;
    }
    return sum;
}
bool com(int a, int b) {
   
   if (get(a) == get(b)) return a < b;
   else return get(a) < get(b);
   
}
int main()
{
    int n;
    //cin >> n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) q[i] = i + 1;
    
    sort(q, q + n,com);
    int m;
    //cin >> m;
    scanf("%d", &m);
    // for (int i = 0; i < n; ++i) cout << q[i] << " ";
    // cout << endl;
    
    //cout << q[m-1] << endl;
    printf("%d\n", q[m-1]);
    return 0;
}