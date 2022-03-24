#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, k, ans;
	int mmin = 0;
	int mmax = 10001;
	ans = 0;
	scanf("%d %d", &n, &k);

	vector<int> v;

	for(int i = 0; i < n; ++i) {
		int temp;
		scanf("%d", &temp);
		v.push_back(temp);
	}

	while (mmax - mmin > k) {
		mmax = 0;
		mmin = 10001;
		int min_fish = 10001;
		for(int i = 0; i < n; ++i) {
			if (min_fish > v[i]) {
				min_fish = v[i];
			}
		}

		// 가장 적은 어항에 물고기를 한마리 넣는다.
		for(int i = 0; i < n; ++i) {
			if (v[i] == min_fish) {
				v[i]++;
			}
		}

		for(int i = 0; i < n; ++i) {
			printf("%d ", v[i]);
		}
		printf("\n");

		// 공중부양 작업
		// 1 1 2 2 3 3 ...
		vector<vector<int>> ball;
		ball.assign(100, vector<int>());
		for(int i = 0; i < n - 1; ++i) {
			ball[0].push_back(v[i + 1]);
		}
		ball[1].push_back(v[0]);

		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < ball[i].size(); ++j) {
				printf("%d ", ball[i][j]);
			}
			printf("\n");
		}

		int height = 2;
		int width = v.size() - 1;
		while (height <= width) {
			int base = ball[1].size();
			for(int i = ball[1].size() - 1; i >= 0; --i) {
				// i번째 줄을 base 부터 포갠다.
				for(int j = 0; j < height; ++j) {
					ball[base - i].push_back(ball[j][i]);
				}
			}
			// 앞에 부분 조정
			for(int i = 0; i < height; ++i) {
				for(int j = 0; j < base; ++j) {
					ball[i].erase(ball[i].begin());
				}
			}

			// height, width 갱신
			for(int i = 0; i < ball.size(); ++i) {
				if (ball[i].size() == 0) {
					height = i;
					break;
				}
			}
			width = ball[0].size() - ball[1].size();
		}

		// 어항 물고기 수 조절
		vector<vector<int>> copyball;
		copyball.assign(height, vector<int>());
		for(int i = 0; i < height; ++i) {
			for(int j = 0; j < ball[i].size(); ++j) {
				copyball[i].push_back(ball[i][j]);
			}
		}

		// 가로 인접
		for(int i = 0; i < height; ++i) {
			for(int j = 0; j < ball[i].size() - 1; ++j) {
				// ball[i][j] 와 ball[i][j + 1] 차이 구하기
				if (ball[i][j] < ball[i][j + 1]) {
					int d = (ball[i][j + 1] - ball[i][j]) / 5;
					if (d > 0) {
						copyball[i][j + 1] -= d;
						copyball[i][j] += d;
					}
				} else if (ball[i][j] == ball[i][j + 1]) {

				} else {
					int d = (ball[i][j] - ball[i][j + 1]) / 5;
					if (d > 0) {
						copyball[i][j] -= d;
						copyball[i][j + 1] += d;
					}
				}
			}
		}

		// 세로 인접
		for(int i = 0; i < height - 1; ++i) {
			for(int j = 0; j < ball[1].size(); ++j) {
				if (ball[i][j] < ball[i + 1][j]) {
					int d = (ball[i + 1][j] - ball[i][j]) / 5;
					if (d > 0) {
						copyball[i + 1][j] -= d;
						copyball[i][j] += d;
					}
				} else if (ball[i][j] == ball[i + 1][j]) {
					continue;
				} else {
					int d = (ball[i][j] - ball[i + 1][j]) / 5;
					if (d > 0) {
						copyball[i][j] -= d;
						copyball[i + 1][j] += d;
					}
				}
			}
		}

		// 바닥에 일렬로 놓기
		vector<int> vline;
		for(int j = 0; j < copyball[0].size() - width; ++j) {
			for(int i = 0; i < height; ++i) {
				if (copyball[i].size() > j)
					vline.push_back(copyball[i][j]);
				else
					break;
			}
		}
		for(int j = copyball[0].size() - width; j < copyball[0].size(); ++j) {
			vline.push_back(copyball[0][j]);
		}

		vector<vector<int>> nball;
		nball.assign(2, vector<int>());

		// n/2개 180도 회전해서 위에 포개기
		for(int i = (n / 2) - 1; i >= 0; --i) {
			nball[0].push_back(vline[i]);
		}
		for(int i = n / 2; i < n; ++i) {
			nball[1].push_back(vline[i]);
		}

		vector<vector<int>> nball2;
		nball2.assign(4, vector<int>());

		// n/4개 180도 회전해서 위에 포개기
		for(int i = n / 4 - 1; i >= 0; --i) {
			nball2[0].push_back(nball[1][i]);
			nball2[1].push_back(nball[0][i]);
		}
		for(int i = n / 4; i < n / 2; ++i) {
			nball2[2].push_back(nball[0][i]);
			nball2[3].push_back(nball[1][i]);
		}

		// 물고기 조절작업
		// 어항 물고기 수 조절
		vector<vector<int>> copyball2;
		copyball2.assign(4, vector<int>(n / 4, 0));
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < nball2[i].size(); ++j) {
				copyball2[i][j] = nball2[i][j];
			}
		}

		// 가로 인접
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < n / 4 - 1; ++j) {
				// ball[i][j] 와 ball[i][j + 1] 차이 구하기
				if (nball2[i][j] < nball2[i][j + 1]) {
					int d = (nball2[i][j + 1] - nball2[i][j]) / 5;
					if (d > 0) {
						copyball2[i][j + 1] -= d;
						copyball2[i][j] += d;
					}
				} else if (nball2[i][j] == nball2[i][j + 1]) {
					continue;
				} else {
					int d = (nball2[i][j] - nball2[i][j + 1]) / 5;
					if (d > 0) {
						copyball2[i][j] -= d;
						copyball2[i][j + 1] += d;
					}
				}
			}
		}
		// 세로 인접
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < n / 4; ++j) {
				// ball[i][j] ball[i + 1][j]
				if (nball2[i][j] < nball2[i + 1][j]) {
					int d = (nball2[i + 1][j] - nball2[i][j]) / 5;
					if (d > 0) {
						copyball2[i + 1][j] -= d;
						copyball2[i][j] += d;
					}
				} else if (nball2[i][j] == nball2[i + 1][j]) {
					continue;
				} else {
					int d = (nball2[i][j] - nball2[i + 1][j]) / 5;
					if (d > 0) {
						copyball2[i][j] -= d;
						copyball2[i + 1][j] += d;
					}
				}
			}
		}

		v.clear();

		for(int i = 0; i < n / 4; ++i) {
			for(int j = 3; j >= 0; --j) {
				v.push_back(copyball2[j][i]);
				if (copyball2[j][i] > mmax) {
					mmax = copyball2[j][i];
				}
				if (copyball2[j][i] < mmin) {
					mmin = copyball2[j][i];
				}
			}
		}
		ans++;
	}

	printf("%d\n", ans);
	return 0;
}
