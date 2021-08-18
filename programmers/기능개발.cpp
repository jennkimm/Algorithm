#include <string.h>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	stack<int> remain_days_for_release;
	vector<int> answer;
	int front;
	int ans = 0;

	for(int i = progresses.size()-1;  i >= 0; i--) {
		int temp = (100 - progresses[i]) / speeds[i];
		int modulo = (100 - progresses[i]) % speeds[i];
		if (modulo > 0)
			temp += 1;
		remain_days_for_release.push(temp);
	}

	front = remain_days_for_release.top();
	while(!remain_days_for_release.empty()) {
		int current = remain_days_for_release.top();
		if (front >= current) { // 현재 값보다 크거나 같으면 answer++
			ans++;
			remain_days_for_release.pop();
		}
		else { // 현재 값보다 작으면 answer 백터에 answer을 push 하고 front 업데이트
			answer.push_back(ans);
			ans = 0;
			front = remain_days_for_release.top();
		}
	}
	if (ans > 0)
		answer.push_back(ans);
    return answer;
}

/*
다른 사람 풀이, 반복문 한개로 끝낸 코드 참고
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int day;
    int max_day = 0;
    for (int i = 0; i < progresses.size(); ++i)
    {
        day = (99 - progresses[i]) / speeds[i] + 1;

        if (answer.empty() || max_day < day)
            answer.push_back(1);
        else
            ++answer.back();

        if (max_day < day)
            max_day = day;
    }

    return answer;
}
*/

int main() {
	vector<int> progresses = {95};
	vector<int> speeds = {4};

	vector<int> answer;
	answer = solution(progresses, speeds);

	for(int i = 0; i < answer.size(); i++) {
		printf("%d\n", answer[i]);
	}
	return 0;
}
