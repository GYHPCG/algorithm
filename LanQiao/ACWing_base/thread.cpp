#include <iostream>
#include <thread>

void increment(int* a_ptr) {
	for (int i = 0; i <= 5000000; ++i)
	{
		++*a_ptr;
	}
}

int main() {
    int a = 0;

    std::thread th1(increment, &a);
    std::thread th2(increment, &a);

    th1.join();
    th2.join();

    std::cout << "a = " << a << '\n';
}
