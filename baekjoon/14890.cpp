#include <stdio.h>
#include <vector>

using namespace std;

int n, l;
vector<vector<int>> map;
vector<vector<bool>> step;

int ans = 0;
int main() {
	scanf("%d %d", &n, &l);

	map.assign(n + 1, vector<int>(n + 1));
	step.assign(n + 1, vector<bool>(n + 1, false));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	// 행 검사
	for(int i = 0; i < n; ++i) {
		int base = map[i][0];
		bool flag = true;
		for(int j = 1; j < n; ++j) {
			if (map[i][j] == base + 1 && j - l >= 0) {
				// 경사로 놓을 수 있는지 뒤 검사
				for(int k = j - l; k < j; ++k) {
					if (map[i][k] != base || step[i][k])
						flag = false;
				}
				if (flag) {
					for(int k = j - l; k < j; ++k) {
						step[i][k] = true;
					}
				}
				// base 갱신
				base = map[i][j];
			} else if (map[i][j] == base + 1 && j - l < 0) {
				flag = false;
				break;
			} else if (map[i][j] == base - 1 && j + l <= n) {
				// 경사로 놓을 수 있는지 앞 검사
				for(int k = j + l - 1; k >= j; --k) {
					if (map[i][k] != base - 1 || step[i][k])
						flag = false;
				}
				if (flag) {
					for(int k = j + l - 1; k >= j; --k) {
						step[i][k] = true;
					}
				}
				// base 갱신
				base = map[i][j];
			} else if (map[i][j] == base - 1 && j + l > n) {
				flag = false;
				break;
			} else if (map[i][j] == base) {
				continue;
			} else {
				flag = false;
				break;
			}
		}
		if (flag) {
			ans++;
		}
	}

	step.assign(n + 1, vector<bool>(n + 1, false));
	for(int i = 0; i < n; ++i) {
		int base = map[0][i];
		bool flag = true;
		for(int j = 1; j < n; ++j) {
			if (map[j][i] == base + 1 && j - l >= 0) {
				// 경사로 놓을 수 있는지 뒤 검사
				for(int k = j - l; k < j; ++k) {
					if (map[k][i] != base || step[k][i]) {
						flag = false;
					}
				}
				if (flag) {
					for(int k = j - l; k < j; ++k) {
						step[k][i] = true;
					}
				}
				// base 갱신
				base = map[j][i];
			} else if (map[j][i] == base + 1 && j - l < 0) {
				flag = false;
				break;
			} else if (map[j][i] == base - 1 && j + l <= n) {
				// 경사로 놓을 수 있는지 앞 검사
				for(int k = j + l - 1; k >= j; --k) {
					if (map[k][i] != base - 1 || step[k][i]) {
						flag = false;
					}
				}
				if (flag) {
					for(int k = j + l - 1; k >= j; --k) {
						step[k][i] = true;
					}
				}
				// base 갱신
				base = map[j][i];
			} else if (map[j][i] == base - 1 && j + l > n) {
				flag = false;
				break;
			} else if (map[j][i] == base) {
				continue;
			} else {
				flag = false;
				break;
			}
		}
		if (flag) {
			ans++;
		}
	}

	printf("%d\n", ans);
	return 0;
}
