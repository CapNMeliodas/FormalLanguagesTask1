#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "LAutomata.h"


//Строитель автомата по регулярке
class LAutomataBuilder{
public:
	LAutomataBuilder() = default;
	LAutomata* build(const std::string& regular_exp);
private:
	LAutomata* B2;
};
