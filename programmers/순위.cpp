#include <string>
#include <deque>
#include <vector>
#include <stdio.h>

using namespace std;

/**
 * 플로이드-와샬 알고리즘 이용 - 모든 정점에서 모든 정점으로의 최단 경로 구할 수 있다 (거쳐가는 정점을 기준으로 DP)
 * O(V^3) 의 시간복잡도를 갖는다
**/

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<bool>> graph(n + 1, vector<bool>(n + 1, false));

    for(int i = 0; i < results.size(); ++i) {
        graph[results[i][0]][results[i][1]] = true;
    }

    // 플로이드 와샬 알고리즘
    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (graph[i][k] && graph[k][j]) {
                    graph[i][j] = true;
                }
            }
        }
    }

    // 승부를 결정하려면 n-1 개의 승패결과가 있어야 한다
    for(int i = 1; i <= n; ++i) {
        int count = 0;
        for(int j = 1; j <= n; ++j) {
            if (graph[j][i] || graph[i][j])
                count++;
        }
        if (count == (n - 1)) {
            answer++;
        }
    }

    return answer;
}
