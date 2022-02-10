#include <string>
#include <vector>
#include <map>

using namespace std;

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = true;
    int m = key.size();
    int n = lock.size();

    // 열쇠 90 회전
    for(int i = 0; i <= 4; ++i) {
        vector<vector<int>> nKey;
        nKey.assign(key.size(), vector<int>(key.size(), 0));

        for(int j = m - 1; j >= 0; --j) {
            for(int k = 0; k < m; ++k) {
                nKey[k][(m - 1) - j] = key[j][k];
            }
        }

        // 열쇠를 이동시키며 검사
        vector<vector<int>> board;
        board.assign(2 * (m - 1) + n, vector<int>(2 * (m - 1) + n, -1));
        // 자물쇠는 m - 1 위치에 고정
        // 열쇠는 0 ~ (n + m - 1)

        for(int u = 0; u < n + m - 1; ++u) {
            for(int v = 0; v < n + m - 1; ++v) {

                for(int j = 0; j < m; ++j) {
                    for(int k = 0; k < m; ++k) {
                        board[u + j][v + k] = nKey[j][k];
                    }
                }

                // board 와 lock 검사
                // board (m - 1) ~ (n + m - 2)
                // lock 0 ~ n - 1
                bool isPossible = true;
                for(int j = 0; j < n; ++j) {
                    for(int k = 0; k < n; ++k) {
                        if (board[j + m - 1][k + m - 1] != -1) {
                            // printf("board의 %d %d , lock의 %d %d \n", j + m - 1, k + m - 1, j, k);
                            if (lock[j][k] == 0 && board[j + m - 1][k + m - 1] != 1) {
                                isPossible = false;
                                break;
                            }
                            if (lock[j][k] == 1 && board[j + m - 1][k + m - 1] != 0) {
                                isPossible = false;
                                break;
                            }
                        } else if (lock[j][k] == 0) {
                            isPossible = false;
                            break;
                        }
                    }
                    if (!isPossible)
                        break;
                }
                if (isPossible)
                    return true;

                // board clear
                board.assign(2 * (m - 1) + n, vector<int>(2 * (m - 1) + n, -1));
            }
        }

        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < m; ++k) {
                key[j][k] = nKey[j][k];
            }
        }
    }
    answer = false;
    return answer;
}
