#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

struct info {
	int rx, ry; // 빨간공
	int bx, by; // 파란공
	int cnt; // 움직임 횟수
};
const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0, 0, -1, 1 };
char map[10][11];
info start;

int bfs() {
	int visited[10][10][10][10] = {0, };
	queue<info> q;
	q.push(start);
	visited[start.ry][start.rx][start.by][start.bx] = 1;

	int ret = -1;
	while(!q.empty()) {
		info currunt = q.front();
		q.pop();
		if (currunt.cnt > 10) {
			break;
		}
		// 둘이 동시에 구멍에 빠지는 경우 break
		if (map[currunt.ry][currunt.rx] == 'O' && map[currunt.by][currunt.bx] != 'O') {
			ret = currunt.cnt;
			break;
		}

		for (int dir = 0; dir < 4; ++dir) {
			int next_rx = currunt.rx;
			int next_ry = currunt.ry;
			int next_bx = currunt.bx;
			int next_by = currunt.by;

			// 한 방향으로 # 만나기 바로 전까지 이동
			while (1) {
                if (map[next_ry][next_rx] != '#' && map[next_ry][next_rx] != 'O') {
                    next_ry += dy[dir], next_rx += dx[dir];
                }
                else {
                    if (map[next_ry][next_rx] == '#') {
                        next_ry -= dy[dir], next_rx -= dx[dir];
						break;
                    }
                    break;
                }
            }

            while (1) {
                if (map[next_by][next_bx] != '#' && map[next_by][next_bx] != 'O') {
                    next_by += dy[dir], next_bx += dx[dir];
                }
                else {
                    if (map[next_by][next_bx] == '#') {
                        next_by -= dy[dir], next_bx -= dx[dir];
						break;
                    }
                    break;
                }
            }

			// 빨간 구슬과 파란 구슬이 겹치는 경우에는 둘의 이동 거리를 구해서 더 멀리서부터 온 구슬을 하나 뒤로 옮긴다.
			if (next_ry == next_by && next_rx == next_bx) {
                if (map[next_ry][next_rx] != 'O') {
                    int red_dist = abs(next_ry - currunt.ry) + abs(next_rx - currunt.rx);
                    int blue_dist = abs(next_by - currunt.by) + abs(next_bx - currunt.bx);
                    if (red_dist > blue_dist) {
                        next_ry -= dy[dir], next_rx -= dx[dir];
                    }
                    else {
                        next_by -= dy[dir], next_bx -= dx[dir];
                    }
                }
            }

			// 방문하지 않았다면
			if (visited[next_ry][next_rx][next_by][next_bx] == 0) {
				visited[next_ry][next_rx][next_by][next_bx] = 1;
				info next;
				next.ry = next_ry;
				next.rx = next_rx;
				next.by = next_by;
				next.bx = next_bx;
				next.cnt = currunt.cnt + 1;
				q.push(next);
			}
		}
	}
	return ret;
}

int main() {
	int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", map[i]);
    }
	printf("\n");

	for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            if (map[y][x] == 'R') {
                start.ry = y, start.rx = x;
            }
            if (map[y][x] == 'B') {
                start.by = y, start.bx = x;
            }
        }
    }

	start.cnt = 0;
	int result = bfs();
	printf("%d\n", result);

	return 0;
}
