#include <iostream>

using namespace std;

int main()
{
    int i = 2, j = 1;
    //静态转换
    double slope = static_cast<double>(j) / i;
    cout << slope << endl;//0.5
    // const_cast转换的类型必须是指针，引用或者对象类型成员的指针
    //只能修改const,类型转换不能做到
    const int k = 3;
    const int *p = &k;
    int *pk = const_cast<int *>(p);
    *pk = 7;//可以使得小权限可以赋值给大权限
    cout << "const_cast: " << *pk << endl;//7
    //reinterpret_cast重新修改读取规则
    int p1 = 97;
    int* pc = &p1;
    char* ipc = reinterpret_cast<char*>(pc);
    cout << *ipc << endl;//a
    return 0;
}
