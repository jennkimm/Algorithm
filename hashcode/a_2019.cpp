#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct photo {
	char ori;
	vector<int> tag;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

	ifstream fin;
	fin.open("input.txt");

	int n;
	map<string, int> tag_dic;
	vector<photo> photos;

	photos.resize(n);
	string tmp;

	fin >> n;
	for(int i = 0; i< n; i++) {
		fin >> tmp;
		if ( tmp == "H" || tmp == "V") {
			photos[i].ori = tmp[0];

		}
	}

}

