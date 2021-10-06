 #include <stdio.h>
 #include <vector>

 using namespace std;

 int r, c, t;
 vector<vector<int>> v;
 vector<vector<int>> add;

 int dx[] = {0, 0, -1, 1};
 int dy[] = {1, -1, 0, 0};
 int total = 0;

 int main() {
	scanf("%d %d %d", &r, &c, &t);

	v.assign(r + 1, vector<int>(c + 1, 0));
	add.assign(r + 1, vector<int>(c + 1, 0));
	int u, d;

	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j) {
			scanf("%d", &v[i][j]);
			if (v[i][j] == -1) {
				d = i;
			} else if(v[i][j] > 0)
				total += v[i][j];
		}
	}

	u = d - 1;

	for(int k = 0; k < t; ++k) {
		// 확산
		for(int i = 0; i < r; ++i) {
			for(int j = 0; j < c; ++j) {
				if (v[i][j] > 0) {
					int air = v[i][j] / 5;
					int cnt = 0;
					for(int p = 0; p < 4; ++p) {
						int nx = i + dx[p];
						int ny = j + dy[p];
						if (nx < 0 || nx >= r || ny < 0 || ny >= c || v[nx][ny] == -1)
							continue;
						else {
							cnt++;
							add[nx][ny] += air;
						}
					}
					add[i][j] -= ( air * cnt );
				}
			}
		}

		for(int i = 0; i < r; ++i) {
			for(int j = 0; j < c; ++j) {
				v[i][j] += add[i][j];
				add[i][j] = 0;
			}
		}

		total -= v[u - 1][0];
		total -= v[d + 1][0];

		// 공기청정기 작동
		// 0번째 행 아래쪽으로 밀기
		for(int i = u - 1; i > 0; --i) {
			v[i][0] = v[i - 1][0];
		}

		// 0번째 열 아래로 밀기
		for(int i = 0; i < c - 1; ++i) {
			v[0][i] = v[0][i + 1];
		}

		// c - 1번째 열 위로 밀기
		for(int i = 1; i <= u; ++i) {
			v[i - 1][c - 1] = v[i][c - 1];
		}

		// u번째 행 오른쪽으로 밀기
		for(int i = c - 1; i > 1; --i) {
			v[u][i] = v[u][i - 1];
		}
		v[u][1] = 0;

		// 0 번째 열 위로 밀기
		for (int i = d + 1; i < r - 1; ++i) {
			v[i][0] = v[i + 1][0];
		}

		// r - 1열 왼쪽으로 밀기
		for(int i = 0; i < c - 1; ++i) {
			v[r - 1][i] = v[r - 1][i + 1];
		}

		// c - 1열 아래로 밀기
		for(int i = r - 1; i >= d; --i) {
			v[i][c - 1] = v[i - 1][c - 1];
		}

		// d 행 오른쪽으로 밀기
		for(int i = c - 1; i > 1; --i) {
			v[d][i] = v[d][i - 1];
		}
		v[d][1] = 0;

	}
	printf("%d\n", total);
}
