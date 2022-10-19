/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-17 17:18:37
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-17 18:19:14
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    string s;
    vector<string>Vec;
    cin.get();
    while(getline(cin,s)) {
        Vec.push_back(s);
    }
    // for (string K : Vec) {
    //     cout << K << endl;
    // }
    cout << "vec[0]: "<< Vec[0] << endl;
    for (int i = 0; i < Vec.size(); ++i) {
        if (i <= 2) {
            cout << Vec[i] << endl;
            cout << endl;
        } else {
                string m = Vec[i];
                string k;
            for (int j = 0; j < m.size(); ++j) {
                if (m[j] == ' ') {
                    cout << k << endl;
                    cout << endl;
                    k = "";
                } else {
                    k += m[j];
                }
                
            }
            cout << k << endl;
            cout << endl;
        }
       
    }
    return 0;

}
