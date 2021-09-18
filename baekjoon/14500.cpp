#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
int n, m;
vector<vector<int>> v;
vector<vector<bool>> visited;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int ans = 0;

void dfs(int x, int y, int depth, int result) {
	if (depth == 3) {
		//printf("ans = %d, result = %d\n", ans , result);
		ans = (ans < result) ? result : ans;
		return;
	} else {
		for(int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= n || ny >= m || visited[nx][ny])
				continue;
			else {
				//printf("(%d, %d) -> %d, ", nx, ny, v[nx][ny]);
				visited[nx][ny] = true;
				dfs(nx, ny, depth + 1, result + v[nx][ny]);
				visited[nx][ny] = false;
			}
		}
		return;
	}
}

int main() {
	scanf("%d %d", &n, &m);

	v.assign(n + 1, vector<int>(m + 1));
	visited.assign(n + 1, vector<bool>(m + 1, false));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			scanf("%d", &v[i][j]);
		}
	}

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			//printf("(%d, %d) -> %d, ", i, j, v[i][j]);
			visited[i][j] = true;
			dfs(i, j, 0, v[i][j]);
			visited[i][j] = false;
			int temp = 0;
			if (i - 1 >= 0 && i + 1 < n && j - 1 >= 0) {
				temp = v[i][j] + v[i - 1][j] + v[i + 1][j] + v[i][j - 1];
				if (temp > ans)
					ans = temp;
			}
			if (i - 1 >= 0 && i + 1 < n && j + 1 < m) {
				temp = v[i][j] + v[i - 1][j] + v[i + 1][j] + v[i][j + 1];
				if (temp > ans)
					ans = temp;
			}
			if (i - 1 >= 0 && j + 1 < m && j - 1 >= 0) {
				temp = v[i][j] + v[i - 1][j] + v[i][j - 1] + v[i][j + 1];
				if (temp > ans)
					ans = temp;
			}
			if (i + 1 < n && j + 1 < m && j - 1 >= 0) {
				temp = v[i][j] + v[i + 1][j] + v[i][j - 1] + v[i][j + 1];
				if (temp > ans)
					ans = temp;
			}
		}
	}
	printf("%d\n",ans);
}
