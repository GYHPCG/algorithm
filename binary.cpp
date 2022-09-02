#include <iostream>

using namespace std;

int binary_search1(int arr[], int x) {
    //二分查找优化：插值排序
    int l = 0;
    int r = 9;
    
    while ( l <= r) {
        int mid = l + ( (x - arr[l]) / (arr[r] - arr[l])) * (r - l);

        if (arr[mid] > x) {
            r = mid - 1;
        }else if (arr[mid] < x) {
            l = mid + 1;
        }else {
            return mid;
        }
    }
    return -1;

}

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    //sort(arr.begin(),arr.end(),(o1,o2)->o1-o2);
    // int x = 5;
    // int index = binary_search1(arr,x);
    // cout << index << endl;
    return 0;
}
