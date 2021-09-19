#include <stdio.h>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;

int n;
vector<vector<int>> v;

int ans = 1001;

void dfs(int x, vector<int> s, vector<bool> visited) {
	if (s.size() == n / 2) {
		int a1 = 0;
		int a2 = 0;
		for(int i = 0; i < s.size(); ++i) {
			for(int j = 0; j < s.size(); ++j) {
				if (s[i] != s[j]) {
					a1 += v[s[i]][s[j]];
				}
			}
		}
		vector<int> v2;
		for(int i = 0; i < n; ++i) {
			if (visited[i] == false) {
				v2.push_back(i);
			}
		}
		for(int i = 0; i < v2.size(); ++i) {
			for(int j = 0; j < v2.size(); ++j) {
				if (i != j) {
					a2 += v[v2[i]][v2[j]];
				}
			}
		}
		ans = (ans > abs(a1 - a2)) ? abs(a1 - a2) : ans;
		return;
	} else {
		for(int i = x; i < n; ++i) {
			s.push_back(i);
			visited[i] = true;
			dfs(i + 1, s, visited);
			visited[i] = false;
			s.pop_back();
		}
	}
}

int main() {
	scanf("%d", &n);
	vector<bool> visited;
	v.assign(n + 1, vector<int>(n + 1));
	visited.assign(n + 1, false);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &v[i][j]);
		}
	}
	vector<int> s;
	dfs(0, s, visited);
	printf("%d\n", ans);
}
