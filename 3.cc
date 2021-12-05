#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <assert.h>

using namespace std;

// https://adventofcode.com/2021/day/3
// https://adventofcode.com/2021/day/3#part1
// https://adventofcode.com/2021/day/3#part2

pair<char,char> mcb_lcb(vector<string>& arr, const int pos) {
	int n = arr.size();
	vector<int> freq = {0, 0};
	for (string& s : arr) {
		freq[s[pos] - '0']++;
	}

	const char mcb = freq[0] > freq[1] ? '0' : '1',
		       lcb = freq[0] <= freq[1] ? '0' : '1';
	return { mcb, lcb };
}

vector<string> filter(vector<string>& arr, const int pos, const char bit) {
	vector<string> out;
	for (string& s : arr) {
		if (s[pos] == bit) out.emplace_back(s);
	}
	return out;
}

int o2_score(vector<string> arr, const int pos) {
	if (arr.size() == 1) {
		return stoi(arr.front(), nullptr, 2);
	}
	assert(pos < arr.front().size());
	auto mcb = mcb_lcb(arr, pos).first;
	return o2_score(filter(arr, pos, mcb), pos + 1);
}

int co2_score(vector<string> arr, const int pos) {
	if (arr.size() == 1) {
		return stoi(arr.front(), nullptr, 2);
	}
	assert(pos < arr.front().size());
	auto lcb = mcb_lcb(arr, pos).second;
	return co2_score(filter(arr, pos, lcb), pos + 1);
}

int main() {
	vector<string> arr;
	while (!cin.eof()) {
		string line;
		getline(cin, line);
		if (cin.fail()) {
			break;
		}
		arr.push_back(line);
	}

	const int end = arr.front().size();
	string gamma, epsilon;
	for (int pos = 0; pos < end; pos++) {
		const pair<int,int> res = mcb_lcb(arr, pos);
		gamma.push_back(res.first);
		epsilon.push_back(res.second);
	}

	assert(gamma.size() == epsilon.size() && gamma.size() == end);

	cout << "ans #1: " << stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2) << endl;
	cout << "ans #2: " << o2_score(arr, 0) * co2_score(arr, 0) << endl;
	return 0;
}