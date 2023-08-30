#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> st;
int n;

int get(string& s)
{
    int index = -1;
    for (int i = 0; i < st.size(); i ++ )
    {
        if (st[i] == s)
        {
            index = i;
            break;
        }
    }
    return index;
}

void replace(int index)
{
    for (int i = index; i < st.size() - 1; i ++ )
    {
        st[i] = st[i + 1];
    }
    st.pop_back();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string th;

    while(n--)
    {
        cin >> th;
        int index = get(th);
        if (index == -1)
        {
            st.push_back(th);
        }
        else if(index != -1)
        {
            replace(index);
            st.push_back(th);
        }

    }

   // cout << st.size() << endl;
    for (int i = st.size() - 1; i >= 0; i--)
    {
        cout << st[i] << endl;
    }
    return 0;

}

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> st;
    unordered_map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (mp.count(s)) {
            int idx = mp[s];
            st.erase(st.begin() + idx);
        }
        st.push_back(s);
        mp[s] = st.size() - 1;
    }

    for (int i = st.size() - 1; i >= 0; i--)
    {
        cout << st[i] << endl;
    }
    return 0;
}
