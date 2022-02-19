#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

int main(int argc, char** argv)
{
	int n, m;
	scanf("%d %d", &n, &m);
	// 구간 길이, 제한 속도
	vector<pair<int, int>> v;
	vector<pair<int, int>> test;

	for(int i = 0; i < n; ++i) {
		int length, velocity;
		scanf("%d %d", &length, &velocity);
		if (i == 0)
			v.push_back({length, velocity});
		else
			v.push_back({length + v[i - 1].first, velocity});
	}

	for(int i = 0 ; i < m; ++i) {
		int length, velocity;
		scanf("%d %d", &length, &velocity);
		if (i == 0)
			test.push_back({length, velocity});
		else
			test.push_back({length + test[i - 1].first, velocity});
	}

	// 50 70 78 100 j v
	// 60 78 100 i test
	int max_answer = 0;
	int v_base = 0;
	for(int i = 0; i < m; ++i) { // test
		for(int j = v_base; j < n; ++j) { // v
			if (v[j].first < test[i].first) {
				if (max_answer < (test[i].second - v[j].second))
					max_answer = test[i].second - v[j].second;
				continue;
			} else if (v[j].first == test[i].first) {
				if (max_answer < (test[i].second - v[j].second))
					max_answer = test[i].second - v[j].second;
				v_base = j + 1;
				break;
			} else {
				if (max_answer < (test[i].second - v[j].second))
					max_answer = test[i].second - v[j].second;
				v_base = j;
				break;
			}
		}
	}

	printf("%d\n", max_answer);

	return 0;
}
