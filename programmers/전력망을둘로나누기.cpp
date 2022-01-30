#include <string>
#include <vector>
#include <math.h>

using namespace std;

vector<int> p;
int ans = 101;

int find(int x) {
    // 루트 노드는 부모 노드 번호로 자기 자신을 가진다.
    if (p[x] == x) {
        return x;
    } else {
        // 각 노드의 부모 노드를 찾아 올라간다.
        return find(p[x]);
    }
}

void _union(int x, int y){
    // 각 원소가 속한 트리의 루트 노드를 찾는다.
    x = find(x);
    y = find(y);

    if (x < y)
        p[y] = x;
    else
        p[x] = y;
}

void check(int n) {
    int cnt = 1;
    for(int i=2; i<n; i++){
        p[i] = find(i);
        if(p[1] == p[i]) {
            cnt++;
        }
    }
    int cnt2 = n - 1 - cnt;
    if (ans > abs(cnt2 - cnt))
        ans = abs(cnt2 - cnt);
}

int solution(int n, vector<vector<int>> wires) {
    int answer = 100;

    for(int i = 0; i < n; ++i) {
        // 초기화
        p.assign(n + 1, 0);
        for(int j = 0; j < n; ++j) {
            p[j] = j;
        }

        for(int j = 0; j < n - 1; j++) {
            if (j == i)
                continue;
            else {
                _union(wires[j][0], wires[j][1]);
            }
        }

        // 전선 갯수 차 구하기
        check(n + 1);
    }
    answer = ans;
    return answer;
}
