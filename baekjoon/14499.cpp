#include <stdio.h>
#include <vector>

using namespace std;

int n, m, x, y, k;
vector<int> orders;
vector<vector<int>> map;
int a[4] = {0,0,0,0};
int b[4] = {0,0,0,0};

int main() {
	scanf("%d %d %d %d %d", &n, &m, &x, &y, &k);
	map.assign(n + 1, vector<int>(m + 1, 0));

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	orders.assign(k + 1, 0);
	for(int i = 0; i < k; ++i) {
		scanf("%d", &orders[i]);
	}
	// 1 = 오 2 = 왼 3 = 위 4 = 아래
	// 항상 a[1]이 바닥, a[3]이 위.
	for(int i = 0; i < k; ++i) {
		if (orders[i] == 1 && y + 1 >= m) {
			continue;
		} else if (orders[i] == 1) {
			int temp = a[0];
			a[0] = a[1];
			a[1] = a[2];
			a[2] = a[3];
			a[3] = temp;
			b[1] = a[1];
			b[3] = a[3];
			y = y + 1;
			if (map[x][y] == 0) {
				map[x][y] = a[1];
			} else {
				a[1] = map[x][y];
				b[1] = map[x][y];
				map[x][y] = 0;
			}
		}
		if(orders[i] == 2 && y - 1 < 0) {
			continue;
		} else if (orders[i] == 2) {
			int temp = a[3];
			a[3] = a[2];
			a[2] = a[1];
			a[1] = a[0];
			a[0] = temp;
			b[1] = a[1];
			b[3] = a[3];
			y = y - 1;
			if (map[x][y] == 0) {
				map[x][y] = a[1];
			} else {
				a[1] = map[x][y];
				b[1] = map[x][y];
				map[x][y] = 0;
			}
		}
		if (orders[i] == 3 && x - 1 < 0) {
			continue;
		} else if (orders[i] == 3) {
			int temp = b[3];
			b[3] = b[2];
			b[2] = b[1];
			b[1] = b[0];
			b[0] = temp;
			a[1] = b[1];
			a[3] = b[3];
			x = x - 1;
			if (map[x][y] == 0) {
				map[x][y] = a[1];
			} else {
				a[1] = map[x][y];
				b[1] = map[x][y];
				map[x][y] = 0;
			}
		}
		if (orders[i] == 4 && x + 1 >= n)
			continue;
		else if (orders[i] == 4) {
			int temp = b[0];
			b[0] = b[1];
			b[1] = b[2];
			b[2] = b[3];
			b[3] = temp;
			a[1] = b[1];
			a[3] = b[3];
			x = x + 1;
			if (map[x][y] == 0) {
				map[x][y] = a[1];
			} else {
				a[1] = map[x][y];
				b[1] = map[x][y];
				map[x][y] = 0;
			}
		}
		printf("%d\n", a[3]);
	}
}
