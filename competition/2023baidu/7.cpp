/*
 * @Descripttion: my code for learning
 * @Author: chenggong Pan
 * @Date: 2023-08-13 13:37:09
 * @LastEditors: chenggong Pan
 * @LastEditTime: 2023-10-23 19:36:18
 */
#include <stdio.h>

int main()
{
    int n, i;
    float sum = 100, high = 50;
    scanf("%d", &n);
    for (i = 1; i < n; i++)
    {
        sum = sum + 2 * high;
        high = high / 2;
    }
    printf("%.4f %.4f", sum, high);

    return 0;
}