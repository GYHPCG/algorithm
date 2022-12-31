/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-12-27 02:33:36
 * @LastEditors: CGPan
 * @LastEditTime: 2022-12-27 02:36:20
 */
#include <iostream>

using namespace std;

const int N = 100010;

int a[N], b[N];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
    int i = 0;
    for (int i = 0; i < n; ) {
        
        int j = i;
        
        while (b[j] != a[i] && j < m) {
            
            ++j;
        }
        
        if (j == m) {
            
            printf("No\n");
            
            break;
        }
        else ++i;
    }
    
    if(i == n) printf("Yes\n");
    
    return 0;
}