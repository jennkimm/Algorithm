#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
	sort(times.begin(), times.end());
	long long answer;
	long long left = 1;
	long long right = (long long)n * (long long)*times.crbegin();

	long long mid;
	answer = right; // answer 처음에 초기화
	while (left <= right) {
		mid = (left + right) / 2; // 시간
		long long max_people = 0;
		for (int i = 0; i < times.size(); i++) {
			max_people += mid / times[i];
		}
		if (max_people < n) {
			left = mid + 1;
		} else if (max_people > n) {
			right = mid - 1;
		}
		else {
			// max_people == n
			answer = mid;
			//answer = answer > mid ? mid : answer; // mid 가 answer 보다 작으면 mid 를 대입.
			right = mid - 1;
		}
		// max_people == n 이라도 바로 break; 시키면 안된다. -> 더 작을 경우도 있을 수 있음. right 와 left 가
		// 수렴할 때까지 계속 하자 그리고 answer을 계속 mid값으로 가져가야한다.
	}
	return answer;
}

int main() {
	int n = 6;
	vector<int> times = {2, 5, 6, 10}; // mid == 9 , mid == 8

	cout << solution(n, times) << endl;
}
