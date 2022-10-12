/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-11 10:18:16
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-11 11:04:06
 */
#include <iostream>
//有一头母牛，它每年年初生一头小母牛。每头小母牛从第四个年头开始，每年年初也生一头小母牛。请编程实现在第n年的时候，共有多少头母牛？
using namespace std;
long long Recursion( int n) {
    if (n <= 4) return n;
    return Recursion(n-3) + Recursion(n-1);
    
}

int main()
{

    int n;
    while(cin>>n && n != 0) cout << Recursion(n) << endl;   
    return 0;

}
