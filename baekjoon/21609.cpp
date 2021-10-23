#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};
struct block_info {
	int bs;
	int r;
	int c;
	int rainbow_cnt;
	vector<pair<int, int>> qq;
};
int score= 0;

vector<vector<int>> mm;

bool cmp(block_info &b1, block_info &b2) {
	if (b1.bs == b2.bs) {
		if (b1.rainbow_cnt == b2.rainbow_cnt) {
			if (b1.r == b2.r) {
				return b1.c > b2.c;
			} else {
				return b1.r > b2.r;
			}
		} else {
			return b1.rainbow_cnt > b2.rainbow_cnt;
		}
	} else {
		return b1.bs > b2.bs;
	}
}

void bfs(int x, int y, int color, vector<block_info> &bi, vector<vector<int>> &visited) {
	queue<pair<int, pair<int, int>>> q;
	q.push({1, {x, y}});
	visited[x][y] = 1;
	int block_size = 1;
	while(!q.empty()) {
		int cur_size = q.front().first;
		int cx = q.front().second.first;
		int cy = q.front().second.second;
		q.pop();
		int nx, ny;
		for(int i = 0; i < 4; ++i) {
			nx = cx + dx[i];
			ny = cy + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny] != -1 || mm[nx][ny] == -1 || mm[nx][ny] == -2)
				continue;
			else if (mm[nx][ny] == 0 || mm[nx][ny] == color){
				printf("%d %d방문\n", nx, ny);
				visited[nx][ny] = 1;
				q.push({cur_size + 1, {nx, ny}});
				block_size++;
			}
		}
	}

	if (block_size == 1) {
		visited[x][y] = -2;
	} else {
		block_info tmp;
		tmp.r = x;
		tmp.c = y;
		tmp.rainbow_cnt = 0;
		tmp.bs = block_size;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (visited[i][j] == 1) {
					visited[i][j] = block_size;
					tmp.qq.push_back({i, j});
					if (mm[i][j] == 0)
						tmp.rainbow_cnt++;
				}
			}
		}
		bi.push_back(tmp);
	}
}

int main() {

	scanf("%d %d", &n, &m);
	mm.assign(n + 1, vector<int>(n + 1, 0));

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &mm[i][j]);
		}
	}

	while(true) {
		vector<vector<int>> visited;
		vector<block_info> bi;
		visited.assign(n + 1, vector<int>(n + 1, -1)); // 블록 사이즈를 넣을꺼야~

		// 블록 구하기
		// -1 : 방문 아직 안한 것.
		// -2 : 방문은 했으나 블록이 되지 못하는 한칸짜리.
		// 2 ~ : 방문 했고, 블록 사이즈.
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (mm[i][j] > 0 && mm[i][j] <= m && visited[i][j] == -1) {
					printf("%d %d bfs, color = %d\n", i, j, mm[i][j]);
					bfs(i, j, mm[i][j], bi, visited);
				}
			}
		}

		if (bi.size() == 0)
			break;

		// 1 블록의 크기가 큰 것
		// 2 무지개 블록 많이 포함한 그룹
		// 3 기준 블록 행 큰거
		// 4 기준 블록 열 큰거
		sort(bi.begin(), bi.end(), cmp);

		// 블록 제거
		// 제거된 블록은 -2
		for(int i = 0; i < bi[0].qq.size(); ++i) {
			mm[bi[0].qq[i].first][bi[0].qq[i].second] = -2;
		}

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				printf("%d ", mm[i][j]);
			}
			printf("\n");
		}

		score += bi[0].bs * bi[0].bs;

		// 중력 작용
		// -1과 -1 사이에 있는 것들 내려야함
		for(int i = 0; i < n; ++i) {
			int loc = n;
			for(int j = 0; j < n; ++j) {
				if (mm[j][i] == -1) {
					loc = j;
				}
			}
			// loc 행 전까지 위에 있는 것들 내리기
			int p = loc - 1;
			for(int j = loc - 1; j >= 0; j--) {
				if (mm[j][i] >= 0) {
					mm[p][i] = mm[j][i];
					p--;
				}
			}

			for(int j = p; j >= 0; j--) {
				mm[j][i] = -2;
			}

			// loc 행 아래에 있는 것들도 내리기
			p = loc;
			printf("p = %d\n", p);
			for(int j = loc + 1; j < n; ++j) {
				if (mm[j][i] >= 0) {
					mm[p][i] = mm[j][i];
					p++;
				}
			}

			for(int j = loc; j < loc; j++) {
				mm[j][i] = -2;
			}
		}

		printf("\n");
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				printf("%d ", mm[i][j]);
			}
			printf("\n");
		}

		// 반시계방향으로 90도 회전
		vector<vector<int>> new_m;
		new_m.assign(n + 1, vector<int>(n + 1, 0));

		int idx = 0;
		for(int i = n - 1; i >= 0; --i) {
			for(int j = 0; j < n; ++j) {
				mm[j][n - 1 - idx] = new_m[idx][j];
			}
			idx++;
		}

		copy(new_m.begin(), new_m.end(), mm.begin());

		// 중력 작용
		for(int i = 0; i < n; ++i) {
			int loc = n;
			for(int j = 0; j < n; ++j) {
				if (mm[j][i] == -1) {
					loc = j;
				}
			}
			// loc 행 전까지 위에 있는 것들 내리기
			int p = loc - 1;
			for(int j = loc - 1; j >= 0; j--) {
				if (mm[j][i] >= 0) {
					mm[p][i] = mm[j][i];
					p--;
				}
			}

			for(int j = p; j >= 0; j--) {
				mm[j][i] = -2;
			}

			// loc 행 아래에 있는 것들도 내리기
			p = loc + 1;
			for(int j = loc + 1; j < n; ++j) {
				if (mm[j][i] >= 0) {
					mm[p][i] = mm[j][i];
					p++;
				}
			}

			for(int j = p; j <= loc + 1; j++) {
				mm[j][i] = -2;
			}
		}

		// 블록이 존재할때가지 반복한다.
	}
	printf("%d\n", score);
	return 0;
}
