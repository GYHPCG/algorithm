#include <string>
using namespace std;
#include <algorithm>
#include<map>
#include <iostream>
std::string duplicate_encoder(const std::string& word) {
  int n = word.length();
  string k = word;
  transform(k.begin(),k.end(),k.begin(),::tolower);
  string s;
  unordered_map<char,int>mp;
  for (int i = 0; i < n; ++i) {
    ++mp[k[i]];
  }
  for (int i = 0; i < n; ++i) {
    if (mp[k[i]] == 1) {
      s += '(';
    } else {
      s += ')';
    }
  }
  return s;
}
int main()
{
    
    string k = "din";
    //k += '8';
    //cout << k ;
    cout << duplicate_encoder(k) << endl;
    return 0;

}
