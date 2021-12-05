#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

// https://adventofcode.com/2021/day/1#part1
// https://adventofcode.com/2021/day/1#part2


// Part 1:
// int main() {
// 	int prev = -1, cnt = -1;
// 	while (!cin.eof()) {
// 	    string line;
// 	    getline(cin, line);

// 	    if (cin.fail()) {
// 	        cout << "End of input! " << endl;
// 	        break;
// 	    }

// 	    const int cur = stoi(line);
// 	    if (cur > prev) ++cnt;
// 	    prev = cur;
// 	}

// 	cout << "ans: " << cnt << endl;
// 	return 0;
// }

// Part 2:
int main() {
	int prev = -1, cnt = -1, cur = 0;
	queue<int> window;
	window.push(0);
	const int SLIDING_WINDOW_SIZE = 3;

	// First process SLIDING_WINDOW_SIZE - 1 elements
	for (int i=0; i<SLIDING_WINDOW_SIZE - 1; i++) {
	    string line;
	    getline(cin, line);
	    if (cin.fail()) {
	        cout << "End of input! " << endl;
	        cout << "ans: " << 0 << endl;
	        return 0;
	    }
	    const int e = stoi(line);
	    cur += e;
	    window.push(e);
	}

	// Process the rest
	while (!cin.eof()) {
		assert(window.size() == SLIDING_WINDOW_SIZE);
	    string line;
	    getline(cin, line);
	    if (cin.fail()) {
	        cout << "End of input! " << endl;
	        cout << "ans: " << cnt << endl;
	        return 0;
	    }
	    const int e = stoi(line);
	    cur += e - window.front();
	    if (cur > prev) ++cnt;

	    window.pop();
	    window.push(e);
	    prev = cur;
	}

	cout << "ans: " << cnt << endl;
	return 0;
}