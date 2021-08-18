#include <string.h>
#include <vector>
#include <queue>

using namespace std;

struct cmp {
	bool operator()(int n1, int n2) {
		if (n1 > n2)
			return false;
		else if (n1 == n2)
			return false;
		else
			return true;
	}
};

int solution(vector<int> priorities, int location) {
	priority_queue<int, vector<int>, cmp> pq;
	queue<int> q;
	int max = priorities.front();
	int answer = 0;

	for(int i = 0; i < priorities.size(); i++) {
		pq.push(priorities[i]); // 중요도 순으로 정렬
		q.push(i);
	}

	while(!pq.empty()) {
		int cur = priorities.front();
		if (cur < pq.top()) { // 중요도 높은게 하나라도 있으면,
			priorities.push_back(cur);
			q.push(q.front());
			priorities.erase(priorities.begin());
			q.pop();
			for(int i = 0; i < priorities.size(); i++) {
				printf("%d ", priorities[i]);
			}
			printf("\n");
		}
		else if (cur == pq.top() && q.front() != location) { // pq.top() 이랑 같은데, location 은 아닐 경우
			priorities.erase(priorities.begin());
			q.pop();
			pq.pop();
			for(int i = 0; i < priorities.size(); i++) {
				printf("%d ", priorities[i]);
			}
			printf("\n");
			answer++;
		}
		else if (cur == pq.top() && q.front() == location) { // pq.top() 이랑 같고, location 일 경우
			answer++;
			break;
		}
	}
	return answer;
}

int main() {
	vector<int> v = {1, 4, 2, 3, 5, 1};
	int answer = solution(v, 0);
	printf("%d\n",answer);
	return 0;
}
