/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-11 11:08:04
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-11 11:36:23
 */
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;//{"I am a student"};
    
    getline(cin,s);
    
    //reverse(s.begin(),s.end()) ;
    //cout << s << endl;
    //delete [] c;
    for(int i = s.size() - 1; i >= 0; --i) {
        cout << s[i];
    }
    return 0;
}