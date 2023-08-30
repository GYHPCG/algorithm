/*
 * @Descripttion: my code for learning
 * @Author: chenggong Pan
 * @Date: 2023-08-13 13:36:28
 * @LastEditors: chenggong Pan
 * @LastEditTime: 2023-08-13 14:45:37
 */
#include<bits/stdc++.h> 

using namespace std;
int p, q, n1, n2, n3;
int main( )
{
    cin >> p >> q >> n1 >> n2 >> n3;
    
     int n3_c, n2_c;
     int n1_c = p - n3_c - n2_c;
      
     int ma = 0, mi = 1e5;
     bool t = false;
     int cnt = 0;
     for (int n3_c = p; n3_c >= 0;  n3_c --) {
        for (int n2_c = 0; n2_c <= p; n2_c++) {
           n1_c = p - n3_c - n2_c;
           if (n3_c * n3 + n2_c * n2 + n1_c * n1 == q && n1_c >= 0) {
                cnt++;
                if (cnt == 1) ma = n3_c;
                mi = n3_c;
                t = true;
              
           }
        }
     }
    if (t == false) cout << -1 << endl;
    cout << ma << ' ' << mi << endl;
    return 0;
}