#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 그리디
**/

int solution(vector<vector<int>> routes) {
    int answer = 0;

    sort(routes.begin(), routes.end());
    int base = -30001;

    for(int i = 0; i < routes.size(); ++i) {
        // 만약 전 꺼랑 겹치는 구간 있나?
        // 있다면 가만히
        // 없다면 answer + 1
        if (base < routes[i][0]) {
            answer++;
            base = routes[i][1];
        }
        if (base >= routes[i][1])
            	base = routes[i][1];
    }

    return answer;
}
