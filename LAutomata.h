#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <set>
#include <memory>

struct Node {
	Node() = default;
	std::vector<std::pair<std::shared_ptr<Node>, char>> ways; //Вектор ребер из данной вершины:
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
 	std::vector<std::shared_ptr<Node>> get_automata(); 
 	std::vector<std::tuple<int, char, int>> get_numeric_automata();
 	void show_numeric_automata();
 	void show_automata();
 	~LAutomata();
private:
	void numerize_automata();

	bool is_numerized = false;
	std::shared_ptr<Node> root;
	std::shared_ptr<Node> terminal;
	std::vector<std::shared_ptr<Node>> automata;
};