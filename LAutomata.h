#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <set>

struct Node {
	Node() = default;
	std::vector<std::pair<Node*, char>> ways; //Вектор ребер из данной вершины:
										 	  //указатель на следующую, и буква
										      //И Бука по которой переходим
	bool terminal = false; //Является ил веришна терминальной
	int number = 0;
};

class LAutomata {
public:
	LAutomata(char symbol);
 	LAutomata& operator+=(const LAutomata& right);
 	LAutomata& operator*=(const LAutomata& right);
 	void CliniStar();
 	std::vector<Node*> get_automata(); 
 	std::vector<std::tuple<int, char, int>> get_numeric_automata();
 	void show_numeric_automata();
 	void show_automata();
 	~LAutomata();
private:
	void numerize_automata();

	bool is_numerized = false;
	Node* root;
	Node* terminal;
	std::vector<Node*> automata;
};