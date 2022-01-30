#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
범위에 유의하자.
A, B, C 등이 -10,000 ~ 10,000 사이더라도, A * D - B * C 같은 식의 결과값은 int 범위를 넘을 수 있다.
또한,
*/
vector<string> solution(vector<vector<int>> line) {
    long long minX = LLONG_MAX, minY = LLONG_MAX;
    long long maxX = LLONG_MIN, maxY = LLONG_MIN;

    vector<pair<long long, long long>> coords;

    int lineSize = line.size();
    for (int i = 0; i < lineSize; i++) {
        for (int j = i + 1; j < lineSize; j++) {
            long long A = line[i][0], B = line[i][1], E = line[i][2];
            long long C = line[j][0], D = line[j][1], F = line[j][2];

            long long mod = A * D - B * C; // int범위 벗어날 수 있음

            if (mod == 0) {
                continue;
            }
            if ((B * F - E * D ) % mod || (E * C  - A * F) % mod) { // 정수로 안 나누어 떨어지는 경우
                continue;
            }

            long long x = (B * F - E * D) / mod;
            long long y = (E * C - A * F) / mod;

            minX = min(minX, x);
            minY = min(minY, y);
            maxX = max(maxX, x);
            maxY = max(maxY, y);

            coords.push_back({ x, y });
        }
    }

    string row = string(maxX - minX + 1, '.');
    vector<string> answer(maxY - minY + 1, row);

    for (pair<long long, long long> coord : coords) {
        answer[abs(coord.second - maxY)][abs(coord.first - minX)] = '*';
    }

    return answer;
}
