#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

bool isValid(const set<vector<int>>& building) {
    for(auto b: building) {
        int x = b[0];
        int y = b[1];

        if (b[2] == 0) { // 기둥
            vector<vector<int>> pred = {
                {x, y, 1},
                {x - 1, y, 1},
                {x, y - 1, 0}
            };
            if (y == 0 || (building.find(pred[0]) != building.end()) || (building.find(pred[1]) != building.end()) || (building.find(pred[2]) != building.end())) {
                continue;
            }
            return false;
        } else { // 보
            vector<vector<int>> pred = {
                {x + 1, y, 1},
                {x - 1, y, 1},
                {x, y - 1, 0},
                {x + 1, y - 1, 0}
            };
            if ( (building.find(pred[0]) != building.end() && building.find(pred[1]) != building.end()) || building.find(pred[2]) != building.end() || building.find(pred[3]) != building.end()) {
                continue;
            }
            return false;
        }
    }
    cout << "here\n";
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    set<vector<int>> building; // 정답셋

    for(int i = 0; i < build_frame.size(); ++i) {
        vector<int> v = {
            build_frame[i][0],
            build_frame[i][1],
            build_frame[i][2]
        };

        if (build_frame[i][3] == 0) { // 삭제
            building.erase(building.find(v));
            if (!isValid(building)) {
                building.insert(v);
            }
        } else { // 추가
            building.insert(v);
            if (!isValid(building)) {
                building.erase(building.find(v));
            }
        }
    }

    // answer
    for(auto b: building) {
        answer.push_back(b);
    }

    return answer;
}
