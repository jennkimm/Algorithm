#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int dr[] = {0, 0, 1, -1}; // 동 서 남 북
int dc[] = {1, -1, 0, 0};

int n, m, k;
vector<vector<int>> map;
int dice[4][3] = {
    {0, 2, 0},
    {4, 1, 3},
    {0, 5, 0},
    {0, 6, 0}
};

int bfs(int x, int y, int val) {
    int cnt = 1;
    queue<pair<int, int>> q;
	vector<vector<bool>> visited;
	visited.assign(n + 1, vector<bool>(m + 1, false));
    q.push({x, y});
	visited[x][y] = true;
    while(!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i) {
            int nx = cx + dr[i];
            int ny = cy + dc[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m || visited[nx][ny]) {
                continue;
            } else if (map[nx][ny] == val) {
                q.push({nx, ny});
				visited[nx][ny] = true;
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    map.assign(n + 1, vector<int>(m + 1));

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    int score = 0;
    int dir = 0;
    int x = 1;
    int y = 1;
    for(int i = 0; i < k; ++i) {
        int nx = x + dr[dir];
        int ny = y + dc[dir];
        if (nx < 1 || nx > n || ny < 1 || ny > m) {
            // 반대방향으로 변경
            if (dir == 0) {
                dir = 1;
            } else if (dir == 1) {
                dir = 0;
            } else if (dir == 2) {
                dir = 3;
            } else {
                dir = 2;
            }
        }

        // 이동 방향으로 한 칸 굴러간다.
        x = x + dr[dir];
        y = y + dc[dir];

        // 주사위 조정
        if (dir == 0) {
            int temp = dice[3][1];
            dice[3][1] = dice[1][2];
            dice[1][2] = dice[1][1];
            dice[1][1] = dice[1][0];
            dice[1][0] = temp;
        } else if (dir == 1) {
			int temp = dice[3][1];
            dice[3][1] = dice[1][0];
            dice[1][0] = dice[1][1];
            dice[1][1] = dice[1][2];
            dice[1][2] = temp;
        } else if (dir == 2) {
            int temp = dice[0][1];
            dice[0][1] = dice[3][1];
            dice[3][1] = dice[2][1];
            dice[2][1] = dice[1][1];
            dice[1][1] = temp;
        } else {
            int temp = dice[0][1];
            dice[0][1] = dice[1][1];
            dice[1][1] = dice[2][1];
            dice[2][1] = dice[3][1];
            dice[3][1] = temp;
        }

        // 주사위가 도착한 칸 (x, y)에 대한 점수 획득
        score += bfs(x, y, map[x][y]) * map[x][y];

        // 주사위 아랫면과 주사위가 있는 칸(x, y)를 비교하여 다음 이동 방향을 결정한다.
        int a = dice[3][1];
        int b = map[x][y];
        if (a > b) {
            if (dir == 0)
                dir = 2;
            else if (dir == 2)
                dir = 1;
            else if (dir == 1)
                dir = 3;
            else
                dir = 0;
        } else if (a < b) {
            if (dir == 0)
                dir = 3;
            else if (dir == 3)
                dir = 1;
            else if (dir == 1)
                dir = 2;
            else
                dir = 0;
        }
    }

    printf("%d\n", score);
    return 0;
}
