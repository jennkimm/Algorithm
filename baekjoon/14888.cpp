#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

int n;
long long ans_min = 1000000001;
long long ans_max = -1000000001;
vector<int> num;
vector<int> operators;
vector<bool> operator_visited;

void dfs(int depth, stack<int> s, long long result) {
	if (depth == n - 1) {
		if (result < ans_min)
			ans_min = result;
		if (result > ans_max)
			ans_max = result;
		return;
	} else {
		for(int i = 0; i < n - 1; ++i) {
			if (!operator_visited[i]) {
				s.push(operators[i]);
				operator_visited[i] = true;
				int n_result;
				if (depth == 0)
					n_result = num[0];
				else
					n_result = result;
				if (operators[i] == 0)
					n_result = n_result + num[depth + 1];
				else if (operators[i] == 1)
					n_result = n_result - num[depth + 1];
				else if (operators[i] == 2)
					n_result = n_result * num[depth + 1];
				else if (operators[i] == 3)
					n_result = n_result / num[depth + 1];
				dfs(depth + 1, s, n_result);
				s.pop();
				operator_visited[i] = false;
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	num.assign(n + 1, 0);

	for(int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}

	operator_visited.assign(n, false);
	for(int i = 0; i < 4; ++i) {
		int temp;
		scanf("%d", &temp);
		if (i == 0) { // 덧셈
			for(int j = 0; j < temp; ++j) {
				operators.push_back(0);
			}
		} else if (i == 1) { // 뺄셈
			for(int j = 0; j < temp; ++j) {
				operators.push_back(1);
			}
		} else if (i == 2) { // 곱셈
			for(int j = 0; j < temp; ++j) {
				operators.push_back(2);
			}
		} else { // 나눗셈
			for(int j = 0; j < temp; ++j) {
				operators.push_back(3);
			}
		}
	}
	stack<int> s;
	dfs(0, s, 0);
	printf("%lld\n%lld\n",ans_max, ans_min);
	return 0;
}
