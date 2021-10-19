#include <stdio.h>
#include <vector>

using namespace std;
vector<vector<int>> map;
int dice[10];
int maxx = 0;
int lll = 0;

void dfs(int cnt, int order[10]) {
	if (cnt == 10) {
		lll++;
		int line[] = {0, 0, 0, 0}; // 위치해있는 노선
		int curr[] = {0, 0, 0, 0}; // 현재 위치
		int score = 0;
		for(int i = 0; i < 10; ++i) {
			// i번째 주사위 order[i] 는 dice[i] 만큼 앞으로 전진한다.
			// 도착 지점에 다른 말이 있으면 갈수가 없음. 단, 도착지점이면 갈 수 있다.
			if (line[order[i]] == -1) { // 이미 도착한 주사위를 사용하려 한다면
				return;
			} else if (curr[order[i]] + dice[i] > map[line[order[i]]].size() - 1) { // 도착.
				curr[order[i]] = map[line[order[i]]].size() - 1;
				line[order[i]] = -1;
			} else if (map[line[order[i]]].size() - 1 > curr[order[i]] + dice[i]) { // 도착지점이 도착이 아니라면.
				curr[order[i]] += dice[i];
				if (map[line[order[i]]][curr[order[i]]] == 10) {
					line[order[i]] = 1;
				} else if (map[line[order[i]]][curr[order[i]]] == 20) {
					line[order[i]] = 2;
				} else if (map[line[order[i]]][curr[order[i]]] == 30 && line[order[i]] == 0) {
					line[order[i]] = 3;
				}
				for(int j = 0; j < 4; ++j) {
					// 다른 주사위가 현재 위치한 곳의 점수와 도착할 칸의 점수가 같은지 비교
					if (j != order[i] && line[order[i]] == line[j] && curr[j] == curr[order[i]] && line[order[i]] != -1 && line[j] != -1)
						return;
					else if (j != order[i] && line[order[i]] != -1 && line[j] != -1 && map[line[j]][curr[j]] == 25 && map[line[order[i]]][curr[order[i]]] == 25) { // 라인이 달라도 만나는 곳 있음...
						return;
					}
					else if (j != order[i] && line[order[i]] != -1 && line[j] != -1 && map[line[j]][curr[j]] == 35 && map[line[order[i]]][curr[order[i]]] == 35) {
						return;
					}
					else if (j != order[i] && line[order[i]] != -1 && line[j] != -1 && map[line[j]][curr[j]] == 40 && map[line[order[i]]][curr[order[i]]] == 40) {
						return;
					}
					else if (j != order[i] && line[order[i]] != -1 && line[j] != -1 &&
						((line[j] == 3 && curr[j] == 20) || (line[j] == 1 && curr[j] == 10) || (line[j] == 2 && curr[j] == 14)) &&
						((line[order[i]] == 3 && curr[order[i]] == 20) || (line[order[i]] == 1 && curr[order[i]] == 10) || (line[order[i]] == 2 && curr[order[i]] == 14)) // 30은 좀 특별히 처리..
					)
						return;
				}
				score += map[line[order[i]]][curr[order[i]]];
			} else {
				return;
			}
		}
		if (maxx < score) {
			maxx = score;
		}
		return;
	} else {
		for(int i = 0; i < 4; ++i) {
			order[cnt] = i;
			dfs(cnt + 1, order);
		}
	}
}

int main() {

	map.push_back(vector<int>(22));
	map.push_back(vector<int>(14));
	map.push_back(vector<int>(18));
	map.push_back(vector<int>(24));

	for(int i = 1; i < 21; ++i) {
		map[0][i] = 2 * i;
	}
	map[0][21] = 4000;

	map[1][5] = 10;
	map[1][6] = 13;
	map[1][7] = 16;
	map[1][8] = 19;
	map[1][9] = 25;
	map[1][10] = 30;
	map[1][11] = 35;
	map[1][12] = 40;
	map[1][13] = 1000;

	map[2][10] = 20;
	map[2][11] = 22;
	map[2][12] = 24;
	map[2][13] = 25;
	map[2][14] = 30;
	map[2][15] = 35;
	map[2][16] = 40;
	map[2][17] = 2000;

	map[3][15] = 30;
	map[3][16] = 28;
	map[3][17] = 27;
	map[3][18] = 26;
	map[3][19] = 25;
	map[3][20] = 30;
	map[3][21] = 35;
	map[3][22] = 40;
	map[3][23] = 3000;

	for(int i = 0; i < 10; ++i) {
		scanf("%d", &dice[i]);
	}

	// 0, 1, 2, 3 숫자를 10번 중복 상관없이 고르는 경우의 수
	int order[10];
	dfs(0, order);

	printf("%d\n", maxx);
	return 0;
}
