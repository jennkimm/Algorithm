#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;
int n;
vector<pair<int, int>> v;
int ans = 0;

void dfs(int time, int curr_t, int result) {
	if (time + curr_t > n) {
		ans = (result > ans) ? result : ans;
		return;
	} else if (time + curr_t == n) {
		ans = (result + v[time].second > ans) ? result + v[time].second : ans;
		return;
	} else {
		for(int i = 0; i < n - time - curr_t; ++i) {
			dfs(time + curr_t + i, v[time + curr_t + i].first, result + v[time].second);
		}
	}
}

int main() {
	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		int t, p;
		scanf("%d %d", &t, &p);
		v.push_back(make_pair(t, p));
	}
	for(int i = 0; i < n; ++i) {
		dfs(i, v[i].first, 0);
	}
	printf("%d\n", ans);
}
