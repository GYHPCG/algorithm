#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

vector<vector<int>> compat;
vector<vector<int>> un_compat;

void solve()
{
	
}
int main() {

    int m;
    string line;
    while (1) {
        cin >> m;
        getline(cin, line); // ����س���
        getline(cin, line); // �������������ĵ�һ��
        istringstream iss(line);
        int num;
        vector<int> vec;
        while (iss >> num) {
            vec.push_back(num);
        }
        compat.push_back(vec);

        getline(cin, line); // �������������ĵڶ���
        istringstream iss2(line);
        vec.clear(); // ��� vector
        while (iss2 >> num) {
            vec.push_back(num);
        }
        un_compat.push_back(vec);

        if (m == 12) break;
    }

//    cout << "---------------------" << endl;
//    for (int i = 0; i < compat.size(); ++i) {
//        for (int j = 0; j < compat[i].size(); ++j) {
//            cout << compat[i][j] << ' ';
//        }
//        cout << "\n";
//    }
//
//    cout << "*********************" << endl;
//    for (int i = 0; i < un_compat.size(); ++i) {
//        for (int j = 0; j < un_compat[i].size(); ++j) { // �����˴�������
//            cout << un_compat[i][j] << ' ';
//        }
//        cout << "\n";
//    }
	int n;
	cin >> n;
	int x, y;
	while(n -- )
	{
		cin >> x >> y;
		if (compat[x - 1][y - 1] || compat[y - 1][x- 1])
	}
    return 0;
}
