// https://adventofcode.com/2021/day/2

// https://adventofcode.com/2021/day/2#part1
// https://adventofcode.com/2021/day/2#part2

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// for string delimiter
vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


// Part 1:
// int main() {
// 	int x = 0, y = 0;
// 	while (!cin.eof()) {
// 		string line;
// 		getline(cin, line);
// 		if (cin.fail()) {
// 			break;
// 		}

// 		vector<string> tokens = split(line, " ");
// 		const string op = tokens[0];
// 		const int delta = stoi(tokens[1]);

// 		if (op == "forward") x += delta;
// 		else if (op == "up") y = max(y - delta, 0);
// 		else if (op == "down") y += delta;
// 	}

// 	cout << "ans: " << x * y << endl;

// 	return 0;
// }

// Part 2:

int main() {
	int x = 0, y = 0, a = 0;
	while (!cin.eof()) {
		string line;
		getline(cin, line);
		if (cin.fail()) {
			break;
		}

		vector<string> tokens = split(line, " ");
		const string op = tokens[0];
		const int delta = stoi(tokens[1]);

		if (op == "forward") {
			x += delta;
			y += (a * delta);
		}
		else if (op == "up") a = max(a - delta, 0);
		else if (op == "down") a += delta;
	}

	cout << "ans: " << x * y << endl;

	return 0;
}