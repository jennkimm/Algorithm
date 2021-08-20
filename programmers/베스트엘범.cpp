#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

bool cmp(const pair<string,int>& a, const pair<string,int>& b) {
	if (a.second == b.second) return a.first > b.first;
	return a.second > b.second;
}

struct myOrder
{
	bool operator() (const int& left, const int& right) const
	{
		if (left == right)
			return true;
		else if (left > right)
			return false;
		else
			return true;
	}
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
	map<string, int> m;
	multimap<int, pair<string, int>, myOrder> songs;

	// 장르 당 몇번 재생되었는지
	for(int i = 0; i < genres.size(); i++) {
		if(m.find(genres[i]) == m.end()) { // not found
			m.insert(make_pair(genres[i], plays[i]));
		} else { // found
			m.find(genres[i])->second += plays[i];
		}
	}
	vector<pair<string, int>> vec(m.begin(), m.end());
	sort(vec.begin(), vec.end(), cmp); // 재생 많은 순으로 장르를 정렬

	for(int i = 0; i < genres.size(); i++) {
		songs.insert({plays[i], {genres[i], i}}); // 재생 수 많은 순으로 정렬
	}

	for(int i = 0; i < vec.size(); i++) { // 각 장르 안에서
		string cur = vec[i].first;
		int count = 0;
		for(auto it = songs.crbegin(); it != songs.crend(); it++) { // 재생 횟수가 많은 순서대로 answer에 push
			if (count == 0 && (it->second).first == cur) {
				answer.push_back((it->second).second);
				count++;
			} else if (count == 1 && (it->second).first == cur) {
				answer.push_back((it->second).second);
				break;
			}
		}
	}

	return answer;
}

int main() {
	vector<string> genres = {"classic", "pop", "classic", "classic", "pop"};
	vector<int> plays = {500, 600, 150, 800, 2500};
	vector<int> answer = solution(genres, plays);
	for (int i = 0; i < answer.size(); i++) {
		printf("%d\n", answer[i]);
	}
	return 0;
}
