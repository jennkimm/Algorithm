#include <stdio.h>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

vector<vector<int>> map;
vector<vector<int>> visited;
int n, l, r;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};
int cnt = 0;
int sum = 0;
int ans = 0;

void bfs(int start_x, int start_y) {
	queue<pair<int, int>> q;
	q.push(make_pair(start_x, start_y));
	visited[start_x][start_y] = 1;
	cnt++;
	sum += map[start_x][start_y];
	while(!q.empty()) {
		int cur_x = q.front().first;
		int cur_y = q.front().second;
		q.pop();
		for(int i = 0; i < 4; ++i) {
			int next_x = cur_x + dx[i];
			int next_y = cur_y + dy[i];
			if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < n) {
				int diff = abs(map[cur_x][cur_y] - map[next_x][next_y]);
				if (diff >= l && diff <= r && visited[next_x][next_y] == 0) {
					visited[next_x][next_y] = 1;
					cnt++;
					sum += map[next_x][next_y];
					q.push(make_pair(next_x, next_y));
				}
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if (visited[i][j] == 1) {
				map[i][j] = sum / cnt;
				visited[i][j] = -1;
			}
		}
	}
	return;
}

int main() {
	scanf("%d %d %d", &n, &l, &r);

	map.assign(n + 1, vector<int>(n + 1, 0));
	//visited.assign(n + 1, vector<int>(n + 1, 0));

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	bool flag = true;
	while(flag) {
		flag = false;
		visited.assign(n + 1, vector<int>(n + 1, 0));
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n ; ++j) {
				bool bFlag = false;
				if (visited[i][j] == 0) {
					for(int k = 0; k < 4; ++k) {
						int nx = i + dx[k];
						int ny = j + dy[k];
						if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
							continue;
						} else if (visited[nx][ny] == 0 && abs(map[i][j] - map[nx][ny]) >= l && abs(map[i][j] - map[nx][ny]) <= r) {
							flag = true;
							bFlag = true;
							break;
						}
					}
				}
				if (bFlag) {
					bfs(i, j);
					bFlag = false;
				}
				cnt = 0;
				sum = 0;
			}
		}
		if (flag)
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}
