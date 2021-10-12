#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

int n;
int ans = 0;

bool isDiagonal(vector<int> &v, int r, int c) {
	bool flag = false;
	for(int i = 0; i < r; ++i) {
		if (abs(r - i) == abs(c - v[i]))
			return true;
	}
	return false;
}

void dfs(int cnt, vector<int> v, vector<bool> visited) {
	if (cnt == n) {
		ans++;
		return;
	} else {
		for(int i = 0; i < n; ++i) {
			if (!isDiagonal(v, cnt, i) && !visited[i]) { // 세로, 대각선 겹치지 않으면
				v[cnt] = i;
				visited[i] = true;
				dfs(cnt + 1, v, visited);
				v[cnt] = -1;
				visited[i] = false;
			}
		}
	}
	return;
}

int main() {
	// 가로, 세로, 대각선에 겹치지 않도록 퀸을 놓는다.
	scanf("%d", &n);

	vector<int> v;
	vector<bool> visited;
	for(int i = 0; i < n; ++i) {
		v.assign(n + 1, -1);
		visited.assign(n + 1, false);
		v[0] = i;
		visited[i] = true;
		dfs(1, v, visited);
		visited[i] = false;
	}
	printf("%d\n", ans);
}
