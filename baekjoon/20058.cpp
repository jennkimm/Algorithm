#include <stdio.h>
#include <vector>
#include <math.h>
#include <queue>

#define MAX 65

using namespace std;

int n, q;
int m[MAX][MAX] = {0, };
bool visited[MAX][MAX] = {false, };

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int g, s;
int max_chunk = 0;
int remain_ice = 0;

void bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({x, y});
	visited[x][y] = true;
	int size = 1;
	while(!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();
		for(int k = 0; k < 4; ++k) {
			int nx = cx + dx[k];
			int ny = cy + dy[k];
			if (nx < 0 || ny >= g || ny < 0 || ny >= g|| visited[nx][ny] || m[nx][ny] <= 0)
				continue;
			else {
				visited[nx][ny] = true;
				q.push({nx, ny});
				size++;
			}
		}
	}
	if (size > max_chunk)
		max_chunk = size;
	return;
}

int main() {
	scanf("%d %d", &n, &q);

	g = pow(2, n);

	for(int i = 0; i < g; ++i) {
		for(int j = 0; j < g; ++j) {
			scanf("%d", &m[i][j]);
		}
	}

	// 2^l * 2^l 부분으로 격자나누기
	for(int t = 0; t < q; ++t) {
		int new_v[MAX][MAX] = { 0, };
		int l;
		scanf("%d", &l);
		s = pow(2, l);

		// 시계방향으로 90도 회전시키기
		if (l > 0) {
			for(int i = 0; i < g / s; ++i) {
				int cr = i * s;
				for(int j = 0; j < g / s; ++j) {
					int cc = j * s;
					//printf("%d, %d - ", cr, cc);
					for(int u = 0; u < s; ++u) {
						for(int v = 0; v < s; ++v) {
							int wx = cc + s - u - 1;
							int wy = cr + v;
							int x = cr + u;
							int y = cc + v;
							//printf("%d %d, %d %d\n", x, y, wy, wx);
							new_v[wy][wx] = m[x][y];
						}
					}
				}
			}

			// 다시 m 으로 옮기기
			for(int i = 0; i < g; ++i) {
				for(int j = 0; j < g; ++j) {
					m[i][j] = new_v[i][j];
					new_v[i][j] = 0;
				}
			}
		}

		// 얼음이 3칸 또는 이상과 인접해있지 않은 칸의 얼음 양 -1
		int cx, cy;
		queue<pair<int, int>> q;
		for(int i = 0; i < g; ++i) {
			for(int j = 0; j < g; ++j) {
				int cnt = 0;
				cx = i;
				cy = j;
				for(int k = 0; k < 4; ++k) {
					int nx = cx + dx[k];
					int ny = cy + dy[k];

					if (nx >= 0 && nx < g && ny >= 0 && ny < g && m[nx][ny] > 0) {
						cnt++;
					}
				}
				if (cnt < 3 && m[cx][cy] > 0) {
					q.push({cx, cy});
				}
			}
		}

		while(!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			m[x][y] -= 1;
			q.pop();
		}


		for(int i = 0; i < g; ++i) {
			for(int j = 0; j < g; ++j) {
				printf("%d ", m[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	// 남아있는 얼음의 합
	for(int i = 0; i < g; ++i) {
		for(int j = 0; j < g; ++j) {
			remain_ice += m[i][j];
			if (!visited[i][j] && m[i][j] > 0) {
				bfs(i, j);
			}
		}
	}

	// 가장 큰 덩어리가 차이하는 칸의 개수
	printf("%d\n%d\n", remain_ice, max_chunk);
	return 0;
}
