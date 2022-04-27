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
		// ���� �ִ� ��� ��ǳ�⿡�� �ٶ��� �� �� ����
		for(int x = 1; x <= r; ++x) {
            for(int y = 1; y <= c; ++y) {
				if (v[x][y] > 0 && v[x][y] < 5) {
					vector<vector<int>> nwind;
					nwind.assign(r + 1, vector<int>(c + 1, 0));
					queue<pair<int, int>> q;

					if (v[x][y] == 1) { // ������
						nwind[x][y+1] = 5;
						q.push({x, y+1});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// �� �ִ��� �˻�
								// ����
								if (walls.find({{cx, cy}, 0}) != walls.end() || walls.find({{cx-1, cy}, 1}) != walls.end()) {
								} else if ((cx - 1) > 0 && (cy + 1) <= c) {
									q.push({cx-1, cy+1});
									nwind[cx-1][cy+1] = i;
								}
								// ��
								if (walls.find({{cx, cy}, 1}) != walls.end()) {
								} else if ((cy + 1) <= c) {
									q.push({cx, cy+1});
									nwind[cx][cy+1] = i;
								}
								// �Ʒ���
								if (walls.find({{cx+1,cy}, 0}) != walls.end() || walls.find({{cx+1, cy}, 1}) != walls.end()) {
								} else if ((cx + 1) <= r && (cy + 1) <= c) {
									q.push({cx+1, cy+1});
									nwind[cx+1][cy+1] = i;
								}
							}
						}
					} else if (v[x][y] == 2) { // ����
						nwind[x][y-1] = 5;
						q.push({x, y-1});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// �� �ִ��� �˻�
								// ����
								if (walls.find({{cx, cy}, 0}) != walls.end() || walls.find({{cx-1, cy-1}, 1}) != walls.end()) {
								} else if ((cx - 1) > 0 && (cy - 1) > 0) {
									q.push({cx-1, cy-1});
									nwind[cx-1][cy-1] = i;
								}
								// ��
								if (walls.find({{cx, cy-1}, 1}) != walls.end()) {
								}
								else if ((cy - 1) > 0) {
									q.push({cx, cy-1});
									nwind[cx][cy-1] = i;
								}
								// �Ʒ���
								if (walls.find({{cx+1,cy}, 0}) != walls.end() || walls.find({{cx+1, cy-1}, 1}) != walls.end()) {
								} else if ((cx + 1) <= r && (cy - 1) > 0) {
									q.push({cx+1, cy-1});
									nwind[cx+1][cy-1] = i;
								}
							}
						}
					} else if (v[x][y] == 3) { // ����
						nwind[x-1][y] = 5;
						q.push({x-1, y});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// ����
								if (walls.find({{cx, cy-1}, 1}) != walls.end() || walls.find({{cx, cy-1}, 0}) != walls.end()) {
								}
								else if ((cx - 1) > 0 && (cy - 1) > 0) {
									q.push({cx-1, cy-1});
									nwind[cx-1][cy-1] = i;
								}
								// ��
								if (walls.find({{cx, cy}, 0}) != walls.end()) {
								}
								else if ((cx-1) > 0) {
									q.push({cx-1, cy});
									nwind[cx-1][cy] = i;
								}
								// ����
								if (walls.find({{cx, cy}, 1}) != walls.end() || walls.find({{cx, cy+1}, 0}) != walls.end()) {
								}
								else if ((cx - 1) > 0 && (cy + 1) <= c) {
									q.push({cx-1, cy+1});
									nwind[cx-1][cy+1] = i;
								}
							}
						}
					} else if (v[x][y] == 4) { // �Ʒ���
						nwind[x+1][y] = 5;
						q.push({x+1, y});
						for(int i = 4; i >= 1; --i) {
							int qs = q.size();
							while(qs--) {
								int cx = q.front().first;
								int cy = q.front().second;
								q.pop();
								// �޾Ʒ�
								if (walls.find({{cx, cy-1}, 1}) != walls.end() || walls.find({{cx+1, cy-1}, 0}) != walls.end()) {
								}
								else if ((cx + 1) <= r && (cy - 1) > 0) {
									q.push({cx+1, cy-1});
									nwind[cx+1][cy-1] = i;
								}
								// �Ʒ�
								if (walls.find({{cx+1, cy}, 0}) != walls.end()) {
								}
								else if ((cx + 1) <= r) {
									q.push({cx+1, cy});
									nwind[cx+1][cy] = i;
								}
								// ���Ʒ�
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

		// �µ� ����
		vector<vector<int>> nwind;
        nwind.assign(r + 1, vector<int>(c + 1, 0));
        copy(wind.begin(), wind.end(), nwind.begin());
		for(int i = 1; i <= r; ++i) {
            for(int j = 1; j <= c; ++j) {
				// ������
				if (walls.find({{i, j}, 1}) == walls.end() && j+1 <= c && wind[i][j] > wind[i][j+1]) {
					int gg = (wind[i][j] - wind[i][j+1]) / 4;
					nwind[i][j+1] += gg;
					nwind[i][j] -= gg;
				}
				// ����
				if (walls.find({{i, j-1}, 1}) == walls.end() && j-1 > 0 && wind[i][j] > wind[i][j-1]) {
					int gg = (wind[i][j] - wind[i][j-1]) / 4;
					nwind[i][j-1] += gg;
					nwind[i][j] -= gg;
				}
				// ����
				if (walls.find({{i, j}, 0}) == walls.end() && i-1 > 0 && wind[i][j] > wind[i-1][j]) {
					int gg = (wind[i][j] - wind[i-1][j]) / 4;
					nwind[i-1][j] += gg;
					nwind[i][j] -= gg;
				}
				// �Ʒ���
				if (walls.find({{i+1, j}, 0}) == walls.end() && i+1 <= r && wind[i][j] > wind[i+1][j]) {
					int gg = (wind[i][j] - wind[i+1][j]) / 4;
					nwind[i+1][j] += gg;
					nwind[i][j] -= gg;
				}
			}
		}

		// nwind -> wind �ű��
		copy(nwind.begin(), nwind.end(), wind.begin());

		// �µ��� 1 �̻��� ���� �ٱ��� ĭ�� �µ��� 1�� ����
        // 1��, r��, 1��, c��

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

		// ���ݸ� �Ա�
		choco++;

		// �˻�
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