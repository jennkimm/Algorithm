#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

const int MAX = 1001;

// 경계값 케이스 확인 필수
int solution(string s) {
    int answer = MAX;

    for(int p = 1; p <= (s.length() / 2); ++p) {
        int cur_pos = 0;
        vector<string> v;
        while ((cur_pos + p) <= (s.length() - 1)) {
            v.push_back(s.substr(cur_pos, p));
            cur_pos += p;
        }
        if (cur_pos != s.length()) {
            v.push_back(s.substr(cur_pos, 1001));
        }

        //printf("p = %d\n", p);
        int base = 1;
        string temp = "";
        int i;
        for(i = 0; i < v.size() - 1; ++i) {
            //printf("%s\n", v[i].c_str());
            if (v[i] == v[i + 1])
                base++;
            else {
                if (base == 1)
                    temp += v[i];
                else {
                    temp += to_string(base);
                    temp += v[i];
                }
                base = 1;
            }
        }
        if (base == 1) {
            temp += v[i];
        } else {
            temp += to_string(base);
            temp += v[i];
        }
        //printf("%s\n",temp.c_str());
        if (temp.length() < answer)
            answer = temp.length();
    }
    if (s.length() == 1)
        answer = 1;
    return answer;
}
