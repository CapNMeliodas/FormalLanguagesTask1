#include "LAutomata.h"

using namespace std;

LAutomata::LAutomata(char symbol) {  		//Строим базовый НКА от одной буквы
	shared_ptr<Node> new_root(new Node);					//(его вид в theory.txt)
	shared_ptr<Node> s(new Node);
	s->terminal = true;
	terminal = s;
	root = new_root;
	root->ways.push_back( {s, symbol} );
	automata.push_back(root);
	automata.push_back(s);
}

LAutomata& LAutomata::operator+=(const LAutomata& right) {	//Учимся объединять языки,
 	for (int i = 0; i < right.automata.size(); ++i) {		//задаваемые автоматом(рисунок в theory.txt)
 		this->automata.push_back(right.automata[i]);
 	}
 	Node* new_root = new Node();
 	Node* last = new Node();
	this->automata.push_back(new_root);
	this->automata.push_back(last);
 	last->terminal = true;
 	new_root->ways.push_back( {this->root, '#'} );
 	new_root->ways.push_back( {right.root, '#'} );
 	this->root = new_root;
 	this->terminal->ways.push_back( {last, '#'} );
 	this->terminal->terminal = false;
 	right.terminal->ways.push_back( {last, '#'} );
 	right.terminal->terminal = false;
 	this->terminal = last;
}

LAutomata& LAutomata::operator*=(const LAutomata& right) {	//Конкатенация языков(рисунок в theory.txt)
 	for (int i = 0; i < right.automata.size(); ++i) {
 		this->automata.push_back(right.automata[i]);
 	}
 	this->terminal->terminal = false;
 	this->terminal->ways.push_back( {right.root, '#'} );
 	this->terminal = right.terminal;
}

void LAutomata::CliniStar() {	//Операция Клини(рисунок в theory.txt)
 	Node* new_root = new Node();
 	automata.push_back(new_root);
 	new_root->ways.push_back( {root, '#'} );
 	root = new_root;
 	terminal->terminal = false;
 	terminal->ways.push_back( {root, '#'} );
 	root->terminal = true;
 	terminal = root;
}

vector<Node*> LAutomata::get_automata() { //Вернуть автомат в виде вектора *Node
 	return automata;
}

void LAutomata::numerize_automata() { //Пронумеровать автомат в порядке вектора automata
	set<Node*> v_ptrs;
	int counter = 0;
	for(int i =0; i < automata.size(); ++i) {
		if (v_ptrs.find(automata[i]) == v_ptrs.end()) {
			automata[i]->number = counter;
			++counter;
			v_ptrs.insert(automata[i]);
		}
	}
	is_numerized = true;
}

void LAutomata::show_automata() { //Вывести его на экран в нормальном виде
	if(!is_numerized) {			  //Номер -> Буква -> Номер
		numerize_automata();
	}
	for(int i =0; i < automata.size(); ++i) {
		for(int j = 0; j < automata[i]->ways.size(); ++j) {
			cout << automata[i]->number << "->" << automata[i]->ways[j].second << "->" << automata[i]->ways[j].first->number << endl;
		}
	}
}

vector<tuple<int, char, int>> LAutomata::get_numeric_automata() { //Вернуть автомат в привычном нам виде:
	if(!is_numerized) {											  //Номер -> Буква -> Номер
		numerize_automata();
	}
	vector<std::tuple<int, char, int>> numeric_automata;
	for(int i =0; i < automata.size(); ++i) {
		for(int j = 0; j < automata[i]->ways.size(); ++j) {
			auto tmp = make_tuple(automata[i]->number, automata[i]->ways[j].second, automata[i]->ways[j].first->number);
			numeric_automata.push_back(tmp);
		}
	}
	return numeric_automata;
}

LAutomata::~LAutomata() {
 	for (int i = 0; i < automata.size(); ++i) {
 		delete automata[i];
 	}
}