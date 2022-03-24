#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int dr[] = { 0, 1, 1, 1, 0, -1, -1, -1 }; // 물고기 이동방향
int dc[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int tr[] = { -1, 0, 1, 0 }; // 상어 이동방향 - 상좌하우
int tc[] = { 0, -1, 0, 1 };

typedef struct {
	int r;
	int c;
	int dir;
} fish;

vector<fish> board[5][5]; // 격자
vector<vector<int>> fish_smell; // 물고기 냄새
vector<fish> fishes; // 물고기
int sr, sc; // 상어 위치

bool cmp(fish &a, fish &b) {
	if (a.r != b.r)
		return a.r < b.r;
	if (a.c != b.c)
		return a.c < b.c;
	return a.dir < b.dir;
}

int main() {
	int m, s;
	scanf("%d %d", &m, &s);

	for(int i = 0; i < m; ++i) {
		int r, c, dir;
		scanf("%d %d %d", &r, &c, &dir);
		fish f;
		f.r = r;
		f.c = c;
		// 방향은 변환이 필요 (받는건 시계방향, 옮겨야하는건 반시계방향 -> 반시계로 통일)
		dir--; // 0 ~ 7 로 조정
		if (dir == 0)
			f.dir = 0;
		else
			f.dir = 8 - dir;
		fishes.push_back(f);
	}

	scanf("%d %d", &sr, &sc);
	fish_smell.assign(5, vector<int>(5, 0));

	while(s--) {
		sort(fishes.begin(), fishes.end(), cmp);

		// 물고기 이동
		for(int i = 0; i < fishes.size(); ++i) {
			bool flag = false;
			for(int q = 0; q < 8; ++q) {
				int nr = fishes[i].r + dr[(fishes[i].dir + q) % 8];
				int nc = fishes[i].c + dc[(fishes[i].dir + q) % 8];

				if (nr < 1 || nr > 4 || nc < 1 || nc > 4) {
					continue;
				} else if (fish_smell[nr][nc] > 0 || ((nr == sr) && (nc == sc))) {
					continue;
				} else {
					fish nf;
					nf.r = nr;
					nf.c = nc;
					nf.dir = (fishes[i].dir + q) % 8;
					// 물고기 이동
					board[nr][nc].push_back(nf);
					flag = true;
					break;
				}
			}
			// 물고기 이동 가능한 곳 없으면 원래 좌표 그대로 격자에
			if (!flag) {
				board[fishes[i].r][fishes[i].c].push_back(fishes[i]);
			}
		}

		// 상어 이동
		int max_fish = -1;
		vector<vector<bool>> visited;
		int x1, y1, x2, y2, x3, y3;
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				for(int k = 0; k < 4; ++k) {
					visited.assign(5, vector<bool>(5, false));
					int fish_cnt = 0;
					int nsr1 = sr + tr[i];
					int nsc1 = sc + tc[i];
					if (nsr1 < 1|| nsr1 > 4 || nsc1 < 1 || nsc1 > 4)
						continue;
					else if (!visited[nsr1][nsc1]) {
						fish_cnt += board[nsr1][nsc1].size();
						visited[nsr1][nsc1] = true;
					}
					int nsr2 = nsr1 + tr[j];
					int nsc2 = nsc1 + tc[j];
					if (nsr2 < 1|| nsr2 > 4 || nsc2 < 1 || nsc2 > 4)
						continue;
					else if (!visited[nsr2][nsc2]) {
						fish_cnt += board[nsr2][nsc2].size();
						visited[nsr2][nsc2] = true;
					}
					int nsr3 = nsr2 + tr[k];
					int nsc3 = nsc2 + tc[k];
					if (nsr3 < 1|| nsr3 > 4 || nsc3 < 1 || nsc3 > 4)
						continue;
					else if (!visited[nsr3][nsc3]) {
						fish_cnt += board[nsr3][nsc3].size();
						visited[nsr3][nsc3] = true;
					}
					if (max_fish < fish_cnt) {
						max_fish = fish_cnt;
						x1 = nsr1;
						y1 = nsc1;
						x2 = nsr2;
						y2 = nsc2;
						x3 = nsr3;
						y3 = nsc3;
					}
				}
			}
		}
		if (board[x1][y1].size() > 0)
			fish_smell[x1][y1] = 3;
		board[x1][y1].clear();
		if (board[x2][y2].size() > 0)
			fish_smell[x2][y2] = 3;
		board[x2][y2].clear();
		if (board[x3][y3].size() > 0)
			fish_smell[x3][y3] = 3;
		board[x3][y3].clear();
		printf("상어 이동 %d %d -> %d %d -> %d %d\n", x1, y1, x2, y2, x3, y3);
		sr = x3;
		sc = y3;

		printf("상어 위치 %d %d\n", sr, sc);

		// 물고기 냄새 조정
		for(int i = 1; i <= 4; ++i) {
			for(int j = 1; j <= 4; ++j) {
				if (fish_smell[i][j] > 0) {
					fish_smell[i][j]--;
				}
			}
		}

		// 물고기 복제
		// fishes 에 현재 board 에 있는 물고기 옮기기
		for(int i = 1; i <= 4; ++i) {
			for(int j = 1; j <= 4; ++j) {
				if (board[i][j].size() > 0) {
					for(int k = 0; k < board[i][j].size(); k++) {
						fishes.push_back(board[i][j][k]);
					}
					board[i][j].clear();
				}
			}
		}
	}

	printf("%lu\n", fishes.size());
	return 0;
}
