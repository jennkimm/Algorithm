#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> map;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
vector<pair<int, int>> two_loc;
int n, m;
int ans = 0;

int bfs(vector<vector<int>> map) {
	queue<pair<int, int>> q;
	int result = 0;
	for(int i = 0; i < two_loc.size(); ++i) {
		q.push(make_pair(two_loc[i].first, two_loc[i].second));
		while(!q.empty()) {
			int cur_x = q.front().first;
			int cur_y = q.front().second;
			q.pop();
			for(int i = 0; i < 4; ++i) {
				int nx = cur_x + dx[i];
				int ny = cur_y + dy[i];
				if (nx < 0 || ny < 0 || nx >= n || ny >= m || map[nx][ny] == 1 || map[nx][ny] == 2) {
					continue;
				} else {
					q.push(make_pair(nx, ny));
					map[nx][ny] = 2;
				}
			}
		}
	}
	// 안전 영역 크기 구하기.
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if (map[i][j] == 0)
				result++;
		}
	}
	return ans < result ? result : ans;
}

//벽세우기
void partition(int l, vector<vector<int>> map) {
	if (l == 4) {
		// 해당 맵의 안전 영역 크기 구한다.
		ans = bfs(map);
		//printf("maximum = %d\n", ans);
	} else {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if (map[i][j] == 0) {
					map[i][j] = 1;
					partition(l + 1, map);
					map[i][j] = 0;
				}
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);

	map.assign(n + 1, vector<int>(m + 1, 0));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				two_loc.push_back(make_pair(i, j));
			}
		}
	}

	partition(1, map);
	printf("%d\n", ans);
}
