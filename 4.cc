#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <assert.h>

using namespace std;

const int SIZE = 5;
const int MARKED = -1;

// https://adventofcode.com/2021/day/4#part1
// https://adventofcode.com/2021/day/4#part2

vector<int> parse_line(string& line) {
	istringstream ss(line);
	int number;
	vector<int> out;
	while (ss >> number) {
		out.push_back(number);
	}
	return out;
}

void print_board(vector<int>& board) {
	cout << endl << "=== BOARD === " << endl;
	for (int i=0; i<SIZE*SIZE; i++) {
		cout << board[i];
		if ((i+1) % SIZE == 0) cout << endl;
		else cout << ", ";
	}
}

void mark(vector<vector<int>>& boards, const int x) {
	for (auto& board : boards) {
		for (int i=0; i<board.size(); i++) {
			if (board[i] == x) board[i] = MARKED;
		}
	}
}

int calculate_score(vector<int>& board, const int x) {
	int s = 0;
	cout << board.size() << endl;
	for (int& y : board) {
		if (y != MARKED) {
			s += y;
		}
	}
	return s * x;
}

int remove_winners(vector<vector<int>>& boards, const int x) {
	int score = -1;
	for (auto& board : boards) {
		if (board.empty()) continue;
		// check rows
		for (int r = 0; r < SIZE; r++) {
			bool ok = true;
			for (int i = 0; i < SIZE; i++) {
				if (board[i + (r*SIZE)] != MARKED) {
					ok = false;
					break;
				}
			}
			if (ok) {
				score = calculate_score(board, x);
				print_board(board);
				board.clear();
				break;
			}
		}

		/*
			     0  1   2   3  4
			    ---------------
			0  | 22 13 17  11  0
			1  | 8   2 23  4  24  
			2  | 21  9 14  16  7
			3  | 6  10  3  18  5
			4  | 1  12 20  15 19
			
			 0. 1  2.  3.  4 5   6 7.  8   9 10 
			[22 13 17  11  0 8   2 23  4  24 21  9 14  16  7 6  10  3  18  5 1  12 20  15 19]
		*/

		// check columns
		for (int c = 0; c < SIZE; c++) {
			if (board.empty()) continue;
			bool ok = true;
			for (int i = 0; i < SIZE; i++) {
				if (board[(i*SIZE) + c] != MARKED) {
					ok = false;
					break;
				}
			}
			if (ok) {
				score = calculate_score(board, x);
				print_board(board);
				board.clear();
				break;
			}
		}
	}
	return score;
}

int main() {
	// Read input

	// 1. List of numbers
	string line;
	getline(cin, line);
	istringstream ss(line);
	int number;
	vector<int> bingo_nums;
	while (ss >> number && ss.ignore()) {
		bingo_nums.push_back(number);
	}

	// 2. Board configurations
	vector<vector<int>> boards;
	while (!cin.eof()) {
		// read empty line
		string line;
		getline(cin, line);
		if (cin.fail()) break;

		vector<int> board;
		for (int i=0; i<SIZE; i++) {
			string line;
			getline(cin, line);
			vector<int> arr = parse_line(line);

			assert(arr.size() == SIZE);
			for (int& x : arr) board.push_back(x);
		}
		boards.push_back(board);
	}

	// cout << "Found boards: " << endl;
	// for (auto& board : boards) {
	// 	print_board(board);
	// }

	// Replay numbers and check for first winning board
	int ans = -1;
	for (int& x : bingo_nums) {
		mark(boards, x);
		const int score_last = remove_winners(boards, x);
		if (score_last != -1) ans = score_last;
	}
	cout << "ans: " << ans << endl;
	return 0;
}