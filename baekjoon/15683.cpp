#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

//4:40

int n, m;

int ans = 65;

// 1 -> 한쪽방향 4개
// 2 -> 양옆 2개
// 3 -> 90도 두방향 4개
// 4 -> 세방향 4개
// 5 -> 4방향 1개

vector<vector<int>> up(vector<vector<int>> copy_map, int i, int j) {
	for(int k = i - 1; k >= 0; --k) {
		if (copy_map[k][j] == 6)
			break;
		else if (copy_map[k][j] == 0)
			copy_map[k][j] = -1;
		else
			continue;
	}
	return copy_map;
}

vector<vector<int>> right(vector<vector<int>> copy_map, int i, int j) {
	for(int k = j + 1; k < m; ++k) {
		if (copy_map[i][k] == 6)
			break;
		else if (copy_map[i][k] == 0)
			copy_map[i][k] = -1;
		else
			continue;
	}
	return copy_map;
}

vector<vector<int>> left(vector<vector<int>> copy_map, int i, int j) {
	for(int k = j - 1; k >= 0; --k) {
		if (copy_map[i][k] == 6)
			break;
		else if (copy_map[i][k] == 0)
			copy_map[i][k] = -1;
		else
			continue;
	}
	return copy_map;
}

vector<vector<int>> down(vector<vector<int>> copy_map, int i, int j) {
	for(int k = i + 1; k < n; ++k) {
		if (copy_map[k][j] == 6)
			break;
		else if (copy_map[k][j] == 0)
			copy_map[k][j] = -1;
		else
			continue;
	}
	return copy_map;
}

void dfs(vector<vector<int>> map, vector<vector<bool>> visited, int w) {
	for(int i = w; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if (map[i][j] == 1 && !visited[i][j]) {
				vector<vector<int>> copy_map;
				copy_map.assign(n + 1, vector<int>(m + 1, 0));
				copy(map.begin(), map.end(), copy_map.begin());
				//왼
				visited[i][j] = true;
				dfs(left(copy_map, i, j), visited, i);
				// 오른
				dfs(right(copy_map, i, j), visited, i);
				// 위
				dfs(up(copy_map,i, j), visited, i);
				// 아래
				dfs(down(copy_map,i, j), visited, i);
			} else if (map[i][j] == 2 && !visited[i][j]) {
				vector<vector<int>> copy_map;
				copy_map.assign(n + 1, vector<int>(m + 1, 0));
				copy(map.begin(), map.end(), copy_map.begin());
				//왼 & 오른쪽
				copy_map = left(copy_map, i, j);
				copy_map = right(copy_map, i, j);
				visited[i][j] = true;
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());

				// 위 & 아래
				copy_map = up(copy_map, i, j);
				copy_map = down(copy_map, i, j);
				dfs(copy_map, visited, i);
			} else if (map[i][j] == 3 && !visited[i][j]) {
				vector<vector<int>> copy_map;
				copy_map.assign(n + 1, vector<int>(m + 1, 0));
				copy(map.begin(), map.end(), copy_map.begin());
				// 위 & 오른쪽
				copy_map = up(copy_map, i, j);
				copy_map = right(copy_map, i, j);
				visited[i][j] = true;
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());
				// 오른쪽 & 아래쪽
				copy_map = right(copy_map, i, j);
				copy_map = down(copy_map, i, j);
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());
				// 아래쪽 & 왼쪽
				copy_map = down(copy_map, i, j);
				copy_map = left(copy_map, i, j);
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());
				// 왼쪽 & 위쪽
				copy_map = up(copy_map, i, j);
				copy_map = left(copy_map, i, j);
				dfs(copy_map, visited, i);
			} else if (map[i][j] == 4 && !visited[i][j]) {
				vector<vector<int>> copy_map;
				copy_map.assign(n + 1, vector<int>(m + 1, 0));
				copy(map.begin(), map.end(), copy_map.begin());
				// 왼 & 위 & 오른쪽
				copy_map = left(copy_map, i, j);
				copy_map = up(copy_map, i, j);
				copy_map = right(copy_map, i, j);
				visited[i][j] = true;
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());
				// 위 & 오른쪽 & 아래쪽
				copy_map = up(copy_map, i, j);
				copy_map = right(copy_map, i,j );
				copy_map = down(copy_map, i, j);
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());
				// 오른쪽 & 아래쪽 & 왼쪽
				copy_map = left(copy_map, i,j );
				copy_map = right(copy_map, i,j);
				copy_map = down(copy_map, i, j);
				dfs(copy_map, visited, i);
				copy(map.begin(), map.end(), copy_map.begin());
				// 아래쪽 & 왼쪽 & 위쪽
				copy_map = left(copy_map, i,j);
				copy_map = up(copy_map, i,j);
				copy_map = down(copy_map, i,j);
				dfs(copy_map, visited, i);
			} else if (map[i][j] == 5 && !visited[i][j]) {
				vector<vector<int>> copy_map;
				copy_map.assign(n + 1, vector<int>(m + 1, 0));
				copy(map.begin(), map.end(), copy_map.begin());
				visited[i][j] = true;
				copy_map = left(copy_map, i,j);
				copy_map = up(copy_map, i,j);
				copy_map = right(copy_map, i,j);
				copy_map = down(copy_map, i, j);
				dfs(copy_map, visited, i);
			}
		}
	}
	int cnt = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if (map[i][j] == 0)
				cnt++;
		}
	}
	if (cnt < ans)
		ans = cnt;
	return;

}

int main() {
	scanf("%d %d", &n, &m);
	vector<vector<int>> map;
	vector<vector<bool>> visited;
	map.assign(n + 1, vector<int>(m + 1, 0));
	visited.assign(n + 1, vector<bool>(m + 1, false));

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	dfs(map, visited, 0);
	printf("%d\n",ans);
	return 0;
}
