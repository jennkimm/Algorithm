#include <stdio.h>
#include <vector>

using namespace std;
int m, n;
int MAP[50][50];
int snail[50][50];
int indexValue[2500];
int dx[] = {0, 1, 0, -1, 0};
int dy[] = {-1, 0, 1, 0, -1};

int tx[] = {0, -1, 1, 0, 0};
int ty[] = {0, 0, 0, -1, 1};

int startX, startY;
int icnt;
int one_cnt = 0;
int two_cnt = 0;
int three_cnt = 0;

void makeArr(int map[50][50], int arr[]) { // 2차원 -> 1차원
	int h[] = {1, 1, 2, 2, 2};
	int cnt = n / 2;
	bool flag = false;
	int idx = 0;
	int nx = startX;
	int ny = startY;
	int ncnt = 1;
	indexValue[idx++] = MAP[nx][ny];
	for(int i = 0; i < cnt; ++i) {
		for(int j = 0; j < 5; ++j) {
			for(int k = 0; k < h[j]; ++k) {
				nx = nx + dx[j];
				ny = ny + dy[j];
				if (MAP[nx][ny] != -1) {
				    indexValue[idx++] = MAP[nx][ny];
                    ncnt++;
                }
			}
			if (flag)
				break;
		}
		if (flag)
			break;
		for(int j = 1; j < 5; ++j) {
			h[j] += 2;
		}
	}
    for (int i = ncnt; i < n * n; ++i) {
        indexValue[i] = 0;
    }
}

void makeMap(int arr[]) { // 1차원 -> 2차원
	int new_arr[2500] = {0};
	int ncnt, count;
	ncnt = 1;
	count = 1;
	for(int i = 1; i < icnt; ++i) {
		if (arr[i] == arr[i + 1])
			count++;
		else {
			new_arr[ncnt++] = count;
			new_arr[ncnt++] = arr[i];
			count = 1;
		}
		if (ncnt == n * n)
			break;
	}
	for(int i = 1; i < ncnt; ++i) {
		arr[i] = new_arr[i];
	}
	for(int i = ncnt; i < n * n; ++i) {
		arr[i] = 0;
	}

	int h[] = {1, 1, 2, 2, 2};
	int cnt = n / 2;
	bool flag = false;
	int idx = 0;
	int nx = startX;
	int ny = startY;
	MAP[nx][ny] = indexValue[idx++];
	for(int i = 0; i < cnt; ++i) {
		for(int j = 0; j < 5; ++j) {
			for(int k = 0; k < h[j]; ++k) {
				nx = nx + dx[j];
				ny = ny + dy[j];
				MAP[nx][ny] = indexValue[idx++];
			}
			if (flag)
				break;
		}
		if (flag)
			break;
		for(int j = 1; j < 5; ++j) {
			h[j] += 2;
		}
	}
}

int explode(int arr[]) {
	int flag, count, start, tcnt;

	flag = 0;
	start = count = 1;

	tcnt = n * n;
	icnt = 1;
	for(int i = 1; i < tcnt; ++i) {
		if (arr[i] == arr[i + 1])
			count++;
		else {
			if (count < 4) {
				for(int k = start; k < start + count; ++k) {
					arr[icnt++] = arr[k];
				}
			} else {
				if (arr[i] == 1)
					one_cnt += count;
				else if (arr[i] == 2)
					two_cnt += count;
				else
					three_cnt += count;
				flag = 1;
			}
			start = i + 1;
			count = 1;
		}
	}

	for(int i = icnt; i < tcnt; ++i) {
		arr[i] = 0;
	}
	return flag;
}

int main() {
	scanf("%d %d", &n, &m);

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &MAP[i][j]);
		}
	}

	startX = (n + 1) / 2;
	startY = (n + 1) / 2;

	for(int i = 0; i < m; ++i) {
		int d, s;
		scanf("%d %d", &d, &s);

		int nx, ny;
		for(int k = 1; k <= s; ++k) {
			nx = startX + tx[d] * k;
			ny = startY + ty[d] * k;
			MAP[nx][ny] = -1; // 구슬 파괴
		}

		makeArr(MAP, indexValue); // 2차원 -> 1차원

		// 구슬 폭발
		while(true) {
			int result = explode(indexValue);
			if (result == 0)
				break;
		}

		makeMap(indexValue); // 1차원 -> 2차원

	}
	printf("%d\n", one_cnt + two_cnt * 2 + three_cnt * 3);
	return 0;
}
