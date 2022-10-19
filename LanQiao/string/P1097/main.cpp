#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int n = 0;
    cin >> n;
    int j = 0;
    int  k = 1;
    int mk = 1;
    for (int i = n; i >= 1; --i) {
           k += j;
           j++;
           int lk = k;
           int zk = mk;
           mk++;
        for (int t = 1; t <= i-1; ++t) {

            printf("%d ",lk);
            zk++;
            lk += zk;
        }
        printf("%d\n",lk);
    }
    return 0;
}
