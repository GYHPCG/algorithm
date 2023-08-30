#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int N = 54;
int a[54], t[54], n, m;
vector<string> cards = {"S1", "S2", "S3",
         "S4", "S5", "S6",
         "S7", "S8", "S9",
         "S10", "S11", "S12",
         "S13",
         "H1", "H2", "H3",
         "H4", "H5", "H6",
         "H7", "H8", "H9",
         "H10", "H11", "H12",
         "H13",
         "C1", "C2", "C3",
         "C4", "C5", "C6",
         "C7", "C8", "C9",
         "C10", "C11", "C12",
         "C13",
         "D1", "D2", "D3",
         "D4", "D5", "D6",
         "D7", "D8", "D9",
         "D10", "D11", "D12",
         "D13",
         "J1", "J2"
		 };

void shuffle_machine()
{
	vector<string> tmp;
	for (int i = 0; i < cards.size(); ++i)
	{
		  tmp.push_back(cards[i]);
	}
	
	for (int i = 0; i < 54; ++i)
	{
		cards[a[i] - 1] = tmp[i];
	}
	
}
int main()
{
	 ios::sync_with_stdio(false);
	 cin.tie(nullptr);
	 
	 cin >> n;
	 
	 for (int i = 0; i < 54; ++i) cin >> a[i], t[i] = a[i];
	 
	 while (n --)
	 {
		  shuffle_machine();
	 }
	
	for (int i = 0; i < cards.size(); ++i)
	{
		cout << cards[i] << ' ';
	}
	return 0;
}

