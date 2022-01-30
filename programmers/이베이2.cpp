#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

string max_s = "";
int max_len = 999999;

bool isFinish(vector<int> &v, int k) {
	bool flag = false;
	for(int i = 0; i < v.size(); ++i) {
		if (v[i] == 0) {
			continue;
		} else if (v[i] == k) {
			if (flag == false) {
				flag = true;
				continue;
			}
			else
				return false;
		} else {
			return false;
		}
	}
	return true;
}

bool isRemovable(vector<int> &v, int remove_idx) {
	for(int i = 0; i < v.size(); ++i) {
		if (i != remove_idx && v[i] == 0)
			return false;
		else
			continue;
	}
	return true;
}

void dfs(vector<int> &curr_st, string s, int k) {
	if(isFinish(curr_st, k)) {
		printf("finish!!!\n");
		for(int j = 0; j < curr_st.size(); ++j) {
			printf("%d ", curr_st[j]);
		}
		printf("\n");
		// s를 그 전 s와 크기 비교.
		if (max_len > s.length()) {
			max_len = s.length();
		} else if (max_len == s.length()) {
			if (max_s < s)
				max_s = s;
		}
		return;
	} else if (s.length() >= max_len) {
        return;
    } else {
		for(int i = 0; i < curr_st.size(); ++i) {
			if (isRemovable(curr_st, i)) {
				printf("%d 번째 돌무더기에 추가\n", i);
				// 돌 +- 하고
				vector<int> new_v;
				new_v.assign(curr_st.size(), 0);
				for(int j = 0; j < curr_st.size(); ++j) {
					if (j == i)
						new_v[j] = curr_st[j] + 1;
					else
						new_v[j] = curr_st[j] - 1;
				}
				printf("원래는 => ");
				for(int j = 0; j < curr_st.size(); ++j) {
					printf("%d ", curr_st[j]);
				}
				printf("지금은 => ");
				for(int j = 0; j < curr_st.size(); ++j) {
					printf("%d ", new_v[j]);
				}
				printf("\n s ");
				// s 에 인덱스 추가하기
				string new_s = s + to_string(i);
				cout << "원래는 " << s << " 지금은 " << new_s << "\n";
				dfs(new_v, new_s, k);
				// s 복구하기
			}
		}
	}
}

string solution(vector<int> stones, int k) {
	string answer = "";

	printf("%lu\n", stones.size());
	dfs(stones, "", k);

	if (max_s == "")
		answer = "-1";
	else
		answer = max_s;

	return answer;
}

int main() {
	vector<int> stones = {1, 3, 2};
	string ans = solution(stones, 3);

	cout << ans << "\n";

	return 0;
}
