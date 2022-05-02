#include <stdio.h>
#include <vector>

using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

int tx[] = {1, -1, 1, -1};
int ty[] = {1, -1, -1, 1};

int main() {
    int n, m, k, c;
    int total = 0;
    vector<vector<int>> bak;
    bak.assign(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> fire;
    fire.assign(n + 1, vector<int>(n + 1, 0));

    scanf("%d %d %d %d", &n, &m, &k, &c);

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &bak[i][j]);
        }
    }

    while (m > 0) {
        // 잡초 성장
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (bak[i][j] > 0) {
                    // 주변 잡초 있는 칸 갯수 세기
                    int cnt = 0;
                    for(int dir = 0; dir < 4; ++dir) {
                        int nx = i + dx[dir];
                        int ny = j + dy[dir];
                        if (nx < 1 || nx > n || ny < 1 || ny > n) {
                            continue;
                        } else if (bak[nx][ny] > 0) {
                            cnt++;
                        }
                    }
                    bak[i][j] += cnt;
                }
            }
        }

        // printf("잡초성장\n");
        // for(int i = 1; i <= n; ++i) {
        //     for(int j = 1; j <= n; ++j) {
        //         printf("%d ", bak[i][j]);
        //     }
        //     printf("\n");
        // }

        // 잡초 증식
        vector<vector<int>> nbak;
        nbak.assign(n + 1, vector<int>(n + 1, 0));
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (bak[i][j] > 0) {
                    int cnt = 0; // 주변에 나눠줄 수 있는 칸 갯수
                    // vector<pair<int, int>> ppos(4);
                    for(int dir = 0; dir < 4; ++dir) {
                        int nx = i + dx[dir];
                        int ny = j + dy[dir];
                        if (nx < 1 || nx > n || ny < 1 || ny > n) {
                            continue;
                        } else if (bak[nx][ny] == 0 && fire[nx][ny] == 0) { // 비었고 불씨 없으면
                            cnt++;
                            // ppos.push_back(make_pair(nx, ny));
                            //  printf("%d %d\n", nx, ny);
                        }
                    }
                    for(int dir = 0; dir < 4; ++dir) {
                        int nx = i + dx[dir];
                        int ny = j + dy[dir];
                        if (nx < 1 || nx > n || ny < 1 || ny > n) {
                            continue;
                        } else if (bak[nx][ny] == 0 && fire[nx][ny] == 0) { // 비었고 불씨 없으면
                            nbak[nx][ny] += bak[i][j] / cnt;
                        }
                    }
                }
            }
        }

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if (nbak[i][j] > 0) {
                    bak[i][j] += nbak[i][j];
                }
            }
        }
        // printf("잡초증식\n");
        // for(int i = 1; i <= n; ++i) {
        //     for(int j = 1; j <= n; ++j) {
        //         printf("%d ", bak[i][j]);
        //     }
        //     printf("\n");
        // }

        // 불에 탄다
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <=n; ++j) {
                if (fire[i][j] > 0)
                    fire[i][j]--;
            }
        }

        // 불씨
        int fireX, fireY;
        bool flag = false;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <=n; ++j) {
                if (bak[i][j] > 0)  {
                    flag = true;
                    break;
                }
            }
            if (flag)
                break;
        }

        if (flag) {
            int max_sum = 0;
            for(int a = 1; a <= n; ++a) {
                for(int b = 1; b <= n; ++b) {
                    int sum = 0;
                    if (bak[a][b] > 0) {
                        sum += bak[a][b];
                        for(int i = 0; i < 4; ++i) {
                            for(int j = 1; j <= k; ++j) {
                                int nx = a + j * tx[i];
                                int ny = b + j * ty[i];
                                if (nx < 1 || nx > n || ny < 1 || ny > n) {
                                    continue;
                                } else if (bak[nx][ny] == -1) {
                                    break;
                                } else if (bak[nx][ny] == 0) {
                                    break;
                                } else if (bak[nx][ny] > 0) {
                                    sum += bak[nx][ny];
                                }
                            }
                        }
                        if (max_sum < sum) {
                            max_sum = sum;
                            fireX = a;
                            fireY = b;
                        }
                    }
                }
            }

            total += bak[fireX][fireY];
            bak[fireX][fireY] = 0;
            fire[fireX][fireY] = c;
            for(int i = 0; i < 4; ++i) {
                for(int j = 1; j <= k; ++j) {
                    int nx = fireX + j * tx[i];
                    int ny = fireY + j * ty[i];
                    if (nx < 1 || nx > n || ny < 1 || ny > n) {
                        continue;
                    } else if (bak[nx][ny] == -1) {
                        break;
                    } else if (bak[nx][ny] == 0) {
                        fire[nx][ny] = c;
                        break;
                    } else if (bak[nx][ny] > 0) {
                        fire[nx][ny] = c;
                        total += bak[nx][ny];
                        bak[nx][ny] = 0;
                    }
                }
            }
        }

        // printf("불탄 후\n");
        // for(int i = 1; i <= n; ++i) {
        //     for(int j = 1; j <= n; ++j) {
        //         printf("%d ", bak[i][j]);
        //     }
        //     printf("\n");
        // }

        m--;
    }
    printf("%d\n", total);
    return 0;
}
