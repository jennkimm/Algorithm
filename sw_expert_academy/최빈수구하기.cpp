#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	int num;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &num);
		printf("#%d ", num);

		map<int, int> m;

		pair<int, int> max_cnt;
		max_cnt.first = 0;
		max_cnt.second = 0;
		for(int i = 0; i < 1000; ++i) {
			int score;
			scanf("%d", &score);
			if (m.find(score) == m.end()) {
				m.insert(make_pair(score, 1));
			} else {
				m.find(score)->second++;
				if (m.find(score)->second > max_cnt.second) {
					max_cnt.first = score;
					max_cnt.second = m.find(score)->second;
				} else if (m.find(score)->second == max_cnt.second) {
					if (max_cnt.first < score) {
						max_cnt.first = score;
					}
				}
			}
		}

		printf("%d\n", max_cnt.first);
	}
	return 0; //정상종료시 반드시 0을 리턴해야합니다.
}
