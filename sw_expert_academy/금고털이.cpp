#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

/**
 * K napsack 알고리즘 리뷰하자
**/

bool cmp(pair<int, int> &a, pair<int, int> &b) {
	return a.second > b.second;
}

int main(int argc, char** argv)
{
	int w, n;
	scanf("%d %d", &w, &n);

	// 총 양과 무게당 가격
	vector<pair<int, int>> v;
	for(int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		v.push_back({a, b});
	}

	sort(v.begin(), v.end(), cmp);

	// 키로당 가치가 큰걸 최대로 담는다.
	// 부족하면 그 다음
	int cur_amount = 0;
	int max_value = 0;
	for(int i = 0; i < v.size(); ++i) {
		if ((v[i].first + cur_amount) < w) {
			cur_amount += v[i].first;
			max_value += (v[i].first * v[i].second);
			continue;
		} else if ((cur_amount + v[i].first) == w) {
			cur_amount += v[i].first;
			max_value += (v[i].first * v[i].second);
			break;
		} else {
			max_value += ((w - cur_amount) * v[i].second);
			cur_amount += (w - cur_amount);
			break;
		}
	}
	printf("%d\n", max_value);

	return 0;
}
