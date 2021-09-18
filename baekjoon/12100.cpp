#include <stdio.h>
#include <vector>

using namespace std;

int n;
int ans = 0;

vector<vector<int>> shift(int k, vector<vector<int>> map) {
	vector<vector<int>> v;
	v.assign(n + 1, vector<int>());

	if (k == 0) { // 왼쪽으로 밀기
		for(int i = 0; i < n; ++i) {
			bool isAllZero = true;
			for(int j = 0; j < n; ++j) {
				if (map[i][j] != 0) {
					v[i].push_back(map[i][j]);
					isAllZero = false;
				}
			}
			if (isAllZero) {
				v[i].push_back(0);
			}
		}
	} else if (k == 1) { // 오른쪽으로 밀기
		for(int i = 0; i < n; ++i) {
			bool isAllZero = true;
			for(int j = n - 1; j >= 0 ; --j) {
				if (map[i][j] != 0) {
					v[i].push_back(map[i][j]);
					isAllZero = false;
				}
			}
			if (isAllZero) {
				v[i].push_back(0);
			}
		}
	} else if (k == 2) { // 위로 밀기
		for(int j = 0; j < n; ++j) {
			bool isAllZero = true;
			for(int i = 0; i < n; ++i) {
				if (map[i][j] != 0) {
					v[j].push_back(map[i][j]);
					isAllZero = false;
				}
			}
			if (isAllZero) {
				v[j].push_back(0);
			}
		}
	} else if (k == 3) { // 아래로 밀기
		for(int j = 0; j < n ; ++j) {
			bool isAllZero = true;
			for(int i = n - 1; i >= 0; --i) {
				if (map[i][j] != 0) {
					v[j].push_back(map[i][j]);
					isAllZero = false;
				}
			}
			if (isAllZero) {
				v[j].push_back(0);
			}
		}
	}

	for(int i = 0; i < n; ++i) {
		int temp = v[i][0];
		for(int j = 1; j < v[i].size(); ++j) {
			if (v[i][j] == 0)
				break;
			else if (temp == v[i][j]) {
				v[i][j - 1] = temp * 2;
				vector<int>::iterator it = v[i].begin();
				v[i].erase(it + j);
				temp = v[i][j]; // 다음걸로 갱신
			} else {
				temp = v[i][j];
			}
		}
	}

	// for(int i = 0; i < n; ++i) {
	// 	for(int j = 0; j < v[i].size(); ++j) {
	// 		printf("%2d ", v[i][j]);
	// 	}
	// 	printf("\n");
	// }

	if (k == 0) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < v[i].size(); ++j) {
				map[i][j] = v[i][j];
			}
			for(int j = v[i].size(); j < n; ++j) {
				map[i][j] = 0;
			}
		}
	}
	else if (k == 1) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < v[i].size(); ++j) {
				map[i][n - 1 - j] =v[i][j];
			}
			for(int j = v[i].size(); j < n; ++j) {
				map[i][n - 1 - j] = 0;
			}
		}
	}
	else if (k == 2) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < v[i].size(); ++j) {
				map[j][i] = v[i][j];
			}
			for(int j = v[i].size(); j < n; ++j) {
				map[j][i] = 0;
			}
		}
	}
	else if (k == 3) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < v[i].size(); ++j) {
				map[n - 1 - j][i] = v[i][j];
			}
			for(int j = v[i].size(); j < n; ++j) {
				map[n - 1 - j][i] = 0;
			}
		}
	}
	return map;
}

void dfs(int cnt, vector<vector<int>> map) {
	if (cnt == 5) {
		// 해당 map 에서의 최대값 구하기
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (ans < map[i][j]) {
					ans = map[i][j];
				}
			}
		}
		return;
	} else {
		for(int i = 0; i < 4; ++i) {
			dfs(cnt + 1, shift(i, map));
		}
	}
}

int main() {
	scanf("%d", &n);
	vector<vector<int>> map;

	map.assign(n + 1, vector<int>(n + 1, 0));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	//최대 5번 움직인다.
	dfs(0, map);

	printf("%d\n", ans);
	return 0;
}
