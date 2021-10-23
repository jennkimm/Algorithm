#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int a, b;
int maxx = 0;
vector<int> num;

int calc() {
	int fnum = 0;
	int tmp = 1;
	for(int i = 0; i < num.size(); ++i) {
		fnum += num[i] * tmp;
		tmp *= 10;
	}
	return fnum;
}

void dfs(int idx, int cnt) {
	if (cnt == b) {
		maxx = max(maxx, calc());
		return;
	} else {
		for(int i = idx; i < num.size(); ++i) { // 기본 base를 설정하므로서 시간초과 방지.
			for(int j = i + 1; j < num.size(); ++j) {
				int temp = num[i];
				int temp2 = num[j];
				num[i] = num[j];
				num[j] = temp;
				dfs(i, cnt + 1);
				num[i] = temp;
				num[j] = temp2;
			}
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

	vector<int> ans;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d", &a, &b);

		while(a != 0) {
			num.push_back(a % 10);
			a = a / 10;
		}

		if (b > num.size()) // 바꾸는 횟수가 더 큰 경우 고려.
			b = num.size();

		dfs(0, 0);
		ans.push_back(maxx);
		maxx = 0; // 초기화 again
		num.clear(); // 초기화 again
	}
	for(int i = 1; i <= ans.size(); ++i) {
		printf("#%d %d\n", i, ans[i - 1]);
	}
	return 0; //정상종료시 반드시 0을 리턴해야합니다.
}
