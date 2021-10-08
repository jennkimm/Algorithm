#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int r, c, m;
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,1,-1 };
struct shark {
	int r;
	int c;
	int s;
	int d;
	int z;
};
queue<pair<int, int>> sPos;
long long ans = 0;
deque<shark> arr[102][102];

void Move(int& i, int& j, int& d, int md)
{
	int ni, nj;
	while (md > 0)
	{
		ni = i + dx[d], nj = j + dy[d];
		if (ni <= r && nj <= c && ni >= 1 && nj >= 1)
		{
			i = ni; j = nj;
			md--;
		}
		else
		{
			if (d == 1) d = 2;
			else if (d == 2) d = 1;
			else if (d == 3) d = 4;
			else if (d == 4) d = 3;
		}
	}
}

int main() {
	scanf("%d %d %d", &r, &c, &m);

	for(int i = 0; i < m; ++i) {
		shark tmp;
		scanf("%d %d %d %d %d", &tmp.r, &tmp.c, &tmp.s, &tmp.d, &tmp.z);
		//v.push_back(tmp);
		arr[tmp.r][tmp.c].push_back(tmp);
	}

	// c 니까
	// 0 ~ c - 1 열
	int nk = 0;
	while(1) {
		nk++;
		//sort(v.begin(), v.end(), cmp);

		// 해당 열에 있는 땅에 가장 가까운 상어 잡아먹는다.
		// i열에 상어가 있는가? -> 있으면 없앤다.
		for(int i = 1; i <= r; ++i) {
			if (!arr[i][nk].empty()) {
				ans += arr[i][nk].front().z;
				arr[i][nk].pop_front();
				break;
			}
		}

		for(int i = 1; i <= r; ++i) {
			for(int j = 1; j <= c; ++j) {
				if (!arr[i][j].empty()) {
					sPos.push({i, j});
				}
			}
		}

		// 상어가 이동
		pair<int, int> temp; int i, j;
		shark ts;
		while (!sPos.empty()) {
			temp = sPos.front();
			sPos.pop();
			i = temp.first; j = temp.second;
			int md;
			ts = arr[i][j].front();
			arr[i][j].pop_front();
			if (ts.d == 1 || ts.d == 2)
				md = ts.s % (2 * (r-1));
			else
				md = ts.s % (2 * (c-1));
			Move(i, j, ts.d, md);
			arr[i][j].push_back(ts);
		}

		for(int g = 1; g <= r; ++g) {
			for(int h = 1; h <= c; ++h) {
				int max_z = 0, max_k = 0;
				if(arr[g][h].size() > 1) {
					for (deque<shark>::size_type k = 0; k < arr[g][h].size(); k++)
					{
						if (arr[g][h][k].z > max_z) { max_k = k; max_z = arr[g][h][k].z; }
					}
					shark temp = arr[g][h][max_k];
					arr[g][h].clear();
					arr[g][h].push_back(temp);
				}
			}
		}

		if(nk == c)
			break;
	}

	printf("%lld\n", ans);
	return 0;
}
