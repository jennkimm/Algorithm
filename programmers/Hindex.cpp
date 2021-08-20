#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
	sort(citations.begin(), citations.end());
	vector<int>::iterator it = citations.begin();
	for (int i = *(it + citations.size() - 1); i >= 0; i--) {
		// when (h-index == i)
		int under = 0;
		int over = 0;
		for (int j = 0; j < citations.size(); j++) {
			if (citations[j] >= i) // i 번 이상 인용
				over++;
			else // i 번 이하 인용
				under++;
		}
		if (over >= i) {
			answer = i;
			break;
		}
	}
	return answer;
}

int main() {
	vector<int> citations = {0, 1, 1};
	int ans = solution(citations);
	printf("%d\n", ans);
	return 0;
}
