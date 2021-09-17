#include <stdio.h>
#include <vector>

using namespace std;

int main() {
	int n, b, c;
	vector<int> a;

	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		int tmp;
		scanf("%d", &tmp);
		a.push_back(tmp);
	}
	scanf("%d %d", &b, &c);

	long long ans = 0;
	for(int i = 0; i < a.size(); ++i) {
		int k = 1;
		if (a[i] > b) {
			k += (a[i] - b) / c;
			if ((a[i] - b) % c > 0)
				k += 1;
		}
		ans += k;
	}
	printf("%lld\n", ans);
	return 0;
}
