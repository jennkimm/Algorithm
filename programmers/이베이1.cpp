#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<string>> schedule) {
    int answer = -1;

	int cal = 1;
	for(int i = 0; i < 4; ++i) {
		int temp = 0;
		if (schedule[0][i].length() > 8) {
			// 1시간 30분씩 두번 진행하는 수업


		} else {
			// 3시간 단위로 진행하는 수업
			for(int j = 1; j < 5; ++j) {
				// 일단 요일 부터 같은지 확인.
				for(int k = 0; k < 4; ++k) {
					if (schedule[0][i][0] != schedule[j][k][0]) {
						temp += 1;
						continue;
					} else {
						// 시간대가 겹치는지?
						string st = schedule[0][i][3] + schedule[0][i][4];
						int hh = stoi(st);
						int mm;
						if (schedule[0][i][6] == "0")
							mm = 0;
						else
							mm = 30;
						int new_hh = stoi(schedule[j][k][3] + schedule[j][k][4]);
						int new_mm;
						if (schedule[j][k][6] == "0")
							new_mm = 0;
						else
							new_mm = 30;
						if (hh < new_hh && (new_hh - hh) >= 3) {
							temp += 1;
						} else if (new_hh == hh) {
							continue;
						} else if (hh > new_hh && (hh - new_hh) >= 3) {
							temp += 1;
						}
					}
				}
			}
		}
		cal *= temp;
	}

    return answer;
}

int main() {
	vector<vector<string>> schedule = [
		["MO 12:00 WE 14:30", "MO 12:00", "MO 15:00", "MO 18:00"],
		["TU 09:00", "TU 10:00", "TU 15:00", "TU 18:00"],
		["WE 09:00", "WE 12:00", "WE 15:00", "WE 18:00"],
		["TH 09:30", "TH 11:30", "TH 15:00", "TH 18:00"],
		["FR 15:00", "FR 15:00", "FR 15:00", "FR 15:00"]
	];


	return 0;
}
