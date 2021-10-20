#include <stdio.h>
#include <vector>
#include <deque>
#include <map>

using namespace std;

int dx[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int maxx = 0;
struct fish {
	int x;
	int y;
	int dir;
};

void dfs(vector<vector<int>> mmap, int total, int bx, int by, int cx, int cy, map<int, fish> fishs, int shark_dir) {
	vector<vector<int>> before;
	bool isThere = false;
	if (bx == cx && by == cy) {
		if (maxx < total) {
			maxx = total;
		}
		return;
	} else {
		before.assign(5, vector<int>(5, 0));
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				before[i][j] = mmap[i][j];
			}
		}

		for(int i = 1; i <= 16; ++i) {
			if (fishs.find(i) == fishs.end()) { // 죽은 물고기
				continue;
			} else {
				int dir = fishs.find(i)->second.dir;
				int tx = fishs.find(i)->second.x;
				int ty = fishs.find(i)->second.y;
				int nx, ny;
				for(int j = 0; j < 8; ++j) {
					nx = tx + dx[dir];
					ny = ty + dy[dir];
					if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
						dir++;
						if (dir > 8)
							dir = 1;
						continue;
					}
					if (mmap[nx][ny] == 0 && !(nx == cx && ny == cy)) { // 비어있는 칸
						fishs.find(i)->second.x = nx;
						fishs.find(i)->second.y = ny;
						fishs.find(i)->second.dir = dir;
						mmap[nx][ny] = mmap[tx][ty];
						mmap[tx][ty] = 0;
						break;
					} else if (mmap[nx][ny] != 0 && !(nx == cx && ny == cy)) { // 물고기가 있는 칸
						// 교환
						// i번 물고기와 mmap[nx][ny]에 위치한 물고기 바꾸기
						fishs.find(i)->second.x = nx;
						fishs.find(i)->second.y = ny;
						fishs.find(i)->second.dir = dir;

						fishs.find(mmap[nx][ny])->second.x = tx;
						fishs.find(mmap[nx][ny])->second.y = ty;

						int temp = mmap[tx][ty];
						mmap[tx][ty] = mmap[nx][ny];
						mmap[nx][ny] = temp;
						break;
					}
					dir++;
					if (dir > 8)
						dir = 1;
				}
			}
		}

		// 상어가 잡아먹을 물고기 정하기
		int nx, ny;
		for(int i = 1; i <= 4; ++i) {
			nx = cx + dx[shark_dir] * i;
			ny = cy + dy[shark_dir] * i;
			if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4 || mmap[nx][ny] == 0) {
				continue;
			} else {
				int fish_number = mmap[nx][ny];
				fish temp = fishs.find(mmap[nx][ny])->second;
				fishs.erase(mmap[nx][ny]);
				mmap[nx][ny] = 0;
				isThere = true;
				dfs(mmap, total + fish_number, cx, cy, nx, ny, fishs, temp.dir);
				mmap[nx][ny] = fish_number;
				fishs.insert({fish_number, temp});
			}
		}
	}
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			mmap[i][j] = before[i][j];
		}
	}
	if (maxx < total) {
		maxx = total;
	}
	return;
}

int main() {
	vector<vector<int>> mmap; // 물고기 번호
	mmap.assign(5, vector<int>(5, 0));
	map<int, fish> fishs; // 물고기 번호, 물고기 위치, 물고기 방향

	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			fish f;
			int a;
			scanf("%d %d", &a, &f.dir);
			mmap[i][j] = a;
			f.x = i;
			f.y = j;
			fishs.insert({a, f});
		}
	}

	int total = 0;

	int shark_dir = fishs.find(mmap[0][0])->second.dir;
	total += mmap[0][0];
	fishs.erase(mmap[0][0]);
	mmap[0][0] = 0; // 상어가 지나간 곳은 빈칸으로 만든다.
	dfs(mmap, total, -1, -1, 0, 0, fishs, shark_dir);

	printf("%d\n", maxx);
	return 0;
}
