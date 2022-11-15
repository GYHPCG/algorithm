/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-08-09 19:37:17
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-24 17:44:40
 */
#include <iostream>

using namespace std;
void quickSort(int arr[], int i, int j);
int main()
{
    int arr[10] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};

    quickSort(arr, 0, 9);
    for (int x : arr)
        cout << x << ", ";
    return 0;
}
void quickSort(int arr[], int i, int j)
{

    int st = i + 1; // arr[i]作为基准数
    int baesNum = arr[i];
    int end = j;
    if ( st > end) {
        return;
    }
    //左边找比基准数大的数，右边找比基准数小的数，然后交换位置，完成第一轮排序
    //下面的算法，要先右后左，否则有问题important
    while (st != end)
    {
         // right
        while (1)
        {
            if (end <= st || arr[end] < baesNum)
            {
                break;
            }

            end--;
        }
       
        // left
        while (1)
        {
            if (end <= st || arr[st] > baesNum)
            {
                break;
            }

            st++;
        }
     // swap;
        swap(arr[st], arr[end]);
    }   
    //基准数归位
    swap(arr[i], arr[end]);

    //分别递归左边和右边
    quickSort(arr,i,st-1);
    quickSort(arr,st+1,j);
}
