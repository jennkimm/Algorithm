#include <stdio.h>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <stack>

using namespace std;

int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, 1, -1, 0, 0};

int n, k;
struct mal{
	int x;
	int y;
	int dir;
};

int main() {
	scanf("%d %d", &n, &k);

	vector<vector<int>> m; // 체스판 정보
	vector<vector<deque<int>>> v; // 몇번 말이 어디에 위치해 있는지
	map<int, mal> mmal; // 말의 정보

	v.assign(n + 1, vector<deque<int>>(n + 1));
	m.assign(n + 1, vector<int>(n + 1));

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &m[i][j]);
		}
	}

	for(int i = 1; i <= k; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		v[a - 1][b - 1].push_back(i); // 번호
		mal temp;
		temp.x = a - 1;
		temp.y = b - 1;
		temp.dir = c;
		mmal.insert({i, temp});
	}

	int turn = 1;
	while(turn < 1001) {
		// 순서대로 말 이동
		bool flag = false;
		for(int i = 1; i <= k; ++i) {
			int cx = mmal.find(i)->second.x;
			int cy = mmal.find(i)->second.y;
			int nx = mmal.find(i)->second.x + dx[mmal.find(i)->second.dir];
			int ny = mmal.find(i)->second.y + dy[mmal.find(i)->second.dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) { // 범위를 벗어나는 경우
				int dir = mmal.find(i)->second.dir;
				if (dir == 1)
					mmal.find(i)->second.dir = 2;
				else if (dir == 2)
					mmal.find(i)->second.dir = 1;
				else if (dir == 3)
					mmal.find(i)->second.dir = 4;
				else if (dir == 4)
					mmal.find(i)->second.dir = 3;
				nx = mmal.find(i)->second.x + dx[mmal.find(i)->second.dir];
				ny = mmal.find(i)->second.y + dy[mmal.find(i)->second.dir];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)
				{
				} else if (m[nx][ny] == 0) { // 이동
					// 이동
					// 현재 있는 칸에 i번 말 포함 위에 얹어져 있는 말들을 같이 옮긴다.
					stack<int> s;
					while(v[cx][cy].back() != i) {
						s.push(v[cx][cy].back());
						mmal.find(v[cx][cy].back())->second.x = nx;
						mmal.find(v[cx][cy].back())->second.y = ny;
						v[cx][cy].pop_back();
					}
					s.push(i);
					v[cx][cy].pop_back();
					mmal.find(i)->second.x = nx;
					mmal.find(i)->second.y = ny;
					while(!s.empty()) {
						v[nx][ny].push_back(s.top());
						s.pop();
					}
				} else if (m[nx][ny] == 1) { // 이동
					queue<int> q;
					while(v[cx][cy].back() != i) {
						q.push(v[cx][cy].back());
						mmal.find(v[cx][cy].back())->second.x = nx;
						mmal.find(v[cx][cy].back())->second.y = ny;
						v[cx][cy].pop_back();
					}
					q.push(i);
					v[cx][cy].pop_back();
					mmal.find(i)->second.x = nx;
					mmal.find(i)->second.y = ny;
					while(!q.empty()) {
						v[nx][ny].push_back(q.front());
						q.pop();
					}
				}
			} else if (m[nx][ny] == 2) {
				int dir = mmal.find(i)->second.dir;
				if (dir == 1)
					mmal.find(i)->second.dir = 2;
				else if (dir == 2)
					mmal.find(i)->second.dir = 1;
				else if (dir == 3)
					mmal.find(i)->second.dir = 4;
				else if (dir == 4)
					mmal.find(i)->second.dir = 3;
				nx = mmal.find(i)->second.x + dx[mmal.find(i)->second.dir];
				ny = mmal.find(i)->second.y + dy[mmal.find(i)->second.dir];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)
				{
				} else if (m[nx][ny] == 0) { // 이동
					// 이동
					// 현재 있는 칸에 i번 말 포함 위에 얹어져 있는 말들을 같이 옮긴다.
					stack<int> s;
					while(v[cx][cy].back() != i) {
						s.push(v[cx][cy].back());
						mmal.find(v[cx][cy].back())->second.x = nx;
						mmal.find(v[cx][cy].back())->second.y = ny;
						v[cx][cy].pop_back();
					}
					s.push(i);
					v[cx][cy].pop_back();
					mmal.find(i)->second.x = nx;
					mmal.find(i)->second.y = ny;
					while(!s.empty()) {
						v[nx][ny].push_back(s.top());
						s.pop();
					}
				} else if (m[nx][ny] == 1) { // 이동
					queue<int> q;
					while(v[cx][cy].back() != i) {
						q.push(v[cx][cy].back());
						mmal.find(v[cx][cy].back())->second.x = nx;
						mmal.find(v[cx][cy].back())->second.y = ny;
						v[cx][cy].pop_back();
					}
					q.push(i);
					v[cx][cy].pop_back();
					mmal.find(i)->second.x = nx;
					mmal.find(i)->second.y = ny;
					while(!q.empty()) {
						v[nx][ny].push_back(q.front());
						q.pop();
					}
				}
			} else if (m[nx][ny] == 0) { // 흰색
				// 이동
				// 현재 있는 칸에 i번 말 포함 위에 얹어져 있는 말들을 같이 옮긴다.
				stack<int> s;
				while(v[cx][cy].back() != i) {
					s.push(v[cx][cy].back());
					mmal.find(v[cx][cy].back())->second.x = nx;
					mmal.find(v[cx][cy].back())->second.y = ny;
					v[cx][cy].pop_back();
				}
				s.push(i);
				v[cx][cy].pop_back();
				mmal.find(i)->second.x = nx;
				mmal.find(i)->second.y = ny;
				while(!s.empty()) {
					v[nx][ny].push_back(s.top());
					s.pop();
				}
			} else if (m[nx][ny] == 1) { // 빨간색
				// 이동
				// 현재 있는 칸에 i번 말 포함 위에 얹어져 있는 말들을 같이 옮긴다.
				queue<int> q;
				while(v[cx][cy].back() != i) {
					q.push(v[cx][cy].back());
					mmal.find(v[cx][cy].back())->second.x = nx;
					mmal.find(v[cx][cy].back())->second.y = ny;
					v[cx][cy].pop_back();
				}
				q.push(i);
				v[cx][cy].pop_back();
				mmal.find(i)->second.x = nx;
				mmal.find(i)->second.y = ny;
				while(!q.empty()) {
					v[nx][ny].push_back(q.front());
					q.pop();
				}
			}

			// 4개 이상 쌓이는 순간 게임 종료
			flag = false;
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < n; ++j) {
					if (v[i][j].size() >= 4) {
						flag = true;
						break;
					}
				}
				if (flag)
					break;
			}
			if (flag)
				break;
		}
		if (flag)
			break;
		turn++;
	}
	if (turn == 1001) {
		turn = -1;
	}
	printf("%d\n", turn);
	return 0;
}
