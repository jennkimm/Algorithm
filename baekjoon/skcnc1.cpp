#include <stdio.h>
#include <vector>

using namespace std;

int main() {
	vector<int> v = {1, 2, 3, 4, 5, 6};

	vector<int> a;
	vector<int> b;

	for(int i = 0; i < v.size(); ++i) {
		if (v[i] >= 1 && v[i] <= 3) {
			a.push_back(v[i]);
		} else {
			b.push_back(v[i]);
		}
	}

	for(int i = 0; i < 3; ++i) {
		printf("%d\n", a[i]);
	}
}
