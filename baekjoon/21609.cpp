#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

struct block {
    int size; // 블록 사이즈
    int rainbow_cnt; // 무지개블록 갯수
    int r; // 기준 블록 행
    int c; // 기준 블록 열
    vector<vector<int>> blck;
};
vector<block> bgroup;
vector<vector<int>> board;
int n, m;

bool cmp(block &a, block &b) {
    if (a.size == b.size) {
        if (a.rainbow_cnt == b.rainbow_cnt) {
            if (a.r == b.r) {
                return a.c > b.c;
            } else
                return a.r > b.r;
        } else
            return a.rainbow_cnt > b.rainbow_cnt;
    } else
        return a.size > b.size;
}

void searchBlockGroup(int x, int y, int color, vector<vector<bool>> &visited) {
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    block b;
    b.size = 1;
    b.rainbow_cnt = 0;
    b.r = x;
    b.c = y;
    b.blck.assign(n+1, vector<int>(n+1, 0));
    b.blck[x][y] = 1;
    printf("visit %d %d\n", x, y);
    while(!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n) {
                continue;
            } else if (!visited[nx][ny] && (board[nx][ny] == 0 || board[nx][ny] == color)) {
                printf("[visit %d %d]\n", nx, ny);
                q.push({nx, ny});
                visited[nx][ny] = true;
                b.blck[nx][ny] = 1;
                b.size++;
                if (board[nx][ny] == 0)
                    b.rainbow_cnt++;
            }
        }
    }
    printf("--\n");
    if (b.size > 1) {
        printf("%d %d 추가\n", b.r, b.c);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (b.blck[i][j] == 1 && board[i][j] == 0)
                    visited[i][j] = false;
            }
        }
        bgroup.push_back(b);
    }
    return;
}

int main() {
    // 비어있는 곳 -2
    // 검은색 블록 -1
    // 무지개 블록 0
    // 일반 블록 1 ~ M
    int score = 0;
    scanf("%d %d", &n, &m);
    board.assign(n+1, vector<int>(n+1, 0));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &board[i][j]);
        }
    }

    // 블록 그룹 - 서로 인접한 무지개 블록 && 색깔이 같은 일반 블록 
    // 기준 블록 - 무지개 블록 아닌 것 중 행 번호 가장 작은거 (같으면 열 번호 가장 작은거)

    //블록그룹 있는 동안 오토 플레이 반복
    int cnt = 0;
    do {
        cnt++;
        bgroup.clear();
        // 블록 그룹 찾기
        vector<vector<bool>> visited;
        visited.assign(n+1, vector<bool>(n+1, false));
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (board[i][j] > 0 && board[i][j] <= m && !visited[i][j]) {
                    searchBlockGroup(i, j, board[i][j], visited);
                }
            }
        }
        if (bgroup.size() == 0)
            break;
        // 크기가 가장 큰 블록 그룹을 찾는다. 그러한 블록 그룹이 여러 개라면 포함된 무지개 블록의 수가 가장 많은 블록 그룹, 그러한 블록도 여러개라면 기준 블록의 행이 가장 큰 것을, 그 것도 여러개이면 열이 가장 큰 것을 찾는다.
        sort(bgroup.begin(), bgroup.end(), cmp);
        // 1에서 찾은 블록 그룹의 모든 블록을 제거한다. 블록 그룹에 포함된 블록의 수를 B라고 했을 때, B^2점을 획득한다.

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (bgroup[0].blck[i][j] == 1)
                    board[i][j] = -2;
            }
        }

        score += bgroup[0].size * bgroup[0].size;

        // 격자에 중력이 작용한다. -> 검은 블록 제외하고 아래로 이동
        vector<vector<int>> nboard;
        nboard.assign(n+1, vector<int>(n+1, -2));
        for(int i = 1; i <= n; ++i) { // 열
            stack<int> s;
            for(int j = 1; j <= n; ++j) { // 행
                if (board[j][i] == -1) {
                    nboard[j][i] = -1;
                    int base = j - 1;
                    while(!s.empty()) {
                        nboard[base][i] = s.top();
                        s.pop();
                        base--;
                    }
                } else if (board[j][i] != -2) {
                    s.push(board[j][i]);
                }
            }
            if (!s.empty()) {
                int base = n;
                while(!s.empty()) {
                    nboard[base][i] = s.top();
                    s.pop();
                    base--;
                }
            }
        }

        copy(nboard.begin(), nboard.end(), board.begin());

        // 격자가 90도 반시계 방향으로 회전한다.
        nboard.assign(n+1, vector<int>(n+1, 0));
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j) {
                nboard[i][j] = board[j][n-i+1];
            }
        }
        
        copy(nboard.begin(), nboard.end(), board.begin());

        // 다시 격자에 중력이 작용한다.
        nboard.assign(n+1, vector<int>(n+1, -2));
        for(int i = 1; i <= n; ++i) { // 열
            stack<int> s;
            for(int j = 1; j <= n; ++j) { // 행
                if (board[j][i] == -1) {
                    nboard[j][i] = -1;
                    int base = j - 1;
                    while(!s.empty()) {
                        nboard[base][i] = s.top();
                        s.pop();
                        base--;
                    }
                } else if (board[j][i] != -2) {
                    s.push(board[j][i]);
                }
            }
            if (!s.empty()) {
                int base = n;
                while(!s.empty()) {
                    nboard[base][i] = s.top();
                    s.pop();
                    base--;
                }
            }
        }

        copy(nboard.begin(), nboard.end(), board.begin());
    } while(!bgroup.empty());

    printf("%d\n", score);
    return 0;
}