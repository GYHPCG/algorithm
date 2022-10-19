/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-15 16:07:51
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-16 17:05:36
 */
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;
[[noreturn]]
bool isPrime(int n) {
    for (int i = 2; i <= sqrt(n); ++i) {
        //if (n % i == 0) //return false;
    }
    //return true;
}
template<typename T>
struct fib
{
    /* data */
    T n;
     static_assert(is_integral<T>::value,"int");
     fib() = default;
};

int main()
{
    int n ;
    [[gnu::unused]]
    int b;
    
    cin >> n;
    //cout << isPrime(n);
    // double k;
    // fib n;
    for (int i = 2; i <= n; ++i) {
        if (isPrime(i) == true) {
            cout << i << endl;
        }
    }
    return 0;

}
