#include <stdio.h>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct wall {
    int x, y, t;
};

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
	int r, c, k, w;
    int choco = 0;
	vector<vector<int>> v;
    vector<vector<int>> wind;
	scanf("%d %d %d", &r, &c, &k);
	v.assign(r + 1, vector<int>(c + 1, 0));
    wind.assign(r + 1, vector<int>(c + 1, 0));
    multimap<pair<pair<int, int>, int>, int> walls;

	for(int i = 1; i <= r; ++i) {
        for(int j = 1; j <= c; ++j) {
            scanf("%d", &v[i][j]);
        }
    }
	scanf("%d", &w);
    for(int i = 0; i < w; ++i) {
        wall temp;
        scanf("%d %d %d", &temp.x, &temp.y, &temp.t);
        walls.insert({{{temp.x, temp.y}, temp.t}, 1});
    }

	while(choco < 101) {
		// 집에 있는 모든 온풍기에서 바람이 한 번 나옴
		for(int x = 1; x <= r; ++x) {
            for(int y = 1; y <= c; ++y) {
				if (v[x][y] > 0 && v[x][y] < 5) {
					vector<vector<int>> nwind;
					nwind.assign(r + 1, vector<int>(c + 1, 0));
					queue<pair<int, int>> q;

					if (v[x][y] == 1) { // 오른쪽
						nwind[x][y+1] = 5;
						q.push({x, y+1});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// 벽 있는지 검사
								// 위오
								if (walls.find({{cx, cy}, 0}) != walls.end() || walls.find({{cx-1, cy}, 1}) != walls.end()) {
								} else if ((cx - 1) > 0 && (cy + 1) <= c) {
									q.push({cx-1, cy+1});
									nwind[cx-1][cy+1] = i;
								}
								// 오
								if (walls.find({{cx, cy}, 1}) != walls.end()) {
								} else if ((cy + 1) <= c) {
									q.push({cx, cy+1});
									nwind[cx][cy+1] = i;
								}
								// 아래오
								if (walls.find({{cx+1,cy}, 0}) != walls.end() || walls.find({{cx+1, cy}, 1}) != walls.end()) {
								} else if ((cx + 1) <= r && (cy + 1) <= c) {
									q.push({cx+1, cy+1});
									nwind[cx+1][cy+1] = i;
								}
							}
						}
					} else if (v[x][y] == 2) { // 왼쪽
						nwind[x][y-1] = 5;
						q.push({x, y-1});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// 벽 있는지 검사
								// 위왼
								if (walls.find({{cx, cy}, 0}) != walls.end() || walls.find({{cx-1, cy-1}, 1}) != walls.end()) {
								} else if ((cx - 1) > 0 && (cy - 1) > 0) {
									q.push({cx-1, cy-1});
									nwind[cx-1][cy-1] = i;
								}
								// 왼
								if (walls.find({{cx, cy-1}, 1}) != walls.end()) {
								}
								else if ((cy - 1) > 0) {
									q.push({cx, cy-1});
									nwind[cx][cy-1] = i;
								}
								// 아래왼
								if (walls.find({{cx+1,cy}, 0}) != walls.end() || walls.find({{cx+1, cy-1}, 1}) != walls.end()) {
								} else if ((cx + 1) <= r && (cy - 1) > 0) {
									q.push({cx+1, cy-1});
									nwind[cx+1][cy-1] = i;
								}
							}
						}
					} else if (v[x][y] == 3) { // 위쪽
						nwind[x-1][y] = 5;
						q.push({x-1, y});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// 왼위
								if (walls.find({{cx, cy-1}, 1}) != walls.end() || walls.find({{cx, cy-1}, 0}) != walls.end()) {
								}
								else if ((cx - 1) > 0 && (cy - 1) > 0) {
									q.push({cx-1, cy-1});
									nwind[cx-1][cy-1] = i;
								}
								// 위
								if (walls.find({{cx, cy}, 0}) != walls.end()) {
								}
								else if ((cx-1) > 0) {
									q.push({cx-1, cy});
									nwind[cx-1][cy] = i;
								}
								// 오위
								if (walls.find({{cx, cy}, 1}) != walls.end() || walls.find({{cx, cy+1}, 0}) != walls.end()) {
								}
								else if ((cx - 1) > 0 && (cy + 1) <= c) {
									q.push({cx-1, cy+1});
									nwind[cx-1][cy+1] = i;
								}
							}
						}
					} else if (v[x][y] == 4) { // 아래쪽
						nwind[x+1][y] = 5;
						q.push({x+1, y});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// 왼아래
								if (walls.find({{cx, cy-1}, 1}) != walls.end() || walls.find({{cx+1, cy-1}, 0}) != walls.end()) {
								}
								else if ((cx + 1) <= r && (cy - 1) > 0) {
									q.push({cx+1, cy-1});
									nwind[cx+1][cy-1] = i;
								}
								// 아래
								if (walls.find({{cx+1, cy}, 0}) != walls.end()) {
								}
								else if ((cx + 1) <= r) {
									q.push({cx+1, cy});
									nwind[cx+1][cy] = i;
								}
								// 오아래
								if (walls.find({{cx, cy}, 1}) != walls.end() || walls.find({{cx+1, cy+1}, 0}) != walls.end()) {
								}
								else if ((cx + 1) <= r && (cy + 1) <= c) {
									q.push({cx+1, cy+1});
									nwind[cx+1][cy+1] = i;
								}
							}
						}
					}
					// nwind + wind
					for(int i = 1; i <= r; ++i) {
						for(int j = 1; j <= c; ++j) {
							wind[i][j] += nwind[i][j];
						}
					}
				}
			}
		}

		// 온도 조절
		vector<vector<int>> nwind;
        nwind.assign(r + 1, vector<int>(c + 1, 0));
        copy(wind.begin(), wind.end(), nwind.begin());
		for(int i = 1; i <= r; ++i) {
            for(int j = 1; j <= c; ++j) {
				// 오른쪽
				if (walls.find({{i, j}, 1}) == walls.end() && j+1 <= c && wind[i][j] > wind[i][j+1]) {
					int gg = (wind[i][j] - wind[i][j+1]) / 4;
					nwind[i][j+1] += gg;
					nwind[i][j] -= gg;
				}
				// 왼쪽
				if (walls.find({{i, j-1}, 1}) == walls.end() && j-1 > 0 && wind[i][j] > wind[i][j-1]) {
					int gg = (wind[i][j] - wind[i][j-1]) / 4;
					nwind[i][j-1] += gg;
					nwind[i][j] -= gg;
				}
				// 위쪽
				if (walls.find({{i, j}, 0}) == walls.end() && i-1 > 0 && wind[i][j] > wind[i-1][j]) {
					int gg = (wind[i][j] - wind[i-1][j]) / 4;
					nwind[i-1][j] += gg;
					nwind[i][j] -= gg;
				}
				// 아래쪽
				if (walls.find({{i+1, j}, 0}) == walls.end() && i+1 <= r && wind[i][j] > wind[i+1][j]) {
					int gg = (wind[i][j] - wind[i+1][j]) / 4;
					nwind[i+1][j] += gg;
					nwind[i][j] -= gg;
				}
			}
		}

		// nwind -> wind 옮기기
		copy(nwind.begin(), nwind.end(), wind.begin());

		// 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
        // 1행, r행, 1열, c열

		for(int i = 1; i <= c; ++i ) {
            if (wind[1][i] > 0)
                wind[1][i]--;
        }
        for(int i = 1; i <= c; ++i ) {
            if (wind[r][i] > 0)
                wind[r][i]--;
        }
        for(int i = 2; i < r; ++i ) {
            if (wind[i][1] > 0)
                wind[i][1]--;
        }
        for(int i = 2; i < r; ++i ) {
            if (wind[i][c] > 0)
                wind[i][c]--;
        }

		// 초콜릿 먹기
		choco++;

		// 검사
		bool flag = true;
		for(int i = 1; i <= r; ++i) {
			for(int j = 1; j <= c; ++j) {
				if (v[i][j] == 5 && wind[i][j] < k) {
					flag = false;
					break;
				}
			}
			if (!flag) {
				break;
			}
		}
		if (flag) {
			break;
		}
	}
	printf("%d\n", choco);
	return 0;
}