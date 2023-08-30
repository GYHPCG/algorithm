#include <iostream>
#include <algorithm>
#include <string>
using namespace std;



string solve(string A, string B, int len)
{   //string A, B;
	int cntB_1 = 0, cntA_1 = 0;
	for (int i = 0; i < len; i++) {
		 if (B[i] == '1')cntB_1++;
		 if (A[i] == '1')cntA_1++;
	}
	string tmp;
	string res = "";

	if (cntA_1 >= cntB_1) {
		for (int i = 0; i < cntA_1; i++) tmp += '1';
		for (int i = 0; i < len - cntA_1; i++) tmp += '0';

		A = tmp;

		int cntB_0 = len - cntB_1;
		for (int i = 0; i < len; i++) {
			if (A[i] == '1' && cntB_0 != 0) {
				cntB_0--;
				res += '1';
			}
			else if (A[i] == '1' && cntB_0 == 0) {
				res += '0';
			}
			else if (A[i] == '0' && cntB_1 != 0) {
				cntB_1--;
				res += '1';
			}
			else if (A[i] == '0' && cntB_1 == 0) {
				res += '0';
			}
		}
	}
	else  {
		for (int i = 0; i < cntB_1; i++) tmp += '1';
		for (int i = 0; i < len - cntB_1; i++) tmp += '0';

		B = tmp;

		int cntA_0 = len - cntA_1;

		for (int i = 0; i < len; i++) {
			if (B[i] == '1' && cntA_0 != 0) {
				cntA_0--;
				res += '1';
			}
			else if (B[i] == '1' && cntA_0 == 0) {
				res += '0';
			}
			else if (B[i] == '0' && cntA_1 != 0) {
				cntA_1--;
				res += '1';
			}
			else if (B[i] == '0' && cntA_1 == 0) {
				res += '0';
			}
		}
	}

	return res;
}


int main()
{
	int n;
	cin >> n;
	string A, B;
	while(n --) {
		int len;
		cin >> len;
		cin >> A;
		cin >> B;

		cout << solve(A, B, len) << endl;
	}
}


