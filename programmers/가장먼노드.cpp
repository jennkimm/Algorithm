#include <string>
#include <vector>
#include <queue>

using namespace std;

const int INF = 20001;

/**
 * 다익스트라 알고리즘 이용 -> 한 정점에 대해서 모든 노드 최단 거리 구하기.
 * 우선순위큐를 이용하면 O(ElogV) 만에 해결할 수 있다.
**/
void dijkstra(vector<vector<pair<int, int>>> v, vector<int> &dist) {
    priority_queue<pair<int, int>> pq;

    for(int i = 0; i < v[1].size(); ++i) {
        pq.push({v[1][i].first, 1});
        dist[v[1][i].first] = 1;
    }

    while(!pq.empty()) {
        int cur = pq.top().first;
        int cur_dist = pq.top().second;
        pq.pop();

        for(int i = 0; i < v[cur].size(); ++i) {
            if (dist[v[cur][i].first] > cur_dist + 1)
            {
                pq.push({v[cur][i].first, cur_dist + 1});
                dist[v[cur][i].first] = cur_dist + 1;
            }
        }
    }
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;

    vector<vector<pair<int, int>>> v(n + 1, vector<pair<int, int>>());

    for(int i = 0; i < edge.size(); ++i) {
        v[edge[i][0]].push_back({edge[i][1], 0});
        v[edge[i][1]].push_back({edge[i][0], 0});
    }

    vector<int> dist(n + 1, INF);

    dijkstra(v, dist);

    int max = 0;
    for(int i = 2; i < dist.size(); ++i) {
        if (dist[i] > max)
            max = dist[i];
    }
    for(int i = 2; i < dist.size(); ++i) {
        if (dist[i] == max)
           answer++;
    }

    return answer;
}
