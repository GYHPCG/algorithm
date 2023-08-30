#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
int get_time(int h, int m, int s)
{
	return h * 3600 + m * 60 + s;
}
int get_seconds()
{
	string line;
	
	getline(cin, line);
	if (line.back() != ')') line += "(+0)";
	int h1, m1, s1, h2, m2, s2, d;
	sscanf(line.c_str(), "%d:%d:%d %d:%d:%d (+%d)", &h1, &m1, &s1, &h2, &m2, &s2, &d);
	
	return get_time(h2, m2, s2) - get_time(h1, m1, s1) + d * 24 * 3600;
	
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int t;
	
	cin >> t;
	
	while(t --)
	{
		
		int time = (get_seconds() + get_seconds()) / 2;
		
		int hour = time / 3600, minute = time % 3600 / 60, second = time % 60;
		
		printf("%02d:%02d:%02d\n", hour, minute, second);
	}
	
	return 0;
}
