#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdio.h>

using namespace std;

bool visited[1001];
vector<int> graph[1001];
stack<int> s;
queue<int> q;

void dfs(int start) {
	s.push(start);
	visited[start] = true;
	cout << start << " ";
	while (!s.empty()) {
		int currunt = s.top();
		bool flag = false;
		for (int i = 0; i < graph[currunt].size(); ++i) {
			//cout << "\n" << "현재 노드는 " << currunt <<"이고, 인접 노드는" << graph[currunt][i] << ", " << visited[graph[currunt][i]] << endl;
			if (visited[graph[currunt][i]] != true && graph[currunt][i] != 0) {
				s.push(graph[currunt][i]);
				visited[graph[currunt][i]] = true;
				flag = true;
				cout << graph[currunt][i] << " ";
				break;
			}
		}
		if (flag == false) {
			s.pop();
		}
	}
}

void bfs(int start) {
	q.push(start);
	visited[start] = true;

	while(!q.empty()) {
		int currunt = q.front();
		cout << currunt << " ";
		q.pop();
		for (int i = 0; i < graph[currunt].size(); ++i) {
			if (visited[graph[currunt][i]] != true) {
				q.push(graph[currunt][i]);
				visited[graph[currunt][i]] = true;
			}
		}
	}
}

int main() {
	int n, m, start;
	scanf("%d %d %d", &n, &m, &start);
	memset(visited, false, n + 1);
	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for(int i = 1; i <= n; ++i) {
		sort(graph[i].begin(), graph[i].end());
	}

	dfs(start);
	memset(visited, false, n + 1);
	cout << endl;
	bfs(start);
}
