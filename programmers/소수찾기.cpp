#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

bool isPrime(int n) {
	int m = 0;
	if (n < 0)
		return false;
	for(int i = 1; i <= n; i++) {
		if (n % i == 0) {
			m++;
		}
	}
	if (m == 2)
		return true;
	else
		return false;
}

int solution(string numbers) {
    int answer = 0;
	set<int> s;
	sort(numbers.begin(), numbers.end());
	int len = numbers.length();

	for (int l = 1; l <= len; l++) {
		vector<bool> v(len - l, false);
		v.insert(v.end(), l, true);
		do {
			string t = "";
			for (int k = 0; k < len; k++) {
				if (v[k])
					t += numbers[k];
			}
			do {
				string p;
				int n;
			 	bool isZero = false;
			 	bool isZeroFinish = false;
				for(auto tit = t.begin(); tit != t.end(); tit++) {
					if (tit == t.begin() && *tit == '0') { // 처음이고, 0이다
						isZero = true;
						continue;
					}
					else if (isZero == true && *tit == '0') // 0이었고, 0이다.
						continue;
					else if (isZero == true && *tit != '0') // 0이었는데 0이 아니다.
						isZero = false;
					p.append(1, *tit);
				}
				if (p != "") {
					n = stoi(p);
					if(isPrime(n)) {
						cout << p << endl;
						if (s.size() == 0 || s.find(n) == s.end())
						{
							s.insert(n);
							answer++;
						}
					}
				}
			} while (next_permutation(t.begin(), t.end()));
		} while(next_permutation(v.begin(), v.end()));
	}
	return answer;
}

int main() {
	cout << solution("17") << endl;
}
