#include <stdio.h>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> a;
vector<pair<int, int>> c;
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

int ddx[] = {-1, -1, 1, 1};
int ddy[] = {-1, 1, 1, -1};

int main() {
	scanf("%d %d", &n, &m);

	a.assign(n + 1, vector<int>(n + 1, 0));
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i = 0; i < m; ++i) {
		int tmp1, tmp2;
		scanf("%d %d", &tmp1, &tmp2);
		c.push_back(make_pair(tmp1 - 1, tmp2));
	}

	vector<pair<int, int>> cloud;
	cloud.push_back(make_pair(n, 1));
	cloud.push_back(make_pair(n, 2));
	cloud.push_back(make_pair(n - 1, 1));
	cloud.push_back(make_pair(n - 1, 2));

	for(int i = 0; i < c.size(); ++i) {

		// 구름 이동
		for(int j = 0; j < cloud.size(); ++j) {
			for(int k = 0; k < c[i].second; ++k) {
				cloud[j].first += dx[c[i].first];
				if (cloud[j].first == 0)
					cloud[j].first = n;
				if (cloud[j].first == n + 1)
					cloud[j].first = 1;
			}
			for(int k = 0; k < c[i].second; ++k) {
				cloud[j].second += dy[c[i].first];
				if (cloud[j].second == 0)
					cloud[j].second = n;
				if (cloud[j].second == n + 1)
					cloud[j].second = 1;
			}
		}

		//물의 양 증가
		for(int j = 0; j < cloud.size(); ++j) {
			a[cloud[j].first][cloud[j].second]++;
		}

		// 물복사버그
		for(int j = 0; j < cloud.size(); ++j) {
			int cnt = 0;
			for(int k = 0; k < 4; ++k) {
				int nx = cloud[j].first + ddx[k];
				int ny = cloud[j].second + ddy[k];
				if (nx < 1 || nx > n || ny < 1 || ny > n) {
					continue;
				} else {
					if (a[nx][ny] > 0)
						cnt++;
				}
			}
			a[cloud[j].first][cloud[j].second] += cnt;
		}

		int cloud_size = cloud.size();

		//구름 재생성과 물의양-2
		for(int j = 1; j <= n; ++j) {
			for(int k = 1; k <= n; ++k) {
				bool flag = false;
				for(int l = 0; l < cloud.size(); ++l) {
					if (j == cloud[l].first && k == cloud[l].second) {
						flag = true;
						break;
					}
				}
				if (flag) {
					continue;
				}
				else if (a[j][k] >= 2) {
					a[j][k] -= 2;
					cloud.push_back(make_pair(j, k));
				}
			}
		}

		// 지운다.
		for(int j = 0; j < cloud_size; ++j) {
			auto it = cloud.begin();
			cloud.erase(it);
		}
	}

	int water = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			water += a[i][j];
		}
	}
	printf("%d\n", water);
	return 0;
}
