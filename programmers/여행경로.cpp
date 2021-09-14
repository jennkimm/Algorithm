#include <string>
#include <vector>
#include <map>
#include <set>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> answer;
bool visited[10001];
bool n = false;

bool compare(vector<string> a, vector<string> b){
    return a[1] < b[1];
}

// 포인터 사용으로 재귀 오버헤드 줄임.
void dfs(vector<vector<string>> &tickets, string curr, vector<string> &path, int depth) {
    if(depth == tickets.size()) {
        answer = path; // 최종 경로를 답으로 준다.
        n = true;
        return;
    }
    if (n == false) {
        for(int i = 0; i < tickets.size(); ++i) {
            if (!visited[i] && curr == tickets[i][0]) {
                visited[i] = true;
                path.push_back(tickets[i][1]);
                dfs(tickets, tickets[i][1], path, depth+1);
                // 다시 뒤로 되돌림
                path.pop_back();
                visited[i] = false;
            }
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> path;
    n = false;
    path.push_back("ICN");
    sort(tickets.begin(), tickets.end(), compare); // 알파벳 순서로 미리 정렬
    dfs(tickets, "ICN", path, 0);
    return answer;
}
