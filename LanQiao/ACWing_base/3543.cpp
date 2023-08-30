 #include <iostream>
 
 using namespace std;
 const int N = 55;
 int a[N];
 int m;
 int get()
 {
 	int res = 0;
 	for (int i = 0; i < m; ++i)
 	{
		for (int j = 0; j < m; ++j)
		{
			for (int k = 0; k < m; ++k)
			{
				if (a[i] + a[j] == a[k]) ++res;
			}
		}
	}
	return res;
 }
 int main()
 {
	  ios::sync_with_stdio(false);
	  cin.tie(nullptr);
	  
	  int n;
	  cin >> n;
	  int res = 0;
	  while(n --)
	  {
		 cin >> m;
		 for (int i = 0; i < m; ++i) cin >> a[i];
		 
		  res += get();
	  	
	  }
	  
	  cout << res << endl;
	  return 0;
 }
