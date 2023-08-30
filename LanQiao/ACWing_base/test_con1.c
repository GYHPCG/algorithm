#include <stdio.h>

void minmax(int a[], int len, int* p1, int* p2)
{
	*p1 = *p2 = a[0];
	for (int i = 0; i < len - 1; i++)
	{
		a[i] > a[i + 1]? (*p2 = a[i + 1]): (*p1 = a[i + 1]);
	}
}
int main()
{
	int a[5] = { 6, 3,4, 5, 1 };
	int len = 5;
	int ma, mi;
	minmax(a, sizeof(a) / sizeof(0), &ma, &mi);
	printf("%d %d\n", ma, mi);
	return 0;
}
