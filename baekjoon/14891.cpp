#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> v;
int ans = 0;

void rotate(vector<int> &v, int r) {
	if (r == 1) {
		// 시계방향
		int temp = v[7];
		for(int i = 6; i >= 0; --i) {
			v[i + 1] = v[i];
		}
		v[0] = temp;
	} else {
		int temp = v[0];
		for(int i = 0; i <= 6; ++i) {
			v[i] = v[i + 1];
		}
		v[7] = temp;
	}
}

int main() {
	v.assign(5, vector<int>(9, 0));

	for(int i = 0; i < 4; ++i) {
		char s[8];
		scanf("%s", s);
		for(int j = 0; j < 8; ++j) {
			if (s[j] == '0')
				v[i][j] = 0;
			else
				v[i][j] = 1;
		}
	}

	int c;
	vector<pair<int, int>> r;
	scanf("%d", &c);
	for(int i = 0; i < c; ++i) {
		int t1, t2;
		scanf("%d %d", &t1, &t2);
		r.push_back(make_pair(t1, t2));
	}

	for(int i = 0; i < c; ++i) {
		bool a = false;
		bool b = false;
		bool c = false;
		if (v[0][2] != v[1][6]) { // 1번의 2 와 2번의 6
			a = true;
		}
		if (v[1][2] != v[2][6]) { // 2번의 2 와 3번의 6
			b = true;
		}
		if (v[2][2] != v[3][6]) { // 3번의 2 와 4번의 6
			c = true;
		}
		if (r[i].first == 1) {
			// 1번 r[i].second 방향으로 움직인다.
			rotate(v[0], r[i].second);
			if (a) {
				// 2번 -r[c].second 방향으로 움직인다
				rotate(v[1], -r[i].second);
			}
			if (a && b) {
				// 3번 r[c].second 방향으로 움직인다
				rotate(v[2], r[i].second);
			}
			if (a && b && c) {
				// 4번 -r[c].second 방향으로 움직인다
				rotate(v[3], -r[i].second);
			}
		} else if (r[i].first == 2) {
			rotate(v[1], r[i].second);
			if (a) {
				rotate(v[0], -r[i].second);
			}
			if (b) {
				rotate(v[2], -r[i].second);
			}
			if (b && c) {
				rotate(v[3], r[i].second);
			}
		} else if (r[i].first == 3) {
			rotate(v[2], r[i].second);
			if (c) {
				rotate(v[3], -r[i].second);
			}
			if (b) {
				rotate(v[1], -r[i].second);
			}
			if (b && a) {
				rotate(v[0], r[i].second);
			}
		} else {
			rotate(v[3], r[i].second);
			if (c) {
				rotate(v[2], -r[i].second);
			}
			if (b && c) {
				rotate(v[1], r[i].second);
			}
			if (b && c && a) {
				rotate(v[0], -r[i].second);
			}
		}
	}
	if (v[0][0])
		ans += 1;
	if (v[1][0])
		ans += 2;
	if (v[2][0])
		ans += 4;
	if (v[3][0])
		ans += 8;
	printf("%d\n", ans);
	return 0;
}
