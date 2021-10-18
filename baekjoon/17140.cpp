#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int r, c, k;
vector<vector<int>> a;
int cnt = 0;

bool cmp(pair<int, int> &x, pair<int, int> &y) {
	if (x.second < y.second) {
		return true;
	} else if (x.second == y.second) {
		if (x.first <= y.first) {
			return true;
		} else
			return false;
	} else
		return false;
}

bool cmp2(const pair<int,int>& a, const pair<int,int>& b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

int main() {
	scanf("%d %d %d", &r, &c, &k);
	a.assign(101, vector<int>(101, 0));

	for(int i = 1; i <=3; ++i) {
		for(int j = 1; j <= 3; ++j) {
			scanf("%d", &a[i][j]);
		}
	}

	int r_size = 3;
	int c_size = 3;
	while(a[r][c] != k && cnt < 101) { // '100초'가 지나도
		if (r_size >= c_size) {
			// R 연산
			// 행에 대해서 정렬 수행
			int max_c = 0;
			for(int i = 1; i <= r_size; ++i) {
				// 한 행에 대해서
				map<int, int> m;
				for(int j = 1; j <= c_size; j++) {
					if (a[i][j] != 0) {
						if (m.find(a[i][j]) != m.end()) {
							m.find(a[i][j])->second++;
						} else {
							m[a[i][j]] = 1;
						}
					}
				}
				vector<pair<int,int>> vec(m.begin(), m.end());
				sort(vec.begin(), vec.end(), cmp2);
				int idx = 1;
				for(int l = 0; l < vec.size(); l++) {
					a[i][idx] = vec[l].first;
					a[i][idx + 1] = vec[l].second;
					idx += 2;
					if (idx > 100)
						break;
				}
				if (max_c < (idx - 1))
					max_c = idx - 1;
				if (idx <= c_size) {
					for(int k = idx; k <= c_size; ++k) {
						a[i][k] = 0;
					}
				}
			}
			c_size = max_c;
			cnt++;
		} else {
			// C 연산
			int max_r= 0;
			for(int i = 1; i <= c_size; ++i) {
				// 한 행에 대해서
				map<int, int> m;
				for(int j = 1; j <= r_size; j++) {
					if (a[j][i] != 0) {
						if (m.find(a[j][i]) != m.end()) {
							m.find(a[j][i])->second++;
						} else {
							m[a[j][i]] = 1;
						}
					}
				}
				vector<pair<int,int>> vec(m.begin(), m.end());
				sort(vec.begin(), vec.end(), cmp2);
				int idx = 1;
				for(int l = 0; l < vec.size(); l++) {
					a[idx][i] = vec[l].first;
					a[idx + 1][i] = vec[l].second;
					idx += 2;
					if (idx > 100)
						break;
				}
				if (max_r < (idx - 1))
					max_r = idx - 1;
				if (idx <= r_size) {
					for(int k = idx; k <= r_size; ++k) {
						a[k][i] = 0;
					}
				}
			}
			r_size = max_r;
			cnt++;
		}
	}

	if (cnt == 101)
		cnt = -1;
	printf("%d\n", cnt);
}
