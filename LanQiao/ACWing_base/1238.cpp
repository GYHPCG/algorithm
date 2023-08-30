#include <bits/stdc++.h>

using namespace std;
const int N = 100010;
#define x first
#define y second
#define PII pair<int, int>
bool str[N];
int cnt[N];
PII logs[N];
int n, d, k;

int main()
{
	  ios::sync_with_stdio(false);
	  cin.tie(0);
	  
	  cin >> n >> d >> k;
	  
	  for (int i = 0; i < n; ++i)
	  {
	  	cin >> logs[i].x >> logs[i].y;
	  }
	  sort(logs, logs + n);
	  for (int i = 0, j = 0; i < n; ++i)
	  {
		 int id = logs[i].y;
		 cnt[id]++;
		 
		 while(logs[i].x - logs[j].x >= d)
		 {
		 	cnt[logs[j].y]--;
		 	++j;
		 }
		 
		 if (cnt[id] >= k) str[id] = true;
		 
	  }
	  for (int i = 0; i < N; ++i)
	  {
	  	if (str[i]) cout << i << endl;
	  }
	  
	  return 0;
	
}
