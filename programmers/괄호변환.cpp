#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

string recur(string p) {
    if(p.empty()) {
        return "";
    }

    int lc = 0;
    int rc = 0;
    string u, v;
    for(int i = 0; i < p.size(); ++i) {
        if (p[i] == ')') {
            lc++;
        } else {
            rc++;
        }
        if (rc == lc && lc != 0 && rc != 0) {
            u = p.substr(0, i + 1);
            v = p.substr(i + 1, 1001);
            break;
        }
    }

    if (u[0] != ')' || u.back() != '(') { // 올바른 괄호문자열이면
        // v에 대해서 1부터 다시수행
        string temp = recur(v);
        return u + temp;
    } else { // 아니면 아래와 같은 과정 수행
        string temp = "(";
        temp += recur(v);
        temp += ")";
        string what = u.substr(1, u.length() - 2);
        for(int j = 0; j < what.length(); ++j) {
            if (what[j] == '(')
                temp += ")";
            else
                temp += "(";
        }
        return temp;
    }
}

string solution(string p) {
    string answer = "";
    if(p.empty()) {
        return answer;
    }

    answer = recur(p);

    return answer;
}
