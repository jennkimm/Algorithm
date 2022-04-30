#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>

using namespace std;

struct cs {
	int a, b, c, d;
	int dist;
	int cost;
};

int taxiX, taxiY;
int n, m, fuel;
vector<vector<int>> map;
vector<cs> css;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// 손님을 도착지로 데려다줄때마다 연료 충전됨.
// 한 승객을 목적지로 성공적으로 이동시키면, 그 승객을 태워 이동하면서 소모한 연료 양의 두 배가 충전
// 연료는 한 칸 이동할 때마다 1만큼 소모
// 연료가 없으면 끝. (도착하면서 연료 바닥나는건 괜찮)

// M명 승객 태우는 것이 목표.
// 현재 위치에서 최단거리 짧은 승객 고른다.
// 그런 승객이 여러 명이면 그중 행 번호가 가장 작은 승객을, 그런 승객도 여러 명이면 그중 열 번호가 가장 작은 승객을 고른다.
// 택시와 승객이 같은 위치에 서 있으면 그 승객까지의 최단거리는 0

// 모든 손님을 이동시키고 연료를 충전했을 때 남은 연료의 양을 출력
// 이동 도중에 연료가 바닥나서 다음 출발지나 목적지로 이동할 수 없으면 -1을 출력한다. 모든 손님을 이동시킬 수 없는 경우에도 -1

int bfs(int sx, int sy, int tx, int ty) {
	vector<vector<bool>> visited;
	visited.assign(n+1, vector<bool>(n+1, false));
	queue<pair<pair<int, int>, int>> q; // {현재 위치}, 이동한 거리
	visited[sx][sy] = true;
	int minDist = 9999999;
	if (sx == tx && sy == ty) {
		minDist = 0;
	} else
		q.push({{sx, sy}, 0});
	while(!q.empty()) {
		int cx = q.front().first.first;
		int cy = q.front().first.second;
		int cur_dist = q.front().second;
		q.pop();
		bool flag = false;
		for(int i = 0; i < 4; ++i) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 1 || nx > n || ny < 1 || ny > n || visited[nx][ny]) {
				continue;
			} else if (map[nx][ny] == 0){
				visited[nx][ny] = true;
				q.push({{nx, ny}, cur_dist + 1});
				if (nx == tx && ny == ty && cur_dist + 1 < minDist) {
					minDist = cur_dist + 1;
					flag = true;
					break;
				}
			}
		}
		if (flag)
			break;
	}
	return minDist;
}

bool cmp(cs &a1, cs &b1) {
	if (a1.dist == b1.dist) {
		if (a1.a == b1.a) {
			return a1.b < b1.b;
		} else
			return a1.a < b1.a;
	} else
		return a1.dist < b1.dist;
}

int main() {
	scanf("%d %d %d", &n, &m, &fuel);
	map.assign(n+1, vector<int>(n+1));

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	scanf("%d %d", &taxiX, &taxiY);

	for(int i = 0; i < m; ++i) {
		cs temp;
		scanf("%d %d %d %d", &temp.a, &temp.b, &temp.c, &temp.d);
		css.push_back(temp);
	}

	int cnt = 0;
	for(int i = 0; i < css.size(); ++i) {
		// 도착지까지 데려다주는 비용
		int cost1 = bfs(css[i].a, css[i].b, css[i].c, css[i].d);
		css[i].cost = cost1;
	}
	while(!css.empty()) {
		for(int i = 0; i < css.size(); ++i) {
			// 현재 위치에서 출발지까지 가는 비용
			int dist1 = bfs(taxiX, taxiY, css[i].a, css[i].b);
			css[i].dist = dist1;
		}
		sort(css.begin(), css.end(), cmp);

		// 고른 승객을 태우러 가는 거리
		printf("%d %d -> %d %d\n", taxiX, taxiY, css[0].a, css[0].b);
		int dist = bfs(taxiX, taxiY, css[0].a, css[0].b);
		if ((dist + css[0].cost) > fuel) {
			break;
		} else {
			// 간다!
			fuel -= dist + css[0].cost;
			fuel += css[0].cost * 2;
			taxiX = css[0].c;
			taxiY = css[0].d;
			css.erase(css.begin());
			cnt++;
		}
	}
	if (cnt < m) {
		printf("-1\n");
	} else {
		printf("%d\n", fuel);
	}
	return 0;
}
