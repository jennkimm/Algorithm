#include<iostream>
#include<cstring>
#include<string>
#include<stdio.h>
#include<sstream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

bool cmp(vector<int> &a, vector<int> &b) {
	// read < write
	if (a[1] == b[1])
		return a[2] < b[2];
	else
		return a[1] > b[1];
}

bool cmp2(pair<int, string> &a, pair<int, string> &b) {
	return a.first < b.first;
}

vector<string> solution(vector<string> arr, vector<string> processes) {
    vector<string> answer;
	vector<pair<int, string>> ans; // process id , answer string
	vector<vector<int>> prcs; // 수행해야 할 프로세스들
	vector<vector<int>> waiting; // 대기중인 프로세스
	vector<vector<int>> working; // 실행중인 프로세스
	prcs.assign(processes.size(), vector<int>());

	for(int i = 0; i < processes.size(); ++i) {
		// 프로세스 번호 t1 t2 A B C 로 쪼개야 해
		string str_buf;
		istringstream ss(processes[i]);
		prcs[i].push_back(i);
		while(getline(ss, str_buf, ' '))
		{
			if (str_buf.compare("read") == 0) {
				prcs[i].push_back(9000);
			} else if (str_buf.compare("write") == 0) {
				prcs[i].push_back(9001);
			} else {
				prcs[i].push_back(stoi(str_buf));
			}
		}
	}

	int time = 0; // 점유하고있는 시간
	int t = 1;
	int next_prcs = 0;

	// read인 경우
	// 배열이 읽기작업 수행중인 경우 바로 작업 수행 가능
	// 하나 이상의 쓰기 작업 대기중인 경우 읽기 요청도 대기

	// write인 경우
	// 배열이 읽기작업 수행중인 경우 새로운 쓰기 요청 프로세스 모두 대기
	// 배열에 쓰기작업 수행중인 경우 새로운 읽기/쓰기 요청 프로세스 모두 대기

	// 대기 중인 프로세스 선택할 때 읽기보다 쓰기 요청 먼저 수행
	// 대기 중인 작업을 선택하려 함과 동시에 새로운 작업이 들어온다면, 새 작업요청을 포함하여 다음으로 작업할 프로세스 선택

	// 출력하는 순서는 먼저 요청된 프로세스가 먼저 출력된다.

	while(t >= 0) {
		if (next_prcs == prcs.size() && waiting.empty() && working.empty()) {
			break;
		}

		//printf("t = %d\n", t);
		int wwsize = working.size();
		for(int i = 0; i < wwsize; ++i) {
			working[i][3]--;
			if (working[i][3] == 0) {
				if (working[i][1] == 9000) {
					string temp = "";
					for(int k = working[i][4]; k <= working[i][5]; ++k) {
						temp += arr[k];
					}
					ans.push_back({working[i][0], temp});
				} else {
					for(int k = working[i][4]; k <= working[i][5]; ++k) {
						arr[k] = to_string(working[i][6]);
					}
				}
			}
		}

		for(int j = wwsize - 1; j >= 0; --j) {
			if (working[j][3] == 0) {
				working.erase(working.begin() + j);
			}
		}

		// for(int i = 0; i < arr.size(); ++i) {
		// 	printf("%s", arr[i].c_str());
		// }
		// printf("\n");

		if (next_prcs < prcs.size()) {
			if (t == prcs[next_prcs][2]) {
				//printf("t = %d, nect_prcs = %d\n", t, prcs[next_prcs][1]);
				vector<int> tv;
				tv.assign(prcs[next_prcs].size(), 0);
				copy(prcs[next_prcs].begin(), prcs[next_prcs].end(), tv.begin());
				waiting.push_back(tv);
				next_prcs++;
			}
		}
		sort(waiting.begin(), waiting.end(), cmp);

		// read 만 있을 때는 waiting 에 있는 모든 read 수행
		bool hor = true;
		for(int i = 0; i < waiting.size(); ++i) {
			if(waiting[i][1] == 9001) {
				hor = false;
				break;
			}
		}

		if (!waiting.empty() && hor) {
			int wsize = waiting.size();
			for(int i = 0; i < wsize; ++i) {
				vector<int> cur; // 실행하려는 프로세스
				cur.assign(waiting[0].size(), 0);
				copy(waiting[0].begin(), waiting[0].end(), cur.begin());
				if (cur[1] == 9000) {
					bool readable = true;
					for(int k = 0; k < working.size(); ++k) {
						if (working[k][1] == 9001) {
							readable = false;
							break;
						}
					}
					if (!readable) {
						// 그냥 대기한다
					} else {
						// 읽는다
						// cur[2] ~ cur[3]
						working.push_back(cur);
						waiting.erase(waiting.begin());
					}
				}
			}
		} else if (!waiting.empty()) {
			// waiting 에 read 만 있는 경우 -> 전부 실행 가능
			vector<int> cur; // 실행하려는 프로세스
			cur.assign(waiting[0].size(), 0);
			copy(waiting[0].begin(), waiting[0].end(), cur.begin());

			if (cur[1] == 9000) {
				bool readable = true;
				for(int k = 0; k < working.size(); ++k) {
					if (working[k][1] == 9001) {
						readable = false;
						break;
					}
				}
				if (!readable) {
					// 계속 그냥 대기한다
				} else {
					// 읽는다
					// cur[2] ~ cur[3]
					working.push_back(cur);
					waiting.erase(waiting.begin());
				}
			} else if (cur[1] == 9001) {
				if (!working.empty()) {
					// 그냥 대기
				} else {
					working.push_back(cur);
					waiting.erase(waiting.begin());
				}
			}
		}

		// printf("working pc => ");
		// for(int i = 0; i < working.size(); ++i) {
		// 	printf("%d %d %d %d %d | ", working[i][1],  working[i][2],  working[i][3],  working[i][4], working[i][5]);
		// }
		// printf("\n-----\n");

		// printf("waiting pc => ");
		// for(int i = 0; i < waiting.size(); ++i) {
		// 	printf("%d %d %d %d %d | ", waiting[i][1],  waiting[i][2],  waiting[i][3],  waiting[i][4], waiting[i][5]);
		// }

		// printf("\n");

		if (!working.empty()) {
			time++;
		}

		t++;
	}
	sort(ans.begin(), ans.end(), cmp2);
	for(int i = 0; i < ans.size(); ++i) {
		answer.push_back(ans[i].second);
	}
	answer.push_back(to_string(time));

    return answer;
}

int main() {
	vector<string> arr = {
		"1","1","1","1","1","1","1"
	};
	vector<string> processes = {
		"write 1 12 1 5 8","read 2 3 0 2","read 5 5 1 2","read 7 5 2 5","write 13 4 0 1 3", "write 19 3 3 5 5", "read 30 4 0 6", "read 32 3 1 5"
	};

	// vector<string> arr = {
	// 	"1","2","4","3","3","4","1","5"
	// };
	// vector<string> processes = {
	// 	"read 1 3 1 2", "read 2 6 4 7", "write 4 3 3 5 2", "read 5 2 2 5", "write 6 1 3 3 9", "read 9 1 0 7"
	// };


	vector<string> answer = solution(arr, processes);

	for(int i = 0; i < answer.size(); ++i) {
		printf("%s\n", answer[i].c_str());
	}
}
