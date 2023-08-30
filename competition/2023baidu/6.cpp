#include<iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
using PII = pair<int, int>;
int n;
vector<PII> vec;
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int p, v;
        cin >> p >> v;
        vec.push_back({p, v});
    }
    sort(vec.begin(), vec.end());
    priority_queue<PII> heap;
    heap.push({vec[0].second, vec[0].first});
    int cnt = 0;
    vector<int> count(n, 0);
    count[cnt] = 1;
    for (int i = 1; i < n; ++i) {
         auto t = heap.top();
         heap.pop();
         if (t.second > vec[i].second || t.first == vec[i].first) {
                if (t.first == vec[i].first)
                   heap.push({min(t.second, vec[i].second), t.first});
                if (t.second > vec[i].second) heap.push({vec[i].second, max(t.first,vec[i].first)});
                
                count[cnt]++;
         }
         else {
            heap.push({vec[i].second, vec[i].first});
            count[++cnt] = 1;
         }
    }
    
    int res = 0;

    for (int i = 0; i < n; ++i) {
        res = max(res, count[i]);
    }

    cout << res << endl;
    return 0;
}