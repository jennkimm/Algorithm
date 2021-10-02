#include <stdio.h>
#include <vector>

using namespace std;

bool visited[101][101] = {false, };
int n;
struct info{
	int x;
	int y;
	int d;
	int g;
};

int main() {
	// 드래곤 커브가 지나간 자리 visited를 true로 한다
	scanf("%d", &n);
	vector<int> direction;

	// 0 : x 좌표 증가
	// 1 : y 좌표 감소
	// 2 : x 좌표 감소
	// 3 : y 좌표 증가
	int cur_x, cur_y;

	for(int i = 0; i < n; ++i) {
		info t;
		scanf("%d %d %d %d", &t.x, &t.y, &t.d, &t.g);
		visited[t.y][t.x] = true;
		cur_x = t.y;
		cur_y = t.x;
		int k = 1;
		direction.push_back(t.d); // 처음에 시작방향 넣음.
		while (k <= t.g) {
			// direction 뒤집은 다음에
			// 1 더해서 뒤에서 push
			for(int f = direction.size() - 1; f >= 0; f--) {
				direction.push_back((direction[f] + 1) % 4);
			}
			k++;
		}

		for(int f = 0; f < direction.size(); ++f) {
			if (direction[f] == 0) {
				cur_y = cur_y + 1;
				visited[cur_x][cur_y] = true;
			} else if (direction[f] == 1) {
				cur_x = cur_x - 1;
				visited[cur_x][cur_y] = true;
			} else if (direction[f] == 2) {
				cur_y = cur_y - 1;
				visited[cur_x][cur_y] = true;
			} else if (direction[f] == 3) {
				cur_x = cur_x + 1;
				visited[cur_x][cur_y] = true;
			}
		}
		direction.clear();
	}

	// 왼쪽 위 꼭짓점 기준으로 정사각형인지
	int ans = 0;
	for(int i = 0; i < 100; i++) {
		for(int j = 0; j < 100; j++) {
			if (visited[i][j] && visited[i + 1][j] && visited[i][j + 1] && visited[i + 1][j + 1] )
				ans++;
		}
	}
	printf("%d\n", ans);
}
