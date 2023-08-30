#include <bits/stdc++.h>

using namespace std;

using PII = pair<int, int>;
const int N = 1e5 + 10;

vector<PII> vec;
int n;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		 int x, y;
		 cin >> x >> y;
		 vec.push_back({x, y});
	}
	sort(vec.begin(), vec.end());
	
	
	int res = 1;
	int end = 0;
	for (int i = 1; i < n; ++i)
	{
		 auto t1 = vec[i], t2 = vec[i - 1];
		 
		 if (t1.first > t2.second)
		 {
			  ++res;
		 }
		 else {
		 	vec[i].second = min(t2.second, t1.second);
		 }
		
	}
	
	cout << res << endl;
	return 0;
}
