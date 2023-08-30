 #include <iostream>
 
 using namespace std;
 int n, m;
 const int N = 1e5 + 10;
 int a[N], b[N];
 int main()
 {
 	ios::sync_with_stdio(false);
 	cin.tie(nullptr);
 	
 	cin >> n >> m;
 	
 	for (int i = 0; i < n; ++i) cin >> a[i];
 	for (int j = 0; j < m; ++j) cin >> b[j];
 	
 	int i = 0, j = 0;
 	while(i < n && j < m)
 	{
		if (a[i] == b[j])
		{
			++i, ++j;
		}
		else ++j;
	}
 	
 	if (i < n) cout << "No" << endl;
 	else cout << "Yes" << endl;
 	return 0;
 }
