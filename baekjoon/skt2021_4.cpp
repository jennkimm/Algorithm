#include <stdio.h>
#include <vector>

using namespace std;
vector<vector<bool>> visited;
int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 1, -1, -1, 1, 0, 0};
int ans = 0;
bool is_b_win = false;
bool is_w_win = false;

void dfs(int depth, int bw, int x, int y, int cur_x, int cur_y, vector<vector<int>> &board) {
	if (depth == 5) {
		ans = bw;
		// 육목인지를 검사.
		int next_x = x + cur_x;
		int next_y = y + cur_y;
		if (next_x >= 0 && next_y < 15 && next_y >= 0 && next_y < 15) {
			if (board[next_x][next_y] == bw)
				ans = -1;
		}
		if (ans != -1) {
			if (ans == 1)
				is_b_win = true;
			else if (ans == 2)
				is_w_win = true;
		}
		return;
	} else {
		int nx = x + cur_x;
		int ny = y + cur_y;
		if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15 || visited[nx][ny] || board[nx][ny] != bw)
			return;
		else {
			visited[nx][ny] = true;
			dfs(depth + 1, bw, nx, ny, cur_x, cur_y, board);
			visited[nx][ny] = false;
		}

	}
}

int main() {
	vector<vector<int>> board;

	board.assign(15, vector<int>(15, 0));
	visited.assign(15, vector<bool>(15, false));

	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 15; ++j) {
			scanf("%d", &board[i][j]);
		}
	}

	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 15; ++j) {
			if ((board[i][j] == 1 || board[i][j] == 2) && !visited[i][j]) {
				visited[i][j] = true;
				// 시간초과 나면 dfs의 호출을 줄이는 방법..
				for(int k = 0; k < 8; ++k) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15 || visited[nx][ny] || board[nx][ny] != board[i][j])
						continue;
					else {
						printf("%d %d\n", i, j);
						dfs(1, board[i][j], i, j, dx[k], dy[k], board);
					}
				}
				if (ans == -1)
				{
					ans = 0;
					break;
				}
			}
		}
		if (ans == -1)
			break;
	}
	// 비기는 경우.
	if (is_w_win && is_b_win && ans != -1)
		ans = 0;
	printf("%d\n", ans);
	return 0;
}
