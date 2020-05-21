#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <string>
#include "Solver.h"

using namespace std;

int main() {
	string regular_exp = "", word = "";

	cin >> regular_exp >> word;

	Solver solver(word);
	int result = solver.find_max_substring(regular_exp);

	if (result == 0) {
		cout << "INF";
	}
	else {
		cout << result;
	}

	return 0;
}