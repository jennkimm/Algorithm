#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<set>
#include<cmath>
#include<algorithm>

using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

/**
 * 수식 계산 정수형인지 실수형인지 꼭 고려하기
 * 특히, pow, sqrt 등 계산 할 시애!!!
 * 해당 문제도 안전거리 계산 시 int -> double 로 변경 후 맞음
**/

int main(int argc, char** argv)
{
	int n, m, q;
	set<int> eating; // 먹고있는 애들 넣음
	set<int> ate; // 다 먹은애들 넣음
	scanf("%d %d %d", &n, &m, &q);
	vector<vector<int>> v; // n * m 좌석 2차원 배열
	v.assign(n + 1, vector<int>(m + 1, 0)); // 0으로 초기화. 좌석 배치 받으면 해당 자리 id로 세팅

	 for(int i = 0; i < q; ++i) {
	 	string inOrOut;
	 	int id;
	 	cin >> inOrOut >> id;

		if (inOrOut == "In") {
			if (eating.find(id) != eating.end()) {
				printf("%d already seated.\n", id);
				continue;
			}
			if (ate.find(id) != ate.end()) {
				printf("%d already ate lunch.\n", id);
				continue;
			}
			// 앉을 자리 있는지 검사
			bool isFull = true;
			// 0인 자리의 상하좌우 검사해서 상하좌우가 다 0이면 ok
			for(int j = 0; j < n; ++j) {
				for(int k = 0; k < m; ++k) {
					bool isYes = false;
					if (v[j][k] == 0) {
						isYes = true;
						int nx, ny;
						for(int l = 0; l < 4; ++l) {
							nx = j + dx[l];
							ny = k + dy[l];
							if (nx < 0 || nx > n || ny < 0 || ny > m) {
								continue;
							} else if (v[nx][ny] != 0) {
								isYes = false; // 상하좌우 중 0이 아닌 곳이 있다 -> (j, k) 는 앉을 수 없다.
								break;
							}
						}
					}
					// (j,k) 가 0 이고 상하좌우 0 이면 앉을 수 있는 자리다.
					if (isYes) {
						isFull = false; // 앉을 자리 있다.
						break;
					}
				}
				if (!isFull) {
					break;
				}
			}
			if (!isFull) {
				if (eating.size() == 0) { // 먹고 있는사람 0명이면
					v[0][0] = id;
					eating.insert(id);
					printf("%d gets the seat (1, 1).\n", id); // (1, 1)에 배치
				} else {
					double max_dist = 0; // 안전거리들 중 최대
					int px, py; // 앉을 자리 좌표
					for(int x = 0; x < n; ++x) {
						for(int y = 0; y < m; ++y) {
							if (v[x][y] == 0) { // (x, y) 가 빈자리 이면 (앉을 자리 후보)
								// (x, y)의 상하좌우 검사 -> 상하좌우가 0이 아니면 continue
								bool isYes = true;
								int nx, ny;
								for(int l = 0; l < 4; ++l) {
									nx = x + dx[l];
									ny = y + dy[l];
									if (nx < 0 || nx > n || ny < 0 || ny > m) {
										continue;
									} else if (v[nx][ny] != 0) {
										isYes = false;
										break;
									}
								}
								if (!isYes)
									continue;
								// 안전 거리 계산
								double min_dist = 100001; // 최소 거리 계산
								for(int a = 0; a < n; ++a) {
									for(int b = 0; b < m; ++b) {
										// (a, b)의 상하좌우를 검사
										if (v[a][b] != 0) {  // (a, b)에 사람이 앉아있으면
											double dist = sqrt(pow(y - b, 2) + pow(x - a, 2)); // 앉아 있는 사람들 간 거리 계산
											if (dist < min_dist) { // 최소 거리 갱신
												min_dist = dist;
											}
										}
									}
								}
								if (min_dist > max_dist) {
									max_dist = min_dist;
									px = x; // 행
									py = y; // 열
								}
							}
						}
					}
					v[px][py] = id;
					eating.insert(id);
					printf("%d gets the seat (%d, %d).\n", id, px + 1, py + 1);
				}
			} else {
				printf("There are no more seats.\n");
			}
		} else {
			if (ate.find(id) == ate.end() && eating.find(id) == eating.end()) {
				printf("%d didn't eat lunch.\n", id);
				continue;
			}
			if (ate.find(id) != ate.end()) {
				printf("%d already left seat.\n", id);
				continue;
			}
			if (eating.find(id) != eating.end()) {
				eating.erase(id);
				ate.insert(id); // 다 먹은 애들에 추가
				bool flag = false;
				for(int j = 0; j < n; ++j) {
					for(int k = 0; k < m; ++k) {
						if (v[j][k] == id) {
							v[j][k] = 0; // id 가 앉아있던 자리 다시 0 으로 세팅
							printf("%d leaves from the seat (%d, %d).\n", id, j + 1, k + 1);
							flag = true;
							break;
						}
					}
					if (flag)
						break;
				}
			}
		}
	}
	return 0;
}
