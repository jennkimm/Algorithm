// you can use includes, for example:
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(int N) {
    // write your code in C++14 (g++ 6.2.0)
	vector<int> v;
	int ans;

	while(N > 0) {
		v.push_back(N % 10);
		N = N / 10;
	}

	if (v.size() >= 9)
	{
		return -1;
	} else {
		sort(v.begin(), v.end());
		for(int i = 1; i <= v.size(); ++i) {
			ans += (i * v[i - 1]);
		}
	}

	return ans;
}
