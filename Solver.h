#include "LAutomataBuilder.h"

class Solver {
public:
	Solver(const std::string& w) : word(w) {};

	int find_max_substring(const std::string& regular_exp);
	void DFS(Node* vertex);
private:
	std::string word;
	int current_letter_index = 0;
	int max_end_pos = 0;
};

int solve(const std::string& w, const std::string& regular_exp);