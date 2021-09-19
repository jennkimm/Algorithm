#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int r, c, d;
vector<vector<int>> map;
vector<vector<bool>> visited;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int a[4][4] = {
	{0, 3, 2, 1},
	{1, 0, 3, 2},
	{2, 1, 0, 3},
	{3, 2, 1, 0}
};

int ans = 0;
// d = 0 위 1 오 2 아래 3 왼

void bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true; // 청소한다.
	ans++;
	while(!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();
		// 현재 방향에서 왼쪽 방향부터 탐색한다.
		bool flag = false;
		for(int i = 0; i < 4; ++i) {
			int nx = cx + dx[a[d][i]];
			int ny = cy + dy[a[d][i]];
			if (map[nx][ny] == 0 && !visited[nx][ny]) {
				q.push(make_pair(nx, ny));
				ans++;
				visited[nx][ny] = true;
				if (a[d][i] == 0)
					d = 3;
				else if (a[d][i] == 1)
					d = 0;
				else if (a[d][i] == 2)
					d = 1;
				else
					d = 2;
				flag = true;
				break;
			} else {
				continue;
			}
		}
		if (!flag) {
			if (d == 0 && cx + 1 < n && map[cx + 1][cy] == 0) {
				// 아래로
				q.push(make_pair(cx + 1, cy));
			} else if (d == 1 && cy - 1 >= 0 && map[cx][cy - 1] == 0) {
				// 왼쪽
				q.push(make_pair(cx, cy - 1));
			} else if (d == 2 && cx - 1 >= 0 && map[cx - 1][cy] == 0) {
				// 위로
				q.push(make_pair(cx - 1, cy));
			} else if (d == 3 && cy + 1 < m && map[cx][cy + 1] == 0) {
				// 오른쪽
				q.push(make_pair(cx, cy + 1));
			} else {
				while(!q.empty())
					q.pop();
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d %d", &n, &m, &r, &c, &d);
	map.assign(n + 1, vector<int>(m + 1));
	visited.assign(n + 1, vector<bool>(m + 1, false));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	bfs(r, c);
	printf("%d\n", ans);
}
