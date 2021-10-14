#include <stdio.h>
#include <vector>

using namespace std;

int dx[] = {0, 1, 0, -1, 0};
int dy[] = {-1, 0, 1, 0, -1};

int h[] = {1, 1, 2, 2, 2};
int startX, startY;
int n;
int sand = 0;
vector<vector<int>> map;

bool isInside(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > n) {
		return false;
	}
	return true;
}

int main() {
	scanf("%d", &n);

	map.assign(n + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	startX = (n + 1) / 2;
	startY = (n + 1) / 2;

	int cnt = 0;
	int cx = startX;
	int cy = startY;
	int nx, ny;

	for(int i = 0; i < n / 2; ++i) {
		for(int j = 0; j < 5; ++j) {
			for(int k = 0; k < h[j]; ++k) {
				nx = cx + dx[j];
				ny = cy + dy[j];

				// (cx, cy) -> (nx, ny) 로 바람이 분다.
				if (map[nx][ny] > 0) {
					int one = map[nx][ny] * 0.01;
					int two = map[nx][ny] * 0.02;
					int five = map[nx][ny] * 0.05;
					int seven = map[nx][ny] * 0.07;
					int ten = map[nx][ny] * 0.1;
					if (dx[j] == 0 && dy[j] == -1) { // 왼
						int alpha = map[nx][ny] - 2 * (one + two + seven + ten) - five;
						if (isInside(nx, ny - 1))
							map[nx][ny - 1] += alpha;
						else
							sand += alpha;
						map[nx][ny] = 0;
						if (isInside(cx - 1, cy))
							map[cx - 1][cy] += one;
						else
							sand += one;
						if (isInside(cx + 1, cy))
							map[cx + 1][cy] += one;
						else
							sand += one;
						if (isInside(nx - 1, ny))
							map[nx - 1][ny] += seven;
						else
							sand += seven;
						if (isInside(nx + 1, ny))
							map[nx + 1][ny] += seven;
						else
							sand += seven;
						if (isInside(nx - 2, ny))
							map[nx - 2][ny] += two;
						else
							sand += two;
						if (isInside(nx + 2, ny))
							map[nx + 2][ny] += two;
						else
							sand += two;
						if (isInside(nx - 1, ny - 1))
							map[nx - 1][ny - 1] += ten;
						else
							sand += ten;
						if (isInside(nx + 1, ny - 1))
							map[nx + 1][ny - 1] += ten;
						else
							sand += ten;
						if (isInside(nx, ny - 2))
							map[nx][ny - 2] += five;
						else
							sand += five;
					}
					else if (dx[j] == 1 && dy[j] == 0) { // 아래
						int alpha = map[nx][ny] - 2 * (one + two + seven + ten) - five;
						if (isInside(nx + 1, ny)) {
							map[nx + 1][ny] += alpha;
						}
						else {
							sand += alpha;
						}
						map[nx][ny] = 0;
						if (isInside(cx, cy - 1))
							map[cx][cy - 1] += one;
						else
							sand += one;
						if (isInside(cx, cy + 1))
							map[cx][cy + 1] += one;
						else
							sand += one;
						if (isInside(nx, ny - 1))
							map[nx][ny - 1] += seven;
						else
							sand += seven;
						if (isInside(nx, ny + 1))
							map[nx][ny + 1] += seven;
						else
							sand += seven;
						if (isInside(nx, ny - 2))
							map[nx][ny - 2] += two;
						else
							sand += two;
						if (isInside(nx, ny + 2))
							map[nx][ny + 2] += two;
						else
							sand += two;
						if (isInside(nx + 1, ny - 1))
							map[nx + 1][ny - 1] += ten;
						else
							sand += ten;
						if (isInside(nx + 1, ny + 1))
							map[nx + 1][ny + 1] += ten;
						else
							sand += ten;
						if (isInside(nx + 2, ny))
							map[nx + 2][ny] += five;
						else
							sand += five;
					} else if (dx[j] == 0 && dy[j] == 1) { // 오른쪽
						int alpha = map[nx][ny] - 2 * (one + two + seven + ten) - five;
						if (isInside(nx, ny + 1))
							map[nx][ny + 1] += alpha;
						else
							sand += alpha;
						map[nx][ny] = 0;
						if (isInside(cx - 1, cy))
							map[cx - 1][cy] += one;
						else
							sand += one;
						if (isInside(cx + 1, cy))
							map[cx + 1][cy] += one;
						else
							sand += one;
						if (isInside(nx - 1, ny))
							map[nx - 1][ny] += seven;
						else
							sand += seven;
						if (isInside(nx + 1, ny))
							map[nx + 1][ny] += seven;
						else
							sand += seven;
						if (isInside(nx - 2, ny))
							map[nx - 2][ny] += two;
						else
							sand += two;
						if (isInside(nx + 2, ny))
							map[nx + 2][ny] += two;
						else
							sand += two;
						if (isInside(nx - 1, ny + 1))
							map[nx - 1][ny + 1] += ten;
						else
							sand += ten;
						if (isInside(nx + 1, ny + 1))
							map[nx + 1][ny + 1] += ten;
						else
							sand += ten;
						if (isInside(nx, ny + 2))
							map[nx][ny + 2] += five;
						else
							sand += five;
					}
					else if (dx[j] == -1 && dy[j] == 0) { // 위쪽
						int alpha = map[nx][ny] - 2 * (one + two + seven + ten) - five;
						if (isInside(nx - 1, ny))
							map[nx - 1][ny] += alpha;
						else
							sand += alpha;
						map[nx][ny] = 0;
						if (isInside(cx, cy - 1))
							map[cx][cy - 1] += one;
						else
							sand += one;
						if (isInside(cx, cy + 1))
							map[cx][cy + 1] += one;
						else
							sand += one;
						if (isInside(nx, ny - 1))
							map[nx][ny - 1] += seven;
						else
							sand += seven;
						if (isInside(nx, ny + 1))
							map[nx][ny + 1] += seven;
						else
							sand += seven;
						if (isInside(nx, ny - 2))
							map[nx][ny - 2] += two;
						else
							sand += two;
						if (isInside(nx, ny + 2))
							map[nx][ny + 2] += two;
						else
							sand += two;
						if (isInside(nx - 1, ny - 1))
							map[nx - 1][ny - 1] += ten;
						else
							sand += ten;
						if (isInside(nx - 1, ny + 1))
							map[nx - 1][ny + 1] += ten;
						else
							sand += ten;
						if (isInside(nx - 2, ny))
							map[nx - 2][ny] += five;
						else
							sand += five;
					}
				}
				cx = nx;
				cy = ny;
			}
		}
		for(int j = 1; j < 5; ++j) {
			h[j] += 2;
		}
	}
	printf("%d\n", sand);
	return 0;
}
