// you can use includes, for example:
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

using namespace std;

vector<int> solution(vector<string> &S) {
    // write your code in C++14 (g++ 6.2.0)

	vector<int> ans;
	bool flag = false;
    for(int i = 0; i < S.size(); ++i) {
		for(int j = i + 1; j < S.size(); ++j) {
			// S[i], S[j] 비교
			for(int k = 0; k < S[i].length(); ++k) {
				printf("%d %d %d %d | %c %c\n", i, k, j, k, S[i][k], S[j][k]);
				if (S[i][k] == S[j][k]) {
					ans.push_back(i);
					ans.push_back(j);
					ans.push_back(k);
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
		if (flag)
			break;
	}
	return ans;
}
