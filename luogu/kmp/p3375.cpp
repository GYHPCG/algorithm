/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-10 16:24:28
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-10 16:45:45
 */
#include <iostream>

using namespace std;

void getNext(int* next, const string s2) {
    int j = 0;
    next[0] = 0;
    for (int i = 1; i < s2.size(); ++i) {
        while( j > 0 && s2[i] != s2[j]) j = next[j-1];
        if (s2[i] == s2[j]) ++j;
        next[i] = j;
    }
}
void printNext(int* next, int n) {
    for (int i = 0; i < n; ++i) {
        cout << next[i] << " ";
    }
}
int main()
{
    string s1;//主串
    string s2;//模式串
    cin >> s1;
    cin >> s2;
    int n = s2.size();
    int next[n] = {0};
    //获取next数组
    getNext(next,s2);
    int j = 0;
    for (int i = 0; i < s1.size(); ++i) {
        while(j > 0 && s1[i] != s2[j]) j = next[j-1];
        if (s1[i] == s2[j]) ++j;
        if (j == n) {
            cout << (i - n + 2) << endl;
        }
    }
    printNext(next,n);
    return 0;

}
