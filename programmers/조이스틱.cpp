#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(string name) {
    int answer = 0;
	int cnt = 1;
	string first;
	vector<bool> v(name.length() - 1, false);

	for(int i = 0; i < name.length(); i++) {
		first += 'A';
		if (name[i] == 'A') {
			v[i] = true;
		}
	}

	int cur_idx = 0;
	bool check = false;
	first[cur_idx] = name[cur_idx];
	while (first.compare(name) != 0) {
		// 앞으로 갈지 뒤로 갈지 결정
		int if_ap = 0;
		int if_dui = 0;
		if (check != true) {
			for (int i = cur_idx; i < name.length(); ++i) {
				if (first[i] != name[i])
					break;
				else
					if_ap++;
			}
		} else {
			for (int i = cur_idx; i > 0; --i) {
				if (first[i] != name[i])
					break;
				else
					if_ap++;
			}
		}
		if (check != true) {
			for (int j = name.length() - 1; j > cur_idx; --j) {
				if (first[j] != name[j]) {
					if_dui += cur_idx + 1;
					break;
				} else
					if_dui++;
			}
		}
		cur_idx = if_ap <= if_dui ? (cur_idx + if_ap) % name.length() : (name.length() - (if_dui - cur_idx)) % name.length();
		if (if_ap <= if_dui) {
			cnt += if_ap;
		} else if (check == true) {
			cur_idx = cur_idx - if_ap;
			cnt += if_ap;
		} else {
			check = true;
			cnt += if_dui;
		}
		first[cur_idx] = name[cur_idx];
	}

	for (int i = 0; i < name.length(); i++) {
		cnt += min((name[i] - 'A'), 'Z' - name[i] + 1);
	}

	answer = cnt - 1;
	return answer;
}

int main() {
	cout << solution("ZZAAAZZ") << endl;
}
