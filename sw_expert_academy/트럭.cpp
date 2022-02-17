#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

/**
 * 시간제한 2초
 * 메모이제이션 활용하여 구현해야 함
 * 미리 최대매출로 목표잡아서 한번 쫙 사이즈당 매출 계산해놓고
 * 각 목표매출 별 사이즈 출력
**/

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

	map<int, pair<int, int>> hubo; // key - 소비자, value - {사이즈, 가격}
	int cur_cost = 0;

	for(auto j = m.begin(); j != m.end(); ++j) { // 사이즈가 작은 순서대로 돌면서
		int p;
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
		}
		memo[j->first] = cur_cost;
	}

	auto base = memo.begin();
	for(int i = 0; i < gc.size(); ++i) {
		bool flag = false;
		for(auto j = base; j != memo.end(); ++j) {
			// 목표 매출이 mm->second 보다 작으면
			if (gc[i].second <= j->second) {
				answer[gc[i].first] = j->first;
				flag = true;
				base = j; // 베이스 업데이트해서 효율적으로
				break;
			}
		}
		if (!flag) {
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
