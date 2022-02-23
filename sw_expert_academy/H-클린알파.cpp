#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

int main(int argc, char** argv)
{
	long long p, n;
	scanf("%lld %lld", &p, &n);

	vector<long long> v(n + 1);
	for(int i = 1; i <= n; ++i) {
		long long k;
		scanf("%lld", &k);
		v[i] = k;
	}

	vector<long long> nuguk;
	nuguk.assign(n + 1, 0);

	// n 초 후의 바이러스 갯수
	for(int t = 1; t <= n; ++t) {
		nuguk[t] = nuguk[t - 1] * p + v[t];
	}

	printf("%lld\n", nuguk[n] % 1000000007);

	return 0;
}
