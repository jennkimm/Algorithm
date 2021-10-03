#include <stdio.h>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> v;
vector<vector<bool>> visited;
int fish_cnt = 0;
int size = 2;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};
int ans = 9876543;

void dfs(int x, int y, int cnt, vector<vector<bool>> visited, int time) {
	if (cnt < fish_cnt) {
		// 다 잡아먹지 못하는 경우
		// 내 사이즈보다 큰 물고기들만 남아있을 경우
		bool flag = false;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (v[i][j] < size && v[i][j] > 0)
					flag = true;
			}
			if (flag)
				break;
		}
		if (!flag) {
			if (time < ans)
				ans = time;
			printf(" time = %d\n", time);
			return;
		}
	}
	if (cnt == fish_cnt) {
		// 다 잡아먹은 시간 출력해서 최소값.
		if (time < ans)
			ans = time;
		printf(" time = %d\n", time);
		return;
	}
	else {
		int sum = 0;
		for(int i = 2; i <= size; ++i) {
			sum += i;
		}
		if (cnt == sum)
			size++;
		printf("size = %d\n",size);
		for(int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || v[nx][ny] > size || visited[nx][ny]) {
				continue;
			}
			else if (v[nx][ny] >= 1 && v[nx][ny] <= 6 && v[nx][ny] < size) { // 물고기 먹고 이동.
				int temp = v[nx][ny];
				visited[nx][ny] = true;
				v[nx][ny] = 0;
				printf("(%d %d) ", nx, ny);
				dfs(nx, ny, cnt + 1, visited, time + 1);
				visited[nx][ny] = false;
				v[nx][ny] = temp;
			} else { // 그냥 이동.
				visited[nx][ny] = true;
				printf("(%d %d) ", nx, ny);
				dfs(nx, ny, cnt, visited, time + 1);
				visited[nx][ny] = false;
			}
		}
		// 갈 수 있는 곳이 없다면?
		return;
	}
}

int main() {
	scanf("%d", &n);
	v.assign(n + 1, vector<int>(n + 1, 0));
	visited.assign(n + 1, vector<bool>(n + 1, false));
	int start_x, start_y;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &v[i][j]);
			if (v[i][j] == 9) {
				start_x = i; // 2
				start_y = j; // 1
				v[i][j] = 0;
			}
			if (v[i][j] >= 1 && v[i][j] <= 6)
				fish_cnt++;
		}
	}

	dfs(start_x, start_y, 0, visited, 0);
	printf("%d\n", ans);
	return 0;

	// 물고기가 더 크면 -> 그 칸 못지나감
	// 크기 같으면 -> 그 칸 지나감. 먹지는 못함
	// 크기 작으면 -> 먹는다.

	// 갈 수 있는 곳에 있는 물고기 다 먹을 수 있는 시간 출력.
	// 가장 가까운 물고기 먹으러 감. 가장 위 왼쪽 부터 먹는다. -> x가 작은 순서. x가 같다면 y 작은 순서.
	// 먹으면 몸 크기 +1
	// 상어의 이동 1초 걸림.

	// bfs..

}
