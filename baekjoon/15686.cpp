#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m;
int ans = 10001;
vector<vector<int>> v;
vector<vector<bool>> visited;
vector<pair<int, int>> c;
vector<pair<int, int>> h;

void dfs(int cnt, int w) {
	if (cnt == m) {
		// 치킨거리 최소값
		int result = 0; // 치킨거리 합
		for(int i = 0; i < h.size(); ++i) {
			int temp = 999; // 한 집에 대한 치킨거리
			for(int k = 0; k < c.size(); ++k) {
				temp = min(temp, abs(c[k].first - h[i].first) + abs(c[k].second - h[i].second));
			}
			result += temp;
		}
		if (result < ans)
			ans = result;
		return;
	} else {
		for(int i = w; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (!visited[i][j] && v[i][j] == 2) {
					c.push_back(make_pair(i, j));
					visited[i][j] = true;
					dfs(cnt + 1, i);
					visited[i][j] = false;
					c.pop_back();
				}
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);

	v.assign(n + 1, vector<int>(n + 1, 0));
	visited.assign(n + 1, vector<bool>(n + 1, false));

	int real_c = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &v[i][j]);
			if (v[i][j] == 2)
				real_c++;
			if (v[i][j] == 1)
				h.push_back(make_pair(i, j));
		}
	}
	m = min(m, real_c);
	dfs(0, 0);
	printf("%d\n", ans);
}
