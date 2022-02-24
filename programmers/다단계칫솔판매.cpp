#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> profit;
map<string, string> m;

/**
 * 유니온파인드st
**/

string find(string x, int money) {
	if (x == "-" || (money / 10 < 1))
		return x;
	else {
		profit[m[x]] += money / 10;
		profit[x] -= money / 10;
		return find(m[x], money / 10);
	}
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;

	for(int i = 0; i < enroll.size(); ++i) {
		m.insert({enroll[i], referral[i]});
		profit.insert({enroll[i], 0});
	}

	for(int i = 0; i < seller.size(); ++i) {
		// 자신의 부모를 찾는 과정에서 거쳐가는 노드에 계속 이익 10%씩 배분하기
		string x = seller[i];
		profit[x] += amount[i] * 100;

		x = find(seller[i], amount[i] * 100);
	}

	for(int i = 0; i < enroll.size(); ++i) {
		answer.push_back(profit[enroll[i]]);
	}

    return answer;
}
