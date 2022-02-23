#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

map<string, int> combi;

// 조합 찾기
void dfs(string order, string ss, int base, int len) {
	if (ss.length() == len) {
		// combi 에 담기
		if (combi.find(ss) != combi.end()) {
			combi.find(ss)->second += 1;
		} else {
			combi.insert({ss, 1});
		}
		return;
	} else {
		string temp = ss;
		for(int i = base; i < order.length(); ++i) {
			ss += order[i];
			dfs(order, ss, i + 1, len);
			ss = temp;
		}
	}
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
	// orders[i] 에 있는 문자열에서 길이가 n 인 조합

	for(int i = 0; i < orders.size(); ++i) {
		for(int j = 0; j < course.size(); ++j) {
			if (orders[i].size() < course[j]) {
				continue;
			} else {
				string s = "";
				dfs(orders[i], s, 0, course[j]);
			}
		}
	}

	// 각 코스길이별 max length 찾기
	for(int i = 0; i < course.size(); ++i) {
		vector<string> temp;
		int xx = 2;
		for(auto m : combi) {
			if (m.first.size() == course[i] && m.second > xx) {
				xx = m.second;
				temp.clear();
				temp.push_back(m.first);
				continue;
			}
			if (m.first.size() == course[i] && m.second == xx) {
				temp.push_back(m.first);
			}
		}

		for(int j = 0; j < temp.size(); ++j) {
			answer.push_back(temp[j]);
		}
	}

	sort(answer.begin(), answer.end());

    return answer;
}

int main() {
	vector<string> orders{
		"ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"
	};
	vector<int> course{
		2, 3, 5
	};

	vector<string> answer = solution(orders, course);
	for(int i = 0; i < answer.size(); ++i) {
		printf("%s, ", answer[i].c_str());
	}
	printf("\n");
	return 0;
}
