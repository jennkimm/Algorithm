#include <cstdio>
#include <iostream>
#include <string>
//#include<bits/stdc++.h>

using namespace std;

void solve()
{
	string s;
	cin >> s;

	int count = 0;
	int answer = 0;
	if (s.size() <= 3)
		cout << answer << endl;
	else {
		for(int i=0; i <= s.size()-4; i++)
		{
			if(s[i]=='K' && s[i+1]=='I' && s[i+2]=='C' && s[i+3]=='K')
    			count++;
			else if(i<=s.size()-5)
    			if(s[i]=='S' && s[i+1]=='T' && s[i+2]=='A' && s[i+3]=='R' && s[i+4]=='T')
        			answer += count;
		}
		cout << answer << endl;
	}
}

int main()
{
	int t;
	cin >> t;
	for(int i=1; i <= t; i++)
	{
		cout<< "Case #" << i << ": ";
		solve();
	}
}
