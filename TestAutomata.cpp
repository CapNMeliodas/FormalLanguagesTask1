#include "TestAutomata.h"

using namespace std;

vector<vector<std::tuple<int, char ,int>>> Tester::correct_automatas;
std::vector<LAutomata*> Tester::automatas;

void Tester::SetUpAutomata() {
	LAutomataBuilder builder;
	Tester::automatas.push_back(builder.build("ab+*"));
	Tester::automatas.push_back(builder.build("a*b*+"));
	Tester::automatas.push_back(builder.build("ab.*"));
};

void Tester::SetUpTestCase() {
	//(a+b)*
	vector<tuple<int, char ,int>> test;
	test.push_back(make_tuple(0, 'b', 1));
	test.push_back(make_tuple(1, '#', 5));
	test.push_back(make_tuple(2, 'a', 3));
	test.push_back(make_tuple(3, '#', 5));
	test.push_back(make_tuple(4, '#', 0));
	test.push_back(make_tuple(4, '#', 2));
	test.push_back(make_tuple(5, '#', 6));
	test.push_back(make_tuple(6, '#', 4));
	Tester::correct_automatas.push_back(test);
	test.resize(0);
	//a*+b*
	test.push_back(make_tuple(0, 'b', 1));
	test.push_back(make_tuple(1, '#', 2));
	test.push_back(make_tuple(2, '#', 0));
	test.push_back(make_tuple(2, '#', 7));
	test.push_back(make_tuple(3, 'a', 4));
	test.push_back(make_tuple(4, '#', 5));
	test.push_back(make_tuple(5, '#', 3));
	test.push_back(make_tuple(5, '#', 7));
	test.push_back(make_tuple(6, '#', 2));
	test.push_back(make_tuple(6, '#', 5));
	Tester::correct_automatas.push_back(test);
	test.resize(0);
	//(ab)*
	test.push_back(make_tuple(0, 'b', 1));
	test.push_back(make_tuple(1, '#', 2));
	test.push_back(make_tuple(2, 'a', 3));
	test.push_back(make_tuple(3, '#', 4));
	test.push_back(make_tuple(4, '#', 0));
	Tester::correct_automatas.push_back(test);
	test.resize(0);
	Tester::SetUpAutomata();
}

vector<tuple<int, char ,int>> Tester::GetElement(size_t index) {
	return Tester::correct_automatas.at(index);
}


TEST_F(Tester, AutomataEQ) {
  EXPECT_EQ(Tester::GetElement(0), Tester::automatas[0]->get_numeric_automata());
  EXPECT_EQ(Tester::GetElement(1), Tester::automatas[1]->get_numeric_automata());
  EXPECT_EQ(Tester::GetElement(2), Tester::automatas[2]->get_numeric_automata());
}