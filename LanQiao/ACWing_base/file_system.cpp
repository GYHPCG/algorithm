#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> arr;
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++) {
		int num;
		cin >>  num;
		arr.push_back(num);
	}
	int x;
	cin >> x;
	
	int ans = -1;
	for (int i = 0 ;i < n; i++) {
		if (arr[i] == x) {
			  ans = i;
			  break;
		}
	}
	cout << ans << endl;
	
	return 0;
}
