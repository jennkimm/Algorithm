#include <stdio.h>
#include <vector>
#include <deque>

using namespace std;

int n, m, k;
int mm[21][21]; // 상어의 번호 & 현재 각 상어의 위치
deque<int> new_m[21][21]; // 상어의 번호 & 현재 각 상어의 위치
int sd[441]; // 각 상어가 현재 바라보고있는 방향
pair<int, int> v[21][21]; // 상어의 번호, 남은 시간
int po[441][5][5];
int dx[] = {0, -1, 1, 0, 0};
int dy[] = {0, 0, 0, -1, 1};

int main() {
	scanf("%d %d %d", &n, &m, &k);

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &mm[i][j]);
		}
	}

	for(int i = 1; i <= m; ++i) {
		scanf("%d ", &sd[i]);
	}

	for(int i = 1; i <= m; ++i) {
		for(int j = 1; j <= 4; ++j) {
			for(int l = 1; l <= 4; ++l) {
				scanf("%d", &po[i][j][l]);
			}
		}
	}

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if (mm[i][j] > 0) {
				v[i][j].first = mm[i][j];
				v[i][j].second = k;
			}
		}
	}

	int loop_cnt = 1;
	while(loop_cnt < 1001) {
		// 상어 이동
		int remember[441];
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				if (mm[i][j] != 0) {
					int cx = i;
					int cy = j;
					bool isEmptyExist = false;
					for(int l = 1; l <= 4; ++l) {
						cx = i + dx[po[mm[i][j]][sd[mm[i][j]]][l]];
						cy = j + dy[po[mm[i][j]][sd[mm[i][j]]][l]];
						if (cx < 1 || cx > n || cy < 1 || cy > n)
							continue;
						else if (v[cx][cy].first == 0) { // 아무 냄새가 없는 칸
							if (new_m[cx][cy].size() > 0) {
								if (new_m[cx][cy].front() > mm[i][j]) {
									new_m[cx][cy].push_front(mm[i][j]);
									remember[mm[i][j]] = l;
								}
								else
									new_m[cx][cy].push_back(mm[i][j]);
							} else {
								new_m[cx][cy].push_front(mm[i][j]);
								remember[mm[i][j]] = l;
							}
							isEmptyExist = true;
							// sd[mm[i][j]] = po[mm[i][j]][sd[mm[i][j]]][l];
							mm[i][j] = 0;
							break;
						}
					}
					if (!isEmptyExist) {
						for(int l = 1; l <= 4; ++l) {
							cx = i + dx[po[mm[i][j]][sd[mm[i][j]]][l]];
							cy = j + dy[po[mm[i][j]][sd[mm[i][j]]][l]];
							if (cx < 1 || cx > n || cy < 1 || cy > n)
								continue;
							else if (v[cx][cy].first == mm[i][j]) { // 자신의 냄새가 있는 칸
								if (new_m[cx][cy].size() > 0) {
									if (new_m[cx][cy].front() > mm[i][j]) {
										new_m[cx][cy].push_front(mm[i][j]);
										remember[mm[i][j]] = l;
									}
									else
										new_m[cx][cy].push_back(mm[i][j]);
								} else {
									new_m[cx][cy].push_front(mm[i][j]);
									remember[mm[i][j]] = l;
								}
								// sd[mm[i][j]] = po[mm[i][j]][sd[mm[i][j]]][l];
								mm[i][j] = 0;
								break;
							}
						}
					}
				}
			}
		}

		// 한 칸에 여러마리 상어 있으면 제거 & 냄새 정리
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				if (new_m[i][j].size() >= 1) {
					mm[i][j] = new_m[i][j].front();
					sd[mm[i][j]] = po[mm[i][j]][sd[mm[i][j]]][remember[mm[i][j]]];
					new_m[i][j].erase(new_m[i][j].begin(), new_m[i][j].end());
				}
			}
		}

		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				if (mm[i][j] != 0) {
					v[i][j].first = mm[i][j];
					v[i][j].second = k;
				} else if (v[i][j].second > 0) {
					v[i][j].second--;
					if (v[i][j].second == 0) {
						v[i][j].first = 0;
					}
				}
			}
		}

		bool isContinue = false;
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				if (mm[i][j] > 1)
				{
					isContinue = true;
					break;
				}
			}
			if (isContinue)
				break;
		}
		if (!isContinue)
			break;
		loop_cnt++;
	}

	if (loop_cnt == 1001)
		loop_cnt = -1;

	printf("%d\n", loop_cnt);
	return 0;
}
