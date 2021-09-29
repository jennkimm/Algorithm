#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, h;
int ans = 4;
vector<vector<int>> v;

bool isItoI() {
	for(int k = 0; k < n; ++k) {
		int curr = k; // 현재 위치한 세로선.
		for(int i = 0; i < h; ++i) {
			// 왼쪽, 오른쪽을 검사하여 사다리가 있는지 검사한다.
			// curr == 0 일때는 오른쪽만, cur == n - 1 일때는 왼쪽만 검사한다.
			if (curr == 0) {
				if (v[i][curr] == 1) {
					curr += 1;
				}
			} else if (curr == n - 1) {
				if (v[i][curr - 1] == 1) {
					curr -= 1;
				}
			} else {
				if (v[i][curr] == 1) {
					curr += 1;
				} else if (v[i][curr - 1] == 1) {
					curr -= 1;
				}
			}
		}
		if (curr != k)
			return false;
	}
	return true;
}

void dfs(int depth, int w) { // w -> 사다리 놓을 곳 검사한 곳은 다시 검사하지 않는다.
	// 세로선 i가 i에 가는지 검사.
	if (isItoI()) {
		ans = min(ans, depth); // 작은지 비교하는 검사 필수!!
		return;
	}
	if (depth == 3) {
		// 세로선 i가 i에 가는지 검사.
		if (isItoI())
			ans = min(ans, depth);
		return;
	} else {
		for(int i = w; i < h; ++i) {
			for(int j = 0; j < n - 1; ++j) {
				// v[i][j] == 0 이고,
				// v[i][j - 1] == 0 v[i][j + 1] == 0 일때
				// 거기다가 다리 놓고 dfs.
				if (j == 0 && v[i][j] == 0 && v[i][j + 1] == 0) {
					v[i][j] = 1;
					dfs(depth + 1, i);
					v[i][j] = 0;
				} else if (j > 0 && v[i][j] == 0 && v[i][j - 1] == 0 && v[i][j + 1] == 0) {
					v[i][j] = 1;
					dfs(depth + 1, i);
					v[i][j] = 0;
				}
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &h);

	v.assign(h + 1, vector<int>(n + 1, 0));
	for(int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		v[a - 1][b - 1] = 1;
	}
	dfs(0, 0);
	printf("%d\n", (ans == 4) ? -1 : ans);
}
