#include <bits/stdc++.h>
#include <string>
#include <cstdio>
#include <unordered_map>
#define lli long long int

using namespace std;

struct street{
	pair<int, int> location; // start, end
	string name; // 도로 이름
	int L; // 지나가는데 걸리는 시간
};

struct car{
	int P; // 지나가야 할 도로 갯수
	vector<string> pass; // 지나가야할 도로
};

struct intersaction {
	vector<pair<string, int> > incoming_street; // 도로 이름과 시간
};

int main() {
	int D, I, S, V, F;
	cin >> D >> I >> S >> V >> F;

	vector<street> streets;
	unordered_map<int, car> cars;
	vector<int> graph[I+1];
	vector<intersaction> intersactions;
	vector<vector<string> > k;

	k.resize(S);
	for(int i = 0; i < S; i++){
		k[i].resize(S);
	}
	streets.resize(S);
	intersactions.resize(I);

	for (int i = 0; i < S; i++) {
		cin >> streets[i].location.first >> streets[i].location.second >> streets[i].name >> streets[i].L;
		graph[streets[i].location.second].push_back(streets[i].location.first);
		k[streets[i].location.second][streets[i].location.first] = streets[i].name;

		//cout << to_string(streets[i].location.first) <<"->" << to_string(streets[i].location.second) << streets[i].name<<"\n";
	}

	for (int i = 0; i < V; i++) {
		cin >> cars[i].P;
		for (int j = 0; j < cars[i].P; j++) {
			string str;
			cin >> str;
			cars[j].pass.push_back(str);
		}
	}

	// for (int i = 0; i < I; i++) {
	// 	for (int j = 0; j < graph[i].size(); j++){
	// 		cout << graph[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	for (int i = 0; i < I; i++) {
		int t = graph[i][0];
		int time = 1;
		// 기본적으로 1
		if (graph[i].size() == 1){
			intersactions[i].incoming_street.push_back(pair<string, int>(k[i][graph[i][0]], 1));
		} else { // 만약 graph[i].size() > 1 이라면
			for (vector<int>::iterator j = graph[i].begin(); j != graph[i].end(); j++){
				intersactions[i].incoming_street.push_back(pair<string, int>(k[i][*j], time));
				//cout << graph[i][j] << " ";
				if (time / 2 == 0)
					time--;
				else
					time++;
			}
		}

		// for (int j = 0; j < graph[i].size(); j++){
		// 	cout << graph[i][j] << " ";
		// }
		// cout << "\n";
	}

	// intersaction 출력
	cout << I << "\n";
	for (int i = 0; i < I; i++) {
		cout << i << "\n" << intersactions[i].incoming_street.size() << "\n";
		for (int j = 0; j < intersactions[i].incoming_street.size(); j++) {
			cout << intersactions[i].incoming_street[j].first <<" "<< intersactions[i].incoming_street[j].second << "\n";
		}
	}

	// 각 intersaction 마다 incoming street 구한다.

	// incoming street 가 하나라면 랜덤으로 1 아니면 2 숫자 부여

	// incoming street 가 2개 이상이라면 그들끼리 어떠한 순서대로 신호등 점멸
	// 그 신호등이 먼저 켜지는 도로 기준이 차가 많이 서있는 기준.

}
