#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int dx[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int tx[] = { 0, -1, 0, 1, 0 };
int ty[] = { 0, 0, -1, 0, 1 };

int m, s;
vector<vector<deque<int>>> v;
vector<vector<int>> smell;
int shark_x, shark_y;

struct fish {
	int x, y, dir;
};
struct vd{
	int a, b, c; // 방향
	int cnt; // 물고기 갯수
}

deque<fish> fishs;

int max_fish = 0;
vector<vd> vvd;

void dfs(int cnt, int x, int y, vector<int> vdir) {
	if(vdir.size() == 3) {
		vd temp;
		temp.a = vdir[0];
		temp.b = vdir[1];
		temp.c = vdir[2];
		temp.cnt = cnt;
		if (cnt > max_fish)
			max_fish = cnt;
		vvd.push_back(temp);
	} else {
		for(int i = 1; i <= 4; ++i) {
			int nx = x + tx[i];
			int ny = y + ty[i];

			if (nx < 1 || nx > 4 || ny < 1 || ny > 4) {
				continue;
			} else {
				vdir.push_back(i);
				dfs(cnt + v[nx][ny].size(), nx, ny, vdir);
				vdir.pop_back();
			}
		}
	}
}

int main() {
	scanf("%d %d", &m, &s);

	v.assign(5, vector<deque<int>>(5));
	smell.assign(5, vector<int>(5, 0));

	for(int i = 0; i < m; ++i) {
		fish tmp;
		scanf("%d %d %d", &tmp.x, &tmp.y, &tmp.dir);
		fishs.push_back(tmp);
	}

	scanf("%d %d", &shark_x, &shark_y);

	for(int t = 0; t < s; ++t) {
		// 알을 낳는다.

		// 물고기 이동
		for(int i = 0; i < fishs.size(); ++i) {
			// 방향에 맞게 이동
			int dir = fishs[i].dir;
			int nx = fishs[i].x + dx[dir];
			int ny = fishs[i].y + dy[dir];
			if (nx < 1 || nx > 4 || ny < 1 || ny > 4 || (shark_x == nx && shark_y == ny) || smell[nx][ny] != 0) {
				// 반시계방향 45도 회전
				dir--;
				if (dir == 0)
					dir = 8;
				continue;
			} else {
				// 물고기 이동시키기
				v[nx][ny].push_back(dir);
			}
		}

		// 상어 이동
		vector<int> vtemp;
		dfs(0, shark_x, shark_y, vtemp);
		for(int i = 0; i < vvd.size(); ++i) {
			if (vvd[i].cnt == max_fish) {
				// 이렇게움직일거다
				int nx1, ny1, nx2, ny2, nx3, ny3;
				nx1 = shark_x + tx[vvd[i].a];
				ny1 = shark_y + ty[vvd[i].a];
				nx2 = nx1 + tx[vvd[i].b];
				ny2 = ny1 + ty[vvd[i].b];
				nx3 = nx2 + tx[vvd[i].c];
				ny3 = ny2 + ty[vvd[i].c];
				for(int k = fishs.size() - 1; k >= 0; --k) {
					if (nx1 == fishs[k].x && ny1 == fishs[k].y) {
						fishs.erase(fishs.begin() + k);
						smell[nx1][ny1] = 2;
					}
					if (nx2 == fishs[k].x && ny2 == fishs[k].y) {
						fishs.erase(fishs.begin() + k);
						smell[nx2][ny2] = 2;
					}
					if (nx3 == fishs[k].x && ny3 == fishs[k].y) {
						fishs.erase(fishs.begin() + k);
						smell[nx2][ny2] = 2;
					}
				}
				v[nx1][ny1].clear();
				v[nx2][ny2].clear();
				v[nx3][ny3].clear();
				shark_x = nx3;
				shark_y = ny3;
				break;
			}
		}

		for(int i = 1; i <= 4; ++i) {
			for(int j = 1; j <= 4; ++j) {
				if (smell[i][j] > 0) {
					smell[i][j]--;
				}
			}
		}

		// 물고기 복제
		


		max_fish = 0;
	}
}
