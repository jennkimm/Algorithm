#include <string>
#include <vector>

using namespace std;

int all_answer = 0;

void dfs(vector<int> &numbers, vector<char> cur_ops, int target) {
     if (cur_ops.size() == numbers.size()) {
         // 계산
         int sum = 0;
         for(int i = 0; i < cur_ops.size(); ++i) {
             if (cur_ops[i] == '+') {
                 sum += numbers[i];
             } else {
                 sum -= numbers[i];
             }
         }
         if (sum == target)
             all_answer++;
     	return;
     } else {
	     cur_ops.push_back('+');
         dfs(numbers, cur_ops, target);
         cur_ops.pop_back();
         cur_ops.push_back('-');
         dfs(numbers, cur_ops, target);
     }
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    vector<char> cur_ops;
    dfs(numbers, cur_ops, target);

    answer = all_answer;
    return answer;
}
