#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
int main() {
	int n;
	scanf("%d", &n);
	vector<vector<int>> m; // 학생 배치
	map<int, vector<int>> stdt; // 학생 번호, 좋아하는 사람
	queue<pair<int, int>> q; // 좋아하는 사람 수 max인 곳의 좌표 큐에 저장.
	m.assign(n + 1, vector<int>(n + 1, 0));
	for(int i = 0; i < n * n; ++i) {
		int num;
		vector<int> a(4);
		scanf("%d %d %d %d %d", &num, &a[0], &a[1], &a[2], &a[3]);
		stdt.insert({num, a});
		// 좋아하는 사람 수 구하기
		vector<vector<int>> tmp;
		tmp.assign(n + 1, vector<int>(n + 1, 0));
		int max_likes = 0;
		for(int j = 0; j < n; ++j) {
			for(int k = 0; k < n; ++k) {
				if (m[j][k] > 0)
					continue;
				int nx, ny;
				int cnt_likes = 0;
				for(int l = 0; l < 4; ++l) {
					nx = j + dx[l];
					ny = k + dy[l];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
						continue;
					} else {
						for(int p = 0; p < 4; ++p) {
							if (m[nx][ny] == stdt.find(num)->second[p])
								cnt_likes++;
						}
					}
				}
				tmp[j][k] = cnt_likes; // 좋아하는 사람의 수가 max 인 곳이 여러 곳 있을 경우를 대비해 tmp 에 저장
				if (max_likes < cnt_likes) {
					max_likes = cnt_likes;
				}
			}
		}
		for(int j = 0; j < n; ++j) {
			for(int k = 0; k < n; ++k) {
				if (m[j][k] == 0 && tmp[j][k] == max_likes) { // 좋아하는 사람의 수 최대값 가진 곳 큐에 저장
					q.push({j, k});
				}
				tmp[j][k] = -1;
			}
		}
		if (q.size() == 1) { // 좋아하는 사람 수 max 인 곳 하나라면 그 곳에 학생 배치
			m[q.front().first][q.front().second] = num;
			q.pop();
			continue;
		} else {
			// 인접한 곳 빈칸 갯수 구하기
			int max_empties = 0;
			while(!q.empty()) {
				int j = q.front().first;
				int k = q.front().second;
				int nx, ny;
				int cnt_empties = 0;
				for(int l = 0; l < 4; ++l) {
					nx = j + dx[l];
					ny = k + dy[l];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
						continue;
					} else {
						for(int p = 0; p < 4; ++p) {
							if (m[nx][ny] == 0)
								cnt_empties++;
						}
					}
				}
				tmp[j][k] = cnt_empties;
				if (max_empties < cnt_empties) {
					max_empties = cnt_empties;
				}
				q.pop();
			}
			bool flag = false;
			for(int j = 0; j < n; ++j) {
				for(int k = 0; k < n; ++k) {
					if (tmp[j][k] == max_empties) // 인접한 곳의 빈칸 갯수가 max인 곳 중 행/열 최소인 곳에 학생 배치
					{
						flag = true;
						m[j][k] = num;
						break;
					}
				}
				if (flag)
					break;
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	int super_sum = 0;
	// 학생의 만족도 구하기
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			int cx = i;
			int cy = j;
			int nx, ny;
			int sum = 0;
			for(int l = 0; l < 4; ++l) {
				nx = cx + dx[l];
				ny = cy + dy[l];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
					continue;
				} else {
					for(int p = 0; p < 4; ++p) {
						if (m[nx][ny] == stdt.find(m[cx][cy])->second[p]) {
							sum++;
						}
					}
				}
			}
			if (sum == 0 || sum == 1) {
				super_sum += sum;
			} else if (sum == 2) {
				super_sum += 10;
			} else if (sum == 3) {
				super_sum += 100;
			} else if (sum == 4) {
				super_sum += 1000;
			}
		}
	}
	printf("%d\n", super_sum);
	return 0;
}
