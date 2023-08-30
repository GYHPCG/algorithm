#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> constructMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    vector<int> nums(n * n);
    for (int i = 0; i < n * n; i++) {
        nums[i] = i + 1;
    }
    random_shuffle(nums.begin(), nums.end());
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = nums[index++];
        }
    }
    return matrix;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> matrix = constructMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
