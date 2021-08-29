#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(string number, int k) {
    string answer = "";
	int target_len = number.length() - k;
	int base = 0;

	// k 개 제거해야함.
	// base ~ (number.length() - (target_len + answer.length()))
	while (answer.length() != target_len) {
		int temp;
		if (answer.length() == 0)
			temp = number[base];
		else
			temp = 0;
		int limit = (number.length() - (target_len - answer.length())) + 1;
		cout << base + 1 << "~" << limit << endl;
		for (int i = base + 1; i < limit; ++i) {
			if (number[i] > temp) {
				base = i;
				temp = number[base];
			}
		}
		cout << "base = " << base << endl;
		answer.append(1, number[base]);
	}
	return answer;
}

int main() {
	cout << solution("1000", 1);
}
