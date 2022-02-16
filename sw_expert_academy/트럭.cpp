#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

bool cmp(pair<int, int> &a, pair<int, int> &b) {
	return a.second < b.second;
}

int main(int argc, char** argv)
{
	int n; // 소비자 수
	scanf("%d", &n);
	map<int, vector<pair<int, int>>> m; // key - 사이즈, value - {가격, 소비자}
	map<int, int> memo; // size, max cost
	int maxvalue = 0;

	for(int i = 1; i <= n; ++i) {
		int a;
		scanf("%d", &a);
		int maxcost = 0;
		for(int j = 0; j < a; ++j) {
			int size, price;
			scanf("%d %d", &size, &price);
			if (maxcost < price) {
				maxcost = price;
			}
			if (m.find(size) == m.end()) {
				vector<pair<int, int>> temp;
				temp.push_back({price, i});
				m.insert({size, temp});
			} else {
				m.find(size)->second.push_back({price, i});
			}
		}
		maxvalue += maxcost;
	}

	// 매출에 따라 신차 크기를 최소 얼마로 설정해야 하는지 구하자.
	// 신차 크기 - 매출 -> map 으로 저장
	int q;
	scanf("%d", &q);
	vector<pair<int, int>> gc;
	for(int k = 0; k < q; ++k) {
		int goal;
		scanf("%d", &goal);
		gc.push_back({k, goal});
	}

	sort(gc.begin(), gc.end(), cmp);

	vector<int> answer(gc.size());

	// 이전까지 검사한 size 와 매출 저장
	auto jj = m.begin();
	int sofarcost = 0;
	for(int i = 0; i < gc.size(); ++i) {
		map<int, pair<int, int>> hubo; // key - 소비자, value - {사이즈, 가격}
		int cur_cost = sofarcost;
		bool flag = false;

		if (maxvalue < gc[i].second) {
			answer[gc[i].first] = -1;
			continue;
		}

		// 이전꺼랑 목표 매출이 같다면
		if (i >= 1 && gc[i].second == gc[i-1].second){
			answer[gc[i].first] = answer[gc[i-1].first];
			continue;
		}

		for(auto j = m.begin(); j != m.end(); ++j) { // 사이즈가 작은 순서대로 돌면서
			int p;
			printf("%d 사이즈부터 검사시작, ", j->first);
			for(p = 0; p < j->second.size(); ++p) {
				// j->first 사이즈
				// j->second[p]->first 가격
				// j->second[p]->second 소비자
				if (hubo.find(j->second[p].second) == hubo.end()) {
					hubo.insert({j->second[p].second, {j->first, j->second[p].first}});
					cur_cost += j->second[p].first;
				} else if (hubo.find(j->second[p].second)->second.second < j->second[p].first) {
					// 갱신
					cur_cost -= hubo.find(j->second[p].second)->second.second;
					cur_cost += j->second[p].first;
					hubo.find(j->second[p].second)->second.first = j->first;
					hubo.find(j->second[p].second)->second.second = j->second[p].first;
				}

				if (cur_cost >= gc[i].second) {
					//printf("%d %d %d\n", cur_cost, gc[i].second, gc[i].first);
					// 성공
					// 처음 성공?
					// 신차 사이즈 최소 찾기
					int max_size = 0;
					for(auto k = hubo.begin(); k != hubo.end(); ++k) {
						if(max_size < k->second.first) {
							max_size = k->second.first;
						}
					}
					answer[gc[i].first] = max_size;
					flag = true;
					break;
				}
			}
			//printf("p = %d, j->second.size() = %lu\n", p, j->second.size());
			if (flag)
				break;
		}

		if (cur_cost < gc[i].second) {
			// 실패
			answer[gc[i].first] = -1;
		}
	}

	int i;
	for(i = 0; i < answer.size() - 1; ++i) {
		printf("%d ", answer[i]);
	}

	printf("%d\n", answer[i]);

	return 0;
}
