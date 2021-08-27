#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;

	for (int y = 3; y < brown; y++) { // 세로
		for (int x = y; x < (brown - 2); x++) { // 가로
			int _brown = (2 * x) + (2 * (y - 2));
			int _yellow = (x * y) - _brown;
			//cout << _brown << ", " << _yellow << endl;

			if (_brown == brown && _yellow == yellow) {
					answer.push_back(x);
					answer.push_back(y);
				break;
			}
		}
	}

	return answer;
}

int main() {
	int b = 10;
	int y = 2;
	vector<int> ans= solution(b, y);
	cout << ans[0] << endl;
	cout << ans[1] << endl;
}
