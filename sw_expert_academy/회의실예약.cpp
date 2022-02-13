#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<string>
#include<map>

using namespace std;

int main(int argc, char** argv)
{
	int n, m;
	scanf("%d %d", &n, &m);
	map<string, vector<bool>> room;
	vector<string> vr;

	for(int i = 0; i < n; ++i) {
		string r;
		vector<bool> v;
		v.assign(10, false);
		cin >> r;
		room.insert({r, v});
		vr.push_back(r);
	}

	for(int i = 0; i < m; ++i) {
		string s;
		int st, et;
		cin >> s >> st >> et;
		for(int j = st; j < et; ++j)
			room.find(s)->second[j - 9] = true;
	}

	sort(vr.begin(), vr.end());

	// 출력
	for(int i = 0; i < n; ++i) {
		cout << "Room " << vr[i] << ":\n";
		// 빈 회의공간 있는지 검사
		vector<int> e;
		bool flag = false;
		for(int j = 0; j < 9; ++j) {
			//cout << j + 9 << "시간 "<< room.find(vr[i])->second[j] << "\n";
			if (room.find(vr[i])->second[j] == false && !flag) {
				e.push_back(j + 9);
				flag = true;
			} else if (room.find(vr[i])->second[j] == true && flag) {
				e.push_back(j + 9);
				flag = false;
			}
		}
		if (e.size() == 0) {
			cout << "Not available\n";
		} else {
			if (e.size() % 2 == 1) {
				cout << e.size() / 2 + 1 << " available:\n";
				e.push_back(18);
			} else {
				cout << e.size() / 2 << " available:\n";
			}
			int cnt = 0;
			for(int j = 0; j < e.size(); ++j) {
				if (e[j] == 9) {
					cout << "09";
				} else {
					cout << e[j];
				}
				if (cnt % 2 == 0)
					cout << "-";
				else
					cout << "\n";
				cnt++;
			}
		}
		if (i != n - 1)
			cout << "-----\n";
		else
			cout << "\n";
	}
	return 0;
}
