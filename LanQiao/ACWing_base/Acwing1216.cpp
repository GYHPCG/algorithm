#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
//    int w, m, n;
//    cin >> w >> m >> n;
//    m --, n -- ;
//	/*
//	m 为楼层宽度， m和n为待计算的楼号
//	*/
//    int x1 = m / w, x2 = n / w;
//    int y1 = m % w, y2 = n % w;
//    if (x1 % 2) y1 = w - 1 - y1;
//    if (x2 % 2) y2 = w - 1 - y2;
//
//    cout << abs(x1 - x2) + abs(y1 - y2) << endl;
//	//cout << gcd(1, 2) << endl;
	int *p;
    void* ptr = (void*)&p; // 将 p 转换为 void 指针并取其地址
    int **pp = (int**)&ptr; // 将 ptr 转换回指向指向整数的指针的指针
    *pp = new int(42); // 动态分配一个整数并将其地址存储在 p 中
    cout << *p << endl; // 输出 42
    return 0;
}
