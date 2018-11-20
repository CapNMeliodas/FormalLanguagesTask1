#include "Solver.h"

using namespace std;

int Solver::find_max_substring(const string& regular_exp) {	
	LAutomataBuilder builder;								 //Строим автомат по решулярке
	LAutomata* automaton = builder.build(regular_exp);		
	int result = 0;
	for (int i = 0; i < word.length(); ++i) {	//Для каждой стартовой позиции в слове
		current_letter_index = i;
		for (auto start : automaton->get_automata()) { //Начиная с каждой вершины автомата
			int max_end_pos = current_letter_index;
			DFS(start);	//Проверяем на какой максимум мы можем отойти от стартовой вершины
			if ((max_end_pos - i) > result) {
				result = max_end_pos - i;
			}
		}
	}
	delete automaton;
	return result;
}

//DFS по автомату
void Solver::DFS(Node* vertex) {
	if (current_letter_index > max_end_pos) {	//Прочли что-то большее - обновляем max
		max_end_pos = current_letter_index;
	}
	if (current_letter_index == word.length()) { //Если достигли конца, выходим
		return;
	}
	for (auto next : vertex->ways) {						//ДФС по буквам и эпсилонам
		if (next.second == word[current_letter_index]) {	//доказательство его рабыто в theory.txt
			++current_letter_index;
			DFS(next.first);
			--current_letter_index;
		}
		else if (next.second == '#') {
			DFS(next.first);
		}
	}
}

int solve(const string& w, const string& regular_exp) {	//Функция для 
	Solver sol(w);
	return sol.find_max_substring(regular_exp);
}