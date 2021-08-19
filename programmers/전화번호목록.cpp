#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool solution(vector<string> phone_book) {
	sort(phone_book.begin(), phone_book.end());
	for(int i = 0; i < phone_book.size() - 1; ++i) {
		if (phone_book[i + 1].find(phone_book[i]) == 0) {
			answer = false;
			break;
		}
	}
	return answer;
}

// 해시 셋으로 풀기
/* bool solution(vector<string> phone_book) {
	bool answer = true;
	unordered_set<string> s;
	for(int i = 0; i < phone_book.size(); i++) {
		s.insert(phone_book[i]);
	}
	for(int i = 0; i < phone_book.size(); i++) {
		string base = "";
		for(int j = 0; j < phone_book[i].length() - 1; j++) {
			base += phone_book[i][j];
			if (s.find(base) != s.end()) { // found
				return false;
			}
		}
	}
	return true;
} */

int main() {
	vector<string> phone_book = {"123","456","789"};
	bool ans = solution(phone_book);
	printf("%s\n", ans ? "true" : "false");
	return 0;
}
