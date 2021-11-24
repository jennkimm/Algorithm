#include <string>
#include <vector>

using namespace std;

int max_cnt = 0;
int d_size;
int min_ctr = 5000;

void dfs(int cnt, int ctr, vector<bool> visited, vector<vector<int>> &dungeons) {
    if (ctr < min_ctr) {
        if (max_cnt < cnt)
            max_cnt = cnt;
        return;
    } else {
        for(int i = 0; i < d_size; ++i) {
            if (visited[i] == true)
                continue;
            else if ((dungeons[i][0] <= ctr) && (visited[i] == false)) {
                visited[i] = true;
                dfs(cnt + 1, ctr - dungeons[i][1], visited, dungeons);
                visited[i] = false;
            }
        }
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    d_size = dungeons.size();

    for(int i = 0; i < d_size; ++i) {
        if (dungeons[i][0] < min_ctr)
            min_ctr = dungeons[i][0];
    }

    // 완전탐색
    vector<bool> visited;
    visited.assign(d_size, false);

    dfs(0, k, visited, dungeons);
    answer = max_cnt;

    return answer;
}
