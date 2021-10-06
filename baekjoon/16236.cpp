#include <stdio.h>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int dx[] = {1, 0, 0, -1};
int dy[] = {0, -1, 1, 0};

int n, m;
vector<vector<int>> v;
vector<vector<int>> visited; // 거리 담는다.
int fsize = 2;
int fish = 0;
int ans = 0;
int eat_cnt = 0;

struct coor{
	int x;
	int y;
	int cnt;
};

int minDist = 987654321;

void bfs(int x, int y) {
	minDist = 987654321;
	queue<coor> q;
	q.push({x, y, 1});
	while(!q.empty()) {
		int dist = q.front().cnt;
		int cx = q.front().x;
		int cy = q.front().y;
		visited[cx][cy] = dist;
		q.pop();
		for(int i = 0; i < 4; ++i) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny] || v[nx][ny] > fsize) {
				continue;
			} else if (v[nx][ny] != 0 && v[nx][ny] < fsize) {
				// 먹을 수 있는 물고기
				if (v[nx][ny] > 0)
					v[nx][ny] *= -1;
				if(minDist > dist + 1)
					minDist = dist + 1;
				fish++;
				q.push({nx, ny, dist + 1});
				visited[nx][ny] = dist + 1;
			} else if (v[nx][ny] == 0 || v[nx][ny] == fsize) {
				// 지나만 갈 수 있는 곳
				q.push({nx, ny, dist + 1});
				visited[nx][ny] = dist + 1;
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	v.assign(n + 1, vector<int>(n + 1, 0));
	visited.assign(n + 1, vector<int>(n + 1, 0));

	int start_x, start_y;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &v[i][j]);
			if (v[i][j] == 9) {
				start_x = i; // 2
				start_y = j; // 1
				v[i][j] = 0;
			}
		}
	}

	int fflag = 0;

	while(true) {
		visited[start_x][start_y] = 1;
		bfs(start_x, start_y);
		if (fish == 0)
			break;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (visited[i][j] == minDist && v[i][j] < 0) {
					start_x = i;
					start_y = j;

					v[i][j] = 0;
					ans += minDist - 1;
					fflag = 1;

					eat_cnt += 1;
					if (eat_cnt == fsize) {
						eat_cnt = 0;
						fsize++;
					}
					break;
				}
			}
			if (fflag == 1)
				break;
		}
		fflag = 0;
		fish = 0;
		visited.assign(n + 1, vector<int>(n + 1, 0));
	}
	printf("%d\n", ans);
	return 0;
}
