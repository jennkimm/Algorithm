#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

int parent[201] = {-1, };

int find(int n) {
    if (parent[n] == n)
        return n;
    else {
        return parent[n] = find(parent[n]);
    }
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v) {
        return; // 사이클 존재
    }
    else if(u < v) {
        parent[u] = v;
    } else {
        parent[v] = u;
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 1;

    for(int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < computers[i].size(); ++j) {
            if (computers[i][j] == 1) {
                merge(i, j);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        parent[i] = find(i); // 최종적으로 확정된 parent 구한다.
    }

    sort(parent, parent + n);

    // 부모가 다른 것의 개수를 세면 됨
    int temp = parent[0];
    for (int i = 1; i < n; ++i) {
        if (parent[i] != temp) {
            temp = parent[i];
            answer++;
        }
    }

    return answer;
}
