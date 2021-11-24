// you can use includes, for example:
#include <algorithm>
#include <stdio.h>
#include <vector>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

string solution(vector<string> &phone_numbers, vector<string> &phone_owners, string &number) {
    // write your code in C++14 (g++ 6.2.0)
	for(int i = 0; i < phone_numbers.size(); ++i) {
		if (number == phone_numbers[i]) {
			return phone_owners[i];
		}
	}
	return number;
}