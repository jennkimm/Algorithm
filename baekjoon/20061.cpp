#include <stdio.h>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int score = 0;

int main() {
	deque<vector<int>> green;
	deque<vector<int>> blue;

	green.assign(6, vector<int>(4, 0));
	blue.assign(6, vector<int>(4, 0));
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		int t, x, y;
		scanf("%d %d %d", &t, &x, &y);

		if (t == 1) { // (x, y)
			// green의 y열을 검사
			int j = 0;
			for(; j < 6; ++j) {
				if (green[j][y] == 0)
					continue;
				else
					break;
			}
			green[j-1][y] = 1;
			j = 0;
			for(;j < 6; ++j) {
				if (blue[j][x] == 0)
					continue;
				else
					break;
			}
			blue[j-1][x] = 1;
		} else if (t == 2) { // (x, y) (x, y+1)
			int a1 = 0;
			int a2 = 0;
			for(; a1 < 6; ++a1) {
				if (green[a1][y] == 0)
					continue;
				else
					break;
			}
			for(; a2 < 6; ++a2) {
				if (green[a2][y + 1] == 0)
					continue;
				else
					break;
			}
			int a3 = min(a1-1, a2-1);
			green[a3][y] = 1;
			green[a3][y + 1] = 1;
			a1 = 0;
			for(; a1 < 6; ++a1) {
				if (blue[a1][x] == 0)
					continue;
				else
					break;
			}
			blue[a1 - 1][x] = 1;
			blue[a1 - 2][x] = 1;
		} else if (t == 3) { // (x, y) (x+1, y)
			int j = 0;
			for(; j < 6; ++j) {
				if (green[j][y] == 0)
					continue;
				else
					break;
			}
			green[j - 1][y] = 1;
			green[j - 2][y] = 1;
			int a1 = 0;
			int a2 = 0;
			for(; a1 < 6; ++a1) {
				if (blue[a1][x] == 0)
					continue;
				else
					break;
			}
			for(; a2 < 6; ++a2) {
				if (blue[a2][x + 1] == 0)
					continue;
				else
					break;
			}
			int a3 = min(a1-1, a2-1);
			blue[a3][x] = 1;
			blue[a3][x + 1] = 1;
		}

		// 없어지는 행 있는지 검사 = 점수 획득
		int remove_row_cnt = 0;

		for(int j = 5; j >= 2 ; --j) {
			bool isRemovable = false;
			for(int k = 0; k < 4; ++k) {
				if (green[j][k] == 1) {
					isRemovable = true;
					continue;
				} else {
					isRemovable = false;
					break;
				}
			}
			if (isRemovable) {
				green.erase(green.begin() + j);
				remove_row_cnt++;
			}
		}

		score += remove_row_cnt;

		// 없어진 행 수만큼 추가
		while(remove_row_cnt--) {
			vector<int> tmp;
			tmp.assign(4, 0);
			green.push_front(tmp);
		}

		remove_row_cnt = 0;

		// 연한 행에 블록 있는지 검사
		for(int j = 1; j >= 0; --j) {
			bool isExist = false;
			for(int k = 0; k < 4; ++k) {
				if (green[j][k] == 1) {
					isExist = true;
					break;
				} else {
					isExist = false;
					continue;
				}
			}
			if (isExist) {
				remove_row_cnt++;
			}
		}

		if (remove_row_cnt == 1) {
			green.pop_back();
			vector<int> tmp;
			tmp.assign(4, 0);
			green.push_front(tmp);
		} else if (remove_row_cnt == 2) {
			green.pop_back();
			green.pop_back();
			vector<int> tmp;
			tmp.assign(4, 0);
			vector<int> tmp2;
			tmp2.assign(4, 0);
			green.push_front(tmp);
			green.push_front(tmp2);
		}

		// blue --
		remove_row_cnt = 0;

		for(int j = 5; j >= 2 ; --j) {
			bool isRemovable = false;
			for(int k = 0; k < 4; ++k) {
				if (blue[j][k] == 1) {
					isRemovable = true;
					continue;
				} else {
					isRemovable = false;
					break;
				}
			}
			if (isRemovable) {
				blue.erase(blue.begin() + j);
				remove_row_cnt++;
			}
		}

		score += remove_row_cnt;

		// 없어진 행 수만큼 추가
		while(remove_row_cnt--) {
			vector<int> tmp;
			tmp.assign(4, 0);
			blue.push_front(tmp);
		}

		remove_row_cnt = 0;
		// 연한 행에 블록 있는지 검사
		for(int j = 1; j >= 0; --j) {
			bool isExist = false;
			for(int k = 0; k < 4; ++k) {
				if (blue[j][k] == 1) {
					isExist = true;
					break;
				} else {
					isExist = false;
					continue;
				}
			}
			if (isExist) {
				remove_row_cnt++;
			}
		}

		if (remove_row_cnt == 1) {
			blue.pop_back();
			vector<int> tmp;
			tmp.assign(4, 0);
			blue.push_front(tmp);
		} else if (remove_row_cnt == 2) {
			blue.pop_back();
			blue.pop_back();
			vector<int> tmp;
			tmp.assign(4, 0);
			vector<int> tmp2;
			tmp2.assign(4, 0);
			blue.push_front(tmp);
			blue.push_front(tmp2);
		}
	}

	printf("%d\n", score);
	int tile_cnt = 0;
	for(int i = 0; i < 6; ++i) {
		for(int j = 0; j < 4; ++j) {
			if (green[i][j] == 1)
				tile_cnt++;
			if (blue[i][j] == 1)
				tile_cnt++;
		}
	}

	printf("%d\n", tile_cnt);
	return 0;
}
