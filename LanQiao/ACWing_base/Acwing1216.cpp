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
//	m Ϊ¥���ȣ� m��nΪ�������¥��
//	*/
//    int x1 = m / w, x2 = n / w;
//    int y1 = m % w, y2 = n % w;
//    if (x1 % 2) y1 = w - 1 - y1;
//    if (x2 % 2) y2 = w - 1 - y2;
//
//    cout << abs(x1 - x2) + abs(y1 - y2) << endl;
//	//cout << gcd(1, 2) << endl;
	int *p;
    void* ptr = (void*)&p; // �� p ת��Ϊ void ָ�벢ȡ���ַ
    int **pp = (int**)&ptr; // �� ptr ת����ָ��ָ��������ָ���ָ��
    *pp = new int(42); // ��̬����һ�������������ַ�洢�� p ��
    cout << *p << endl; // ��� 42
    return 0;
}
