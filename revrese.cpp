#include <iostream>
#include <string>
using namespace std;
std::string reverse_words(std::string str)
{
    //std::string s = "";

  int j = 0;
  int n = str.size();
  for (int i = 0; i <= n; ++i) {
    if (str[i] == ' ' || i == n) {
        reverse(str.begin()+j,str.begin() + i);
        j = i + 1;
    }
  }
  return str;
}

int main()
{
    string s  ="abc lkj";
    //reverse(s.begin(),s.end());
    cout << reverse_words(s);
    return 0;

}
