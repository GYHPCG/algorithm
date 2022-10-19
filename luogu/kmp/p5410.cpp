/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-14 12:01:56
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-14 12:39:19
 */
#include <iostream>
#include <string>
//扩展kmp(z函数)
using namespace std;
const int N = 2e7 + 5;
int z[N], p[N];
void get_z(string a) {
    int n = a.size();
    z[0] = n;
    for (int i = 1,l,r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(z[i-l],r-i);
        while(a[z[i]] == a[i+z[i]]) z[i]++;
        if (i + z[i] > r) l = i,r = i + z[i];
        //printf("i=%d z=%d [%d %d]\n",i,z[i],l,r);
    }
}
void get_p(string b, string a) {
    for (int i = 0,l,r = 0; i < a.size(); ++i) {
        if ( i <= r && i != 0) z[i] = min(z[i-1],r-i);
        while(z[z[i]] == b[i+z[i]] && p[i] < b.size() && i+p[i] < a.size())p[i]++;
        if (i+p[i] > r)l = i, p[i] = i+ p[i];
    }
}
int main()
{
    string a;
    string b;
    cin >> a;
    cin >> b;
    get_z(b);
    get_p(b,a);
    long long res1 = 0, res2 = 0;
    // for (int i = 0; i < b.size();++i) {
    //     //res1^= 1LL * i *(z[i]+1);
    //     //cout << z[i] << " ";
    // }
    for (int i = 0; i < a.size();++i) {
        // res2^= 1LL * i * (p[i]+1);
        cout << p[i] << " ";
    }
    // cout << res1 << endl << res2 << endl;
    return 0;

}
