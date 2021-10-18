#include <stdio.h>
#include <vector>
#include <queue>

#define MAX 51

using namespace std;

struct fireball {
	int r;
	int c;
	int m; // 질량
	int d; // 방향
	int s; // 속력
};

int n, m, p;

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int ans = 0;

int main() {
	scanf("%d %d %d", &n, &m, &p);
	vector<vector<queue<fireball>>> map;
	vector<vector<queue<fireball>>> new_map;

	map.assign(n + 1, vector<queue<fireball>>(n + 1));
	new_map.assign(n + 1, vector<queue<fireball>>(n + 1));

	for(int i = 0; i < m; ++i) {
		fireball tmp;
		scanf("%d %d %d %d %d", &tmp.r, &tmp.c, &tmp.m, &tmp.s, &tmp.d);
		map[tmp.r][tmp.c].push(tmp);
	}

	for(int i = 0; i < p; ++i) {
		// 파이어볼 이동
		for(int j = 1; j <= n; ++j) {
			for(int k = 1; k <= n; ++k) {
				if (!map[j][k].empty()) {
					int size = map[j][k].size();
					for(int v = 0; v < size; ++v) {
						int x = map[j][k].front().r;
						int y = map[j][k].front().c;
						// d방향으로 s번 만큼 이동
						for(int u = 0; u < map[j][k].front().s; ++u) {
							x = x + dx[map[j][k].front().d];
							y = y + dy[map[j][k].front().d];
							if (x > n)
								x = 1;
							if (y > n)
								y = 1;
							if (x < 1)
								x = n;
							if (y < 1)
								y = n;
						}
						fireball tmp = map[j][k].front();
						tmp.r = x;
						tmp.c = y;
						new_map[x][y].push(tmp);
						map[j][k].pop();
					}
				}
			}
		}

		// 2개 이상의 파이어볼이 있는 칸이 있다면
		for(int j = 1; j <= n; ++j) {
			for(int k = 1; k <= n; ++k) {
				if (new_map[j][k].size() == 1) {
					map[j][k] = new_map[j][k];
					new_map[j][k].pop();
				} else if (new_map[j][k].size() >= 2) {
					// 같은 칸의 파이어볼을 하나로 합친다
					int m_sum = 0;
					int s_sum = 0;
					int size = new_map[j][k].size();
					bool isAllEven = false;
					bool isAllOdd = false;
					while(!new_map[j][k].empty()) {
						m_sum += new_map[j][k].front().m;
						s_sum += new_map[j][k].front().s;
						if (new_map[j][k].front().d % 2 == 0) {
							isAllEven = true;
						} else {
							isAllOdd = true;
						}
						new_map[j][k].pop();
					}
					// 파이어볼은 4개의 파이어볼로 나눈다.
					// 나누어진 파이어볼의 질량은 1/5
					// 속력은 속력합 / 합쳐진 파이어볼 갯수
					// 합쳐지는 파이어볼의 방향이 모두 홀수 or 모두 짝수면 0, 2, 4, 6 아니면 1, 3, 5, 7
					if (isAllEven == isAllOdd && m_sum / 5 > 0) {
						for(int u = 0; u < 4; ++u) {
							fireball fb;
							fb.r = j;
							fb.c = k;
							fb.s = s_sum / size;
							fb.d = u * 2 + 1;
							fb.m = m_sum / 5;
							map[j][k].push(fb);
						}
					} else if (isAllEven != isAllOdd && m_sum / 5 > 0) {
						for(int u = 0; u < 4; ++u) {
							fireball fb;
							fb.r = j;
							fb.c = k;
							fb.s = s_sum / size;
							fb.d = u * 2;
							fb.m = m_sum / 5;
							map[j][k].push(fb);
						}
					}
				}
			}
		}

	}

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if (map[i][j].size() > 0) {
				while(!map[i][j].empty()) {
					ans += map[i][j].front().m;
					//printf("%d %d, m = %d, s = %d, d = %d\n", map[i][j].front().r, map[i][j].front().c, map[i][j].front().m, map[i][j].front().s, map[i][j].front().d);
					map[i][j].pop();
				}
			}
		}
	}

	printf("%d\n", ans);
}
