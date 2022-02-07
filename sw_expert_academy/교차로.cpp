#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX_INF = 1000000001;
int main(int argc, char** argv)
{
	int n;
	int max_t, min_t;
	scanf("%d", &n);

	queue<pair<int, int>> a; // index, time
	queue<pair<int, int>> b;
	queue<pair<int, int>> c;
	queue<pair<int, int>> d;
	vector<int> answer;
	answer.assign(n + 1, -1);

	for(int i = 0; i < n; ++i) {
		int temp;
		char ch;
		scanf("%d %c", &temp, &ch);
		if (ch == 'A') {
			a.push({i, temp});
		} else if (ch == 'B') {
			b.push({i, temp});
		} else if (ch == 'C') {
			c.push({i, temp});
		} else if (ch == 'D') {
			d.push({i, temp});
		}
		if (i == 0)
			min_t = temp;
		else if (i == (n - 1))
			max_t = temp;
	}

	int cur_time = min_t;

	while(!a.empty() || !b.empty() || !c.empty() || !d.empty()) {
		//printf("cur_time = %d\n", cur_time);
		int a_min = MAX_INF;
		int b_min = MAX_INF;
		int c_min = MAX_INF;
		int d_min = MAX_INF;
		if (!a.empty())
			a_min = a.front().second;
		if (!b.empty())
			b_min = b.front().second;
		if (!c.empty())
			c_min = c.front().second;
		if (!d.empty())
			d_min = d.front().second;
		if ((a_min < cur_time) || (b_min < cur_time) || (c_min < cur_time) || (d_min < cur_time)) {
		} else {
			cur_time = min({a_min, b_min, c_min, d_min});
		}

		// 각 큐를 돌아가면서 검사
		bool isA_Possible = false;
		bool isB_Possible = false;
		bool isC_Possible = false;
		bool isD_Possible = false;

		// 교착상태 검사
		bool isA_Stuck = false;
		bool isB_Stuck = false;
		bool isC_Stuck = false;
		bool isD_Stuck = false;

		if (!a.empty()) {
			if(d.empty() && a.front().second <= cur_time) {
				isA_Possible = true;
			}
			if (!d.empty() && d.front().second > cur_time && a.front().second <= cur_time) {
				isA_Possible = true;
			}
			if (!isA_Possible && a.front().second <= cur_time) {
				isA_Stuck = true;
			}
		}
		if (!d.empty()) {
			if(c.empty() && d.front().second <= cur_time) {
				isD_Possible = true;
			}
			if (!c.empty() && c.front().second > cur_time && d.front().second <= cur_time) {
				isD_Possible = true;
			}
			if (!isD_Possible && d.front().second <= cur_time) {
				isD_Stuck = true;
			}
		}
		if (!c.empty()) {
			if(b.empty() && c.front().second <= cur_time) {
				isC_Possible = true;
			}
			if (!b.empty() && b.front().second > cur_time && c.front().second <= cur_time) {
				isC_Possible = true;
			}
			if (!isC_Possible && c.front().second <= cur_time) {
				isC_Stuck = true;
			}
		}
		if (!b.empty()) {
			if(a.empty() && b.front().second <= cur_time) {
				isB_Possible = true;
			}
			if (!a.empty() && a.front().second > cur_time && b.front().second <= cur_time) {
				isB_Possible = true;
			}
			if (!isB_Possible && b.front().second <= cur_time) {
				isB_Stuck = true;
			}
		}
		// 교착상태인지 검사
		if (isA_Stuck && isB_Stuck && isC_Stuck && isD_Stuck)
			break;
		if (isA_Possible) {
			answer[a.front().first] = cur_time;
			a.pop();
		}
		if (isB_Possible) {
			answer[b.front().first] = cur_time;
			b.pop();
		}
		if (isC_Possible) {
			answer[c.front().first] = cur_time;
			c.pop();
		}
		if (isD_Possible) {
			answer[d.front().first] = cur_time;
			d.pop();
		}
		cur_time++;
	}

	for(int i = 0; i < n; ++i) {
		printf("%d\n", answer[i]);
	}

	return 0;
}
