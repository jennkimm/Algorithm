#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int sum = 0;
int ans = 40001;
vector<vector<int>> a;

int dx[] = {1, 1, -1, -1};
int dy[] = {-1, 1, 1, -1};

int main() {
	scanf("%d ", &n);
	a.assign(n + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &a[i][j]);
			sum += a[i][j];
		}
	}

	int d1, d2;
	for(int i = 1; i < n; ++i) {
		for(int j = 1; j < n; ++j) {
			if (i + j <= n - 1) {
				d1 = i;
				d2 = j;
				printf("%d %d---\n", d1, d2);
				int x_rower = 1;
				int x_upper = n - d1 - d2;
				int y_rower = 1 + d1;
				int y_upper = n - d2;
				for(int x = x_rower; x <= x_upper; ++x) {
					for(int y = y_rower; y <= y_upper; ++y) {
						vector<vector<int>> v;
						v.assign(n + 1, vector<int>(n + 1, 0));
						vector<int> ppl = {0, 0, 0, 0, 0};
						// 경계선
						int cx = x;
						int cy = y;
						v[x][y] = 5;
						for(int k = 0; k < d1; ++k) {
							cx += dx[0];
							cy += dy[0];
							v[cx][cy] = 5;
						}
						for(int k = 0; k < d2; ++k) {
							cx += dx[1];
							cy += dy[1];
							v[cx][cy] = 5;
						}
						for(int k = 0; k < d1; ++k) {
							cx += dx[2];
							cy += dy[2];
							v[cx][cy] = 5;
						}
						for(int k = 0; k < d2; ++k) {
							cx += dx[3];
							cy += dy[3];
							v[cx][cy] = 5;
						}

						// 1~4선거구 정하기
						for(int r = 1; r < x + d1; ++r) {
							for(int c = 1; c <= y; ++c) {
								if (v[r][c] == 5)
									break;
								ppl[0] += a[r][c];
								v[r][c] = 1;
							}
						}
						for(int r = 1; r <= x + d2; ++r) {
							for(int c = n; c > y; --c) {
								if (v[r][c] == 5)
									break;
								ppl[1] += a[r][c];
								v[r][c] = 2;
							}
						}
						for(int r = x + d1; r <= n; ++r) {
							for(int c = 1; c < y-d1+d2; ++c) {
								if (v[r][c] == 5)
									break;
								ppl[2] += a[r][c];
								v[r][c] = 3;
							}
						}
						for(int r = x + d2 + 1; r <= n; ++r) {
							for(int c = n; c >= y-d1+d2; --c) {
								if (v[r][c] == 5)
									break;
								ppl[3] += a[r][c];
								v[r][c] = 4;
							}
						}
						ppl[4] = sum - ppl[0] - ppl[1] - ppl[2] - ppl[3];
						printf("%d %d %d %d %d\n", ppl[0], ppl[1], ppl[2], ppl[3], ppl[4]);
						sort(ppl.begin(), ppl.end());
						if (ppl[4] - ppl[0] < ans)
							ans = ppl[4] - ppl[0];
						printf("%d\n", ppl[4] - ppl[0]);
						for(int k = 1; k <= n; ++k) {
							for(int l = 1;l <= n; ++l) {
								printf("%d ", v[k][l]);
							}
							printf("\n");
						}
						printf("\n");
					}
				}

			}
		}
	}


	printf("%d\n", ans);
	return 0;


}
